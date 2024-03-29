#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include "../_Common_/Lib/files.h"

//------------------------------------------------------------------------
ENVELOPE::ENVELOPE() {
Items=0;
Data=new short[1];
}

ENVELOPE::~ENVELOPE() {
delete[] Data;
}

bool ENVELOPE::read(UnicodeString filename) {
// Находим размер файла и определяем кол-во элементов
Items=getFileSize(filename)/2;
// Пересоздаём массив
delete[] Data;
Data=new short[Items];
// Читаем данные
FILE *fd=_wfopen(filename.w_str(),L"rb");
fread(&Data[0],2,Items,fd);
fclose(fd);
return(true);
}

void ENVELOPE::draw(int pos, TCanvas *canvas) {
int i,sx,sy,y,y0,dy,k;
// Проверка, что данные есть
if (Items==0) return;
// Очистка фона
canvas->Brush->Color=clWhite;
canvas->FillRect(canvas->ClipRect);
// Проверка выхода за границы
if (pos>=Items) return;
//
sx=canvas->ClipRect.Right;
sy=canvas->ClipRect.Bottom;
dy=sy/3;
k=dy-10;
y0=dy-1;
// Рисуем сетку
canvas->Pen->Color=TColor(220+(220<<8)+(220<<16));
for (i=0;i<sx;i+=10) {
	canvas->MoveTo(i,0);
	canvas->LineTo(i,sy);
}
// Рисуем огибающую
canvas->Pen->Color=TColor(100<<8);
y=k*Data[pos]/32768;
canvas->MoveTo(0,y0-y);
for (i=pos;i<pos+sx;i++) {
	if (i>=Items) break;
	y=k*Data[i]/32768;
	canvas->LineTo(i-pos,y0-y);
}
// Рисуем ось
canvas->Pen->Color=clBlack;
canvas->MoveTo(0,y0);
canvas->LineTo(sx,y0);
// Рисуем надписи
canvas->Brush->Color=clWhite;
canvas->Font->Color=TColor(100<<8);
canvas->TextOut(10,0,"Огибающая");
}
//------------------------------------------------------------------------
PACKETS::PACKETS() {
	Items=0;
	RecSize=24;
	Data=new Packet[1];
	BoxSize=8;
}

PACKETS::~PACKETS() {
	Items=0;
	delete[] Data;
}

bool PACKETS::read(UnicodeString filename) {
// Находим размер файла и определяем кол-во элементов
Items=getFileSize(filename)/RecSize;
// Пересоздаём массив
delete[] Data;
Data=new Packet[Items];
// Читаем данные
FILE *fd=_wfopen(filename.w_str(),L"rb");
fread(&Data[0],RecSize,Items,fd);
fclose(fd);
return(true);
}

void PACKETS::draw(int pos, TCanvas *canvas) {
int i,sx,sy,dy,k,y0,x1,x2,y1,y2;
// Проверка, что данные есть
if (Items==0) return;
//
canvas->Pen->Color=TColor(100<<8);
sx=canvas->ClipRect.Right;
sy=canvas->ClipRect.Bottom;
dy=sy/3;
k=dy-10;
y0=2*dy-1;
// Цикл по пакетам
for (i=0;i<Items;i++) {
	if (Data[i].Pos+Data[i].Len<pos) continue; // Данные слева
	if (Data[i].Pos>pos+sx) break; // Остальное справа
	x1=Data[i].Pos-pos;
	x2=Data[i].Pos+Data[i].Len-pos;
	y1=y0;
	y2=y0-k*Data[i].Amp/32768;
	canvas->Brush->Color=TColor(255<<16);
	canvas->FillRect(Rect(x1,y1,x2,y2));
	y2=y0-k*Data[i].AmpMin/32768;
	canvas->Brush->Color=TColor(100<<16);
	canvas->FillRect(Rect(x1,y1,x2,y2));
}
// Рисуем ось
canvas->Pen->Color=clBlack;
canvas->MoveTo(0,y0);
canvas->LineTo(sx,y0);
// Рисуем надписи
canvas->Brush->Color=clWhite;
canvas->Font->Color=TColor(255<<16);
canvas->TextOut(10,dy,"Пакет (длина, амплитуда)");
canvas->Font->Color=TColor(100<<16);
canvas->TextOut(170,dy,"Минимум огибающей");
}

void PACKETS::drawRel(int pos, TCanvas *canvas) {
int i,j,sx,sy,dy,k,y0,x1,x2,y1,y2,m=5;
// Проверка, что данные есть
if (Items==0) return;
// Очистка фона
canvas->Brush->Color=clWhite;
canvas->FillRect(canvas->ClipRect);
//
sx=canvas->ClipRect.Right;
sy=canvas->ClipRect.Bottom;
dy=sy/6;
k=dy-10;
y0=2*dy-1;
// Цикл по пакетам
for (i=pos;i<Items;i++) {
	j=i-pos;
	if (j*BoxSize>sx) break; // Остальное справа
	x1=j*BoxSize;
	x2=x1+BoxSize-1;
	// Amplitude
	y1=dy;
	y2=y1-k*Data[i].Amp/32768;
	canvas->Brush->Color=TColor(100<<8);
	canvas->FillRect(Rect(x1,y1,x2,y2));
	// Rel Amplitude
	if (i==0) y2=k/m;
	else {
		y2=k*Data[i].Amp/Data[i-1].Amp/m;
		if (y2>k) y2=k;
	}
	y2=y1+y2;
	canvas->Brush->Color=TColor(255<<8);
	canvas->FillRect(Rect(x1,y1,x2,y2));
	// Length
	y1=3*dy;
	y2=y1-k*Data[i].Len/30;
	canvas->Brush->Color=TColor(100<<16);
	canvas->FillRect(Rect(x1,y1,x2,y2));
	// Rel Length       -
	if (i==0) y2=k/m;
	else {
		if (Data[i-1].Len==0) y2=k/m;
		else y2=k*Data[i].Len/Data[i-1].Len/m;
		if (y2>k) y2=k;
	}
	y2=y1+y2;
	canvas->Brush->Color=TColor(255<<16);
	canvas->FillRect(Rect(x1,y1,x2,y2));
	// Pause
	y1=5*dy;
	y2=y1-k*Data[i].Len/30;
	canvas->Brush->Color=TColor(100);
	canvas->FillRect(Rect(x1,y1,x2,y2));
	// Rel Pause
	if (i==0) y2=k/m;
	else {
		if (Data[i-1].RightPause==0) y2=k/m;
		else y2=k*Data[i].RightPause/Data[i-1].RightPause/m;
		if (y2>k) y2=k;
	}
	y2=y1+y2;
	canvas->Brush->Color=TColor(255);
	canvas->FillRect(Rect(x1,y1,x2,y2));
}
// Рисуем оси
canvas->Pen->Color=clBlack;
y0=dy+k/m; 		canvas->MoveTo(0,y0); 	canvas->LineTo(sx,y0);
y0=3*dy+k/m; 	canvas->MoveTo(0,y0); 	canvas->LineTo(sx,y0);
y0=5*dy+k/m; 	canvas->MoveTo(0,y0); 	canvas->LineTo(sx,y0);
// Рисуем надписи
canvas->Brush->Color=clWhite;
canvas->Font->Color=TColor(100<<8);
canvas->TextOut(10,0,"Амплитуда");
canvas->Font->Color=TColor(250<<8);
canvas->TextOut(150,0,"Изменение амплитуды (отношение к предыдущему)");

canvas->Font->Color=TColor(100<<16);
canvas->TextOut(10,dy*2,"Длина пакета");
canvas->Font->Color=TColor(250<<16);
canvas->TextOut(150,dy*2,"Изменение длины (отношение к предыдущему)");

canvas->Font->Color=TColor(100);
canvas->TextOut(10,dy*4,"Пауза");
canvas->Font->Color=TColor(250);
canvas->TextOut(150,dy*4,"Изменение паузы (отношение к предыдущему)");
}
//------------------------------------------------------------------------
int Items,BufSize;
short *Data;
FILE *fd;

AUDIO_DATA::AUDIO_DATA() {
AllItems=0;
Data=new short[1];
fd=NULL;
Show=true;
Show1=true;
Show2=true;
Show3=true;
}

AUDIO_DATA::~AUDIO_DATA() {
delete[] Data;
if (fd!=NULL) fclose(fd);
}

bool AUDIO_DATA::open(UnicodeString filename) {
if (fd!=NULL) fclose(fd);
AllItems=getFileSize(filename)/2;
fd=_wfopen(filename.w_str(),L"rb");
return(true);
}

bool AUDIO_DATA::read(int pos,int items) {
if (AllItems==0) return(false);
delete[] Data;
if (pos+items>AllItems) Items=AllItems-pos;
else Items=items;
Data=new short[Items];
fseek(fd,pos*2,SEEK_SET);
fread(&Data[0],2,Items,fd);
return(true);
}

short AUDIO_DATA::DataP(int n) {
if (n>=Items) return(0);
if (n<0) return(0);
if (n==0) return(Data[1]-Data[0]);
return(Data[n]-Data[n-1]);
}

short AUDIO_DATA::DataP2(int n) {
if (n>=Items) return(0);
if (n<0) return(0);
if (n==0) return(DataP(1)-DataP(0));
return(DataP(n)-DataP(n-1));
}

short AUDIO_DATA::DataP3(int n) {
if (n>=Items) return(0);
if (n<0) return(0);
if (n==0) return(DataP2(1)-DataP2(0));
return(DataP2(n)-DataP2(n-1));
}

void AUDIO_DATA::draw(int pos, TCanvas *canvas,int len) {
int i,j,sx,sy,dy,k,y0,y,max,val;
// Проверка, что данные есть
if (AllItems==0) return;
if (pos>=Items) return;
//
sx=canvas->ClipRect.Right;
sy=canvas->ClipRect.Bottom;
dy=sy/3;
// Рисуем оси и длину проигрывания
canvas->Pen->Color=clBlack;
canvas->MoveTo(0,dy-1);
canvas->LineTo(sx,dy-1);
canvas->MoveTo(0,dy*2-1);
canvas->LineTo(sx,dy*2-1);
canvas->Pen->Color=clYellow;
int xx=pos/480;
canvas->MoveTo(xx,dy-1);
canvas->LineTo(xx+len,dy-1);
canvas->MoveTo(xx,dy*2-1);
canvas->LineTo(xx+len,dy*2-1);
// Очистка фона
canvas->Brush->Color=clWhite;
canvas->FillRect(TRect(0,2*dy,sx,3*dy));

// Третья производная
if (Show3) {
	// Находим максимум данных
	max=0;
	for (i=0;i<sx;i++) {
		j=pos+i;
		if (j>=Items) break;
		val=DataP3(j);
		if (val>max) max=val;
	}
	// Рисуем вторую производную
	k=dy/2-10;
	canvas->Pen->Color=TColor((250<<16)+250);
	y0=3*dy-dy/2;
	if (max==0) y=y0;
	else y=y0-k*DataP3(pos)/max;
	canvas->MoveTo(0,y);
	//
	for (i=0;i<sx;i++) {
		j=pos+i;
		if (j>=Items) break;
		if (max==0) y=y0;
		else y=y0-k*DataP3(j)/max;
		canvas->LineTo(i,y);
	}
}

// Вторая производная
if (Show2) {
	// Находим максимум данных
	max=0;
	for (i=0;i<sx;i++) {
		j=pos+i;
		if (j>=Items) break;
		val=DataP2(j);
		if (val>max) max=val;
	}
	// Рисуем вторую производную
	k=dy/2-10;
	canvas->Pen->Color=TColor(250<<16);
	y0=3*dy-dy/2;
	if (max==0) y=y0;
	else y=y0-k*DataP2(pos)/max;
	canvas->MoveTo(0,y);
	//
	for (i=0;i<sx;i++) {
		j=pos+i;
		if (j>=Items) break;
		if (max==0) y=y0;
		else y=y0-k*DataP2(j)/max;
		canvas->LineTo(i,y);
	}
}

// Производная
if (Show1) {
	// Находим максимум данных
	max=0;
	for (i=0;i<sx;i++) {
		j=pos+i;
		if (j>=Items) break;
		val=DataP(j);
		if (val>max) max=val;
	}
	// Рисуем производную звуковых данных
	k=dy/2-10;
	canvas->Pen->Color=TColor(250<<8);
	y0=3*dy-dy/2;
	if (max==0) y=y0;
	else y=y0-k*DataP(pos)/max;
	canvas->MoveTo(0,y);
	for (i=0;i<sx;i++) {
		j=pos+i;
		if (j>=Items) break;
		if (max==0) y=y0;
		else y=y0-k*DataP(j)/max;
		canvas->LineTo(i,y);
	}
}

// Звуковые данные
if (Show) {
	// Находим максимум данных
	max=0;
	for (i=0;i<sx;i++) {
		j=pos+i;
		if (j>=Items) break;
		if (Data[j]>max) max=Data[j];
	}
	// Рисуем звуковые данные
	k=dy/2-10;
	canvas->Pen->Color=TColor(250);
	y0=3*dy-dy/2;
	if (max==0) y=y0;
	else y=y0-k*Data[pos]/max;
	canvas->MoveTo(0,y);
	for (i=0;i<sx;i++) {
		j=pos+i;
		if (j>=Items) break;
		if (max==0) y=y0;
		else y=y0-k*Data[j]/max;
		canvas->LineTo(i,y);
	}
}

// Рисуем ось
canvas->Pen->Color=clBlack;
canvas->MoveTo(0,y0);
canvas->LineTo(sx,y0);
canvas->Font->Color=TColor(250);
canvas->TextOut(10,dy*2+20,"Звуковой сигнал");
canvas->Font->Color=TColor(250<<8);
canvas->TextOut(110,dy*2+20,"Производная");
canvas->Font->Color=TColor(250<<16);
canvas->TextOut(210,dy*2+20,"Вторая производная");
canvas->Font->Color=TColor((250<<16)+250);
canvas->TextOut(400,dy*2+20,"Третья производная");
}
//------------------------------------------------------------------------

//_________________________________________________________________________________________
//_________________________________________________________________________________________
//
// NAME:          FFT.
// PURPOSE:       Быстрое преобразование Фурье: Комплексный сигнал в комплексный спектр и обратно.
//                В случае действительного сигнала в мнимую часть (Idat) записываются нули.
//                Количество отсчетов - кратно 2**К - т.е. 2, 4, 8, 16, ... (см. комментарии ниже).
//
//
// PARAMETERS:
//
//    double *Rdat    [in, out] - Real part of Input and Output Data (Signal or Spectrum)
//    double *Idat    [in, out] - Imaginary part of Input and Output Data (Signal or Spectrum)
//    int    N       [in]      - Input and Output Data length (Number of samples in arrays)
//    int    LogN    [in]      - Logarithm2(N)
//    int    Ft_Flag [in]      - Ft_Flag = FT_ERR_DIRECT  (i.e. -1) - Direct  FFT  (Signal to Spectrum)
//		                 Ft_Flag = FT_ERR_INVERSE (i.e.  1) - Inverse FFT  (Spectrum to Signal)
//
// RETURN VALUE:  false on parameter error, true on success.
//_________________________________________________________________________________________
//
// NOTE: In this algorithm N and LogN can be only:
//       N    = 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384;
//       LogN = 2, 3,  4,  5,  6,   7,   8,   9,   10,   11,   12,   13,    14;
//_________________________________________________________________________________________
//_________________________________________________________________________________________

bool  FFT(double *Rdat, double *Idat, int N, int LogN, int Ft_Flag)
{
  // parameters error check:
  if((Rdat == NULL) || (Idat == NULL))                  return false;
  if((N > 16384) || (N < 1))                            return false;
  if(!NUMBER_IS_2_POW_K(N))                             return false;
  if((LogN < 2) || (LogN > 14))                         return false;
  if((Ft_Flag != FT_DIRECT) && (Ft_Flag != FT_INVERSE)) return false;

  int  i, j, n, k, io, ie, in, nn;
  double         ru, iu, rtp, itp, rtq, itq, rw, iw, sr;

  static const double Rcoef[14] =
  {  -1.0000000000000000F,  0.0000000000000000F,  0.7071067811865475F,
      0.9238795325112867F,  0.9807852804032304F,  0.9951847266721969F,
      0.9987954562051724F,  0.9996988186962042F,  0.9999247018391445F,
      0.9999811752826011F,  0.9999952938095761F,  0.9999988234517018F,
      0.9999997058628822F,  0.9999999264657178F
  };
  static const double Icoef[14] =
  {   0.0000000000000000F, -1.0000000000000000F, -0.7071067811865474F,
     -0.3826834323650897F, -0.1950903220161282F, -0.0980171403295606F,
     -0.0490676743274180F, -0.0245412285229122F, -0.0122715382857199F,
     -0.0061358846491544F, -0.0030679567629659F, -0.0015339801862847F,
     -0.0007669903187427F, -0.0003834951875714F
  };

  nn = N >> 1;
  ie = N;
  for(n=1; n<=LogN; n++)
  {
    rw = Rcoef[LogN - n];
    iw = Icoef[LogN - n];
    if(Ft_Flag == FT_INVERSE) iw = -iw;
    in = ie >> 1;
    ru = 1.0F;
    iu = 0.0F;
    for(j=0; j<in; j++)
    {
      for(i=j; i<N; i+=ie)
      {
        io       = i + in;
        rtp      = Rdat[i]  + Rdat[io];
        itp      = Idat[i]  + Idat[io];
        rtq      = Rdat[i]  - Rdat[io];
        itq      = Idat[i]  - Idat[io];
        Rdat[io] = rtq * ru - itq * iu;
        Idat[io] = itq * ru + rtq * iu;
        Rdat[i]  = rtp;
        Idat[i]  = itp;
      }

      sr = ru;
      ru = ru * rw - iu * iw;
      iu = iu * rw + sr * iw;
    }

    ie >>= 1;
  }

  for(j=i=1; i<N; i++)
  {
    if(i < j)
    {
      io       = i - 1;
      in       = j - 1;
      rtp      = Rdat[in];
      itp      = Idat[in];
      Rdat[in] = Rdat[io];
      Idat[in] = Idat[io];
      Rdat[io] = rtp;
      Idat[io] = itp;
    }

    k = nn;

    while(k < j)
    {
      j   = j - k;
      k >>= 1;
    }

    j = j + k;
  }

  if(Ft_Flag == FT_DIRECT) return true;

  rw = 1.0F / N;

  for(i=0; i<N; i++)
  {
    Rdat[i] *= rw;
    Idat[i] *= rw;
  }

  return true;
}
//---------------------------------------------------------------------------
// Пример вычисления БПФ от одного периода косинусного
// действительного сигнала
#define KK 1024
void Test_FFT()
{
  static double Re[KK];
  static double Im[KK];
  double  p = 2. * 3.141592653589 / KK; // будет 8 отсчетов на период

  int i;
  // формируем сигнал
  for(i=0; i<KK; i++)
  {
	Re[i] = cos(3.9* p * i);  // заполняем действительную часть сигнала
	Im[i] = 0.0;         // заполняем мнимую часть сигнала
  }

  FFT(Re, Im, KK, 10, FT_DIRECT); // вычисляем прямое БПФ

  // выводим действительную и мнимую части спектра и спектр мощности
  FILE *f = fopen("spectrum.txt", "w");
  for(i=0; i<KK; i++)
  {
	fprintf(f, "%14.10f  %14.10f  %14.10f\n", Re[i], Im[i], Re[i]*Re[i]+Im[i]*Im[i]);
  }
  fclose(f);
}
//---------------------------------------------------------------------------
// AVal - массив анализируемых данных, Nvl - длина массива должна быть кратна степени 2.
// FTvl - массив полученных значений, Nft - длина массива должна быть равна Nvl.
const double TwoPi = 6.283185307179586;

void FFTAnalysis(double *AVal, double *FTvl, int Nvl, int Nft) {
  int i, j, n, m, Mmax, Istp;
  double Tmpr, Tmpi, Wtmp, Theta;
  double Wpr, Wpi, Wr, Wi;
  double *Tmvl;
  n = Nvl * 2; Tmvl = new double[n];
  for (i = 0; i < n; i+=2) { Tmvl[i] = 0; Tmvl[i+1] = AVal[i/2]; }
  i = 1; j = 1;
  while (i < n) {
	if (j > i) {
	  Tmpr = Tmvl[i]; Tmvl[i] = Tmvl[j]; Tmvl[j] = Tmpr;
	  Tmpr = Tmvl[i+1]; Tmvl[i+1] = Tmvl[j+1]; Tmvl[j+1] = Tmpr;
	}
	i = i + 2; m = Nvl;
	while ((m >= 2) && (j > m)) { j = j - m; m = m >> 1; }
	j = j + m;
  }
  Mmax = 2;
  while (n > Mmax) {
	Theta = -TwoPi / Mmax; Wpi = sin(Theta);
	Wtmp = sin(Theta / 2); Wpr = Wtmp * Wtmp * 2;
	Istp = Mmax * 2; Wr = 1; Wi = 0; m = 1;
	while (m < Mmax) {
	  i = m; m = m + 2; Tmpr = Wr; Tmpi = Wi;
	  Wr = Wr - Tmpr * Wpr - Tmpi * Wpi;
	  Wi = Wi + Tmpr * Wpi - Tmpi * Wpr;
	  while (i < n) {
		j = i + Mmax;
		Tmpr = Wr * Tmvl[j] - Wi * Tmvl[j-1];
		Tmpi = Wi * Tmvl[j] + Wr * Tmvl[j-1];
		Tmvl[j] = Tmvl[i] - Tmpr; Tmvl[j-1] = Tmvl[i-1] - Tmpi;
		Tmvl[i] = Tmvl[i] + Tmpr; Tmvl[i-1] = Tmvl[i-1] + Tmpi;
		i = i + Istp;
	  }
	}
	Mmax = Istp;
  }
  for (i = 0; i < Nft; i++) { j = i * 2; FTvl[i] = 2*sqrt(pow(Tmvl[j],2) + pow(Tmvl[j+1],2))/Nvl; }
  delete []Tmvl;
}
//---------------------------------------------------------------------------
FFT_RESULT::FFT_RESULT() {
Data=new double[1];
init(512,1000);
}

FFT_RESULT::~FFT_RESULT() {
delete[] Data;
}

bool FFT_RESULT::init(int n,int t) {
N=n;
T=t;
delete[] Data;
Data=new double[N*T];
max=0.;
return(true);
}

bool FFT_RESULT::Add(double *arr,int index) {
int i,k;
if (index>=T) return(false);
k=index*N;
for (i=0;i<N;i++) {
	Data[k++]=arr[i];
	if (arr[i]>max) max=arr[i];
}
return(true);
}
//------------------------------------------------------------------------
SPECTR_BASE_RESULT::SPECTR_BASE_RESULT() {
	RecID=new int[1];
	Delta=new float[1];
	MaxItems=0;
	Items=0;
}

SPECTR_BASE_RESULT::~SPECTR_BASE_RESULT() {
	delete[] RecID;
	delete[] Delta;
}

void SPECTR_BASE_RESULT::Init(int max_items) {
	delete[] RecID;
	delete[] Delta;
	MaxItems=max_items;
	Items=0;
	RecID=new int[MaxItems];
	Delta=new float[MaxItems];
}

int SPECTR_BASE_RESULT::FindPos(float delta) {
	int i;
	for (i=0;i<Items;i++) {
		if (delta<Delta[i]) return(i);
	}
	return(-1);
}

void SPECTR_BASE_RESULT::Insert(int n,int rec_id,float delta) {
	int i;
	for (i=Items-1;i>=n+1;i--) {
		RecID[i]=RecID[i-1];
		Delta[i]=Delta[i-1];
	}
	RecID[n]=rec_id;
	Delta[n]=delta;
}

void SPECTR_BASE_RESULT::Add(int rec_id,float delta) {
int i,n;
if (Items==0) { // Ещё нет элементов
	RecID[0]=rec_id;
	Delta[0]=delta;
	Items=1;
	return;
}
if (Items==MaxItems) { // Все места заняты
	if (delta>=Delta[Items-1]) return;
	// Ищем позицию, куда добавить
	if ((n=FindPos(delta))!=-1) {
		// Добавляем
		Insert(n,rec_id,delta);
	}
}
else { // Элементов меньше, чем может быть
	// Ищем позицию, куда добавить
	if ((n=FindPos(delta))!=-1) {
        Items++;
		// Добавляем
		Insert(n,rec_id,delta);
	}
}
}
//---------------------------------------------------------------------------
SPECTR_BASE::SPECTR_BASE() {
Sample=new SPECTR_SAMPLE[1];
Items=0;
LOADED=false;
Result=new SPECTR_BASE_RESULT;
Result->Init(10);
}

SPECTR_BASE::~SPECTR_BASE() {
delete[] Sample;
}

void SPECTR_BASE::init(int packets) {
if (packets<1) return;
Items=packets;
delete[] Sample;
Sample=new SPECTR_SAMPLE[Items];
LOADED=false;
}

void SPECTR_BASE::AddSample(AUDIO_DATA *adata,PACKETS *packets,int n) {
int i,j,k,l,pos[3],N;
double val[SPECTR_ITEMS*2],res[SPECTR_ITEMS*2];
N=SPECTR_ITEMS*2;
// Находим позиции начала, середины и конца
pos[0]=packets->Data[n].Pos*480;
pos[2]=(packets->Data[n].Pos+packets->Data[n].Len)*480-N;
pos[1]=(pos[0]+pos[2])/2;
for (k=0;k<3;k++) {
	// Читаем данные из файла
	adata->read(pos[k],N);
	// Преобразуем в double
	for (i=0;i<N;i++) val[i]=1.*adata->Data[i]/32768;
	// Находим частоты
	FFTAnalysis(val,res,N,N);
	// Сохраняем результат
	for (i=0;i<SPECTR_ITEMS;i++) Sample[n].Data[k][i]=res[i];
}
}

float SPECTR_BASE::Compare(float *sample,float *base) {
	int i;
	float res=0.;
	//for (i=0;i<SPECTR_ITEMS*3;i++) {
    for (i=0;i<SPECTR_ITEMS;i++) {
		res+=fabs(sample[i]-base[i]);
	}
	return(res);
}

bool SPECTR_BASE::FindBestMatch(SPECTR_SAMPLE *sample) {
int i;
float delta=0.;
// Цикл по всем пакетам в базе
Result->Init(10);
for (i=0;i<Items;i++) {
	// Находим разницу
	delta=Compare((float*)sample,(float*)&Sample[i]);
	// Записываем результат
	Result->Add(i,delta);
}
return(true);
}
//---------------------------------------------------------------------------
void RecalculateArray(double *A,double *B,int M,int N,int DM,int DN) {
int i,j,k,l,n=0,m,pts;
double sum,max;
// Цикл по вертикали
for (j=0;j<N;j++) {
	// Цикл по горизонтали
	for (i=0;i<M;i++) {
		// Среднее значение
		sum=0.;
		max=0.;
		pts=0;
		for (k=j-DN;k<=j+DN;k++) {
			if (k<0) continue;
			if (k>=N) continue;
			for (l=i-DM;l<=i+DM;l++) {
				if (l<0) continue;
				if (l>=M) continue;
				m=l+k*M;
				sum+=A[m];
				if (A[m]>max) max=A[m];
				pts++;
			}
		}
		B[n]=sum/pts;
		//B[n]=max;
		n++;
	}
}
}
//---------------------------------------------------------------------------
SPECTR_BASE_FOR_DETECT_PACKETS::SPECTR_BASE_FOR_DETECT_PACKETS() {
Items=0;
LOADED=false;
Data=new float[1];
Prev=new double[SPECTR_ITEMS];
Step=480;
N=1024;
}

SPECTR_BASE_FOR_DETECT_PACKETS::~SPECTR_BASE_FOR_DETECT_PACKETS() {
delete[] Data;
delete[] Prev;
}

void SPECTR_BASE_FOR_DETECT_PACKETS::Init(AUDIO_DATA *adata) {
// Определяем кол-во элементов
Items=adata->AllItems/Step;
Current=0;
delete[] Data;
Data=new float[Items];
for (int i=0;i<Items;i++) Data[i]=0.;
max=0.;
}

bool SPECTR_BASE_FOR_DETECT_PACKETS::ReadNext(AUDIO_DATA *adata) {
int i,N2;
double val[N],res[N],dif=0.;
N2=N/2;
// Читаем данные из файла
adata->read(Step*Current,N+2);
// Преобразуем в double
for (i=0;i<N;i++) val[i]=1.*adata->DataP(i)/32768;
// Находим частоты
FFTAnalysis(val,res,N,N);
// Сравниваем с предыдущим
for (i=0;i<N2;i++) {
	if (Current>0) dif+=fabs(res[i]-Prev[i]);
	Prev[i]=res[i];
}
// Сохраняем результат
Data[Current]=dif;
Current++;
return(true);
}

float SPECTR_BASE_FOR_DETECT_PACKETS::Get(int pos) {
if ((pos<0)||(pos>=Items)) return(0.);
return(Data[pos]);
}

bool SPECTR_BASE_FOR_DETECT_PACKETS::Read(UnicodeString filename,ENVELOPE *env) {
AUDIO_DATA *aData=new AUDIO_DATA;
aData->open(filename);
Init(aData);
int i,k,N2,e;
double val[N],res[N],dif,Norm=3.;
N2=N/2;
for (k=0;k<Items;k++) {
	// Читаем данные из файла
	aData->read(Step*k,N+2);
	// Преобразуем в double
	for (i=0;i<N;i++) {
		//val[i]=1.*aData->DataP(i)/32768;
		e=env->Data[i];
		if (e==0) e=1;
		val[i]=1.*aData->DataP(i)/e;
	}
	// Находим частоты
	FFTAnalysis(val,res,N,N);
	// Приводим некую "нормализацию" с коэффициентом нормализации = Norm
	for (i=0;i<N2;i++) {
		res[i]=res[i]*Norm*i/N2;
	}
	// Сравниваем с предыдущим
	dif=0.;
	for (i=0;i<N2;i++) {
		if (k>0) dif+=fabs(res[i]-Prev[i]);
		Prev[i]=res[i];
	}
	// Сохраняем результат
	if (dif>max) max=dif;
	Data[k]=dif;
}
delete aData;
LOADED=true;
return(true);
}

void SPECTR_BASE_FOR_DETECT_PACKETS::Draw(int pos,TCanvas *canvas) {
int i,sx,sy,y,y0,dy,k;
// Проверка, что данные есть
if (Items==0) return;
// Проверка выхода за границы
if (pos>=Items) return;
//
sx=canvas->ClipRect.Right;
sy=canvas->ClipRect.Bottom;
dy=sy/3;
k=dy-10;
y0=dy/2-1;
// Рисуем Разницу
canvas->Pen->Color=TColor((250<<16)+250);
y=1.*k*Data[pos]/max;
canvas->MoveTo(0,y0-y);
for (i=pos;i<pos+sx;i++) {
	if (i>=Items) break;
	y=k*Data[i]/max;
	canvas->LineTo(i-pos,y0-y);
}
// Рисуем надписи
canvas->Brush->Color=clWhite;
canvas->Font->Color=TColor((250<<16)+250);
canvas->TextOut(100,0,"Суммарная разница в спектре");
}
//---------------------------------------------------------------------------
COMPARE_FREQUENCES::COMPARE_FREQUENCES() {

}

COMPARE_FREQUENCES::~COMPARE_FREQUENCES() {

}

double COMPARE_FREQUENCES::CountSum(float *a,int items) {
double sum=0.;
for (int i=0;i<items;i++) sum+=a[i];
return(sum);
}

double COMPARE_FREQUENCES::Compare(float *a,float *b,int items) {
double sum_a=0.,sum_b=0.,ratio,diff=0.;
int i,j,k,l;
// Находим суммы значений для нормировки
for (i=0;i<items;i++) {
	sum_a+=a[i];
	sum_b+=b[i];
}
// Находим отношения значений
if (sum_b==0.) return(sum_a/items); // Возвращаем среднюю разницу
ratio=sum_a/sum_b;
// Ищем средний коэффициент, а также минимальное и максимальное значение
for (i=0;i<items;i++) {
	diff+=fabs(a[i]-ratio*b[i]);
}
return(diff/items);
}

COMPARE_FREQUENCES::Compare3(float *a1,float *a2,float *a3,float *b1,float *b2,float *b3,int items) {
// Находим суммы значений для нормировки
// Находим отношения значений
// Ищем средний коэффициент, а также минимальное и максимальное значение
// Уточняем средний коэффициент
// Находим суммараную разность между значениями
//
//
//
//
}

void COMPARE_FREQUENCES::CountDynamics(float *a1,float *a2,float *a3,int items,float *left,float *right) {
for (int i=0;i<items;i++) {
	if (a2[i]==0.) {
		left[i]=-a1[i];
        right[i]=-a3[i];
	}
	else {
		left[i]=a1[i]/a2[i];
		right[i]=a3[i]/a2[i];
	}
}
}


float COMPARE_FREQUENCES::CompareItem(float a,float b) {
	if (b==0.) return(a/IfZero);
	return(a/b);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------

