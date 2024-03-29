//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
#include "Unit1.h"
#include "common.h"
#include "../_Common_/Lib/bitmap.h"
#include "../_Common_/Lib/strings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
extern AUDIO_DATA *AudioDataSpectre;
extern FFT_RESULT *TTFRes;
extern PACKETS *Packets;

FFT_RESULT *TTFRes2;
FFT_RESULT *TTFRes3;
int POS4,T;

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
TTFRes2=new FFT_RESULT();
TTFRes3=new FFT_RESULT();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::DrawExecute(TObject *Sender)
{
int i,j,sx,sy;
double dx,dy,x1,x2,y1,y2;
TCanvas *canvas=PaintBox1->Canvas;
// Размеры экрана
sx=canvas->ClipRect.Right;
sy=canvas->ClipRect.Bottom;
dy=1.*sy/TTFRes->T;
dx=1.*sx/TTFRes->N;
// Очистка фона
canvas->Brush->Color=clWhite;
canvas->FillRect(TRect(0,0,sx,sy));
Image1->Update();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::PaintBox1Paint(TObject *Sender)
{
DrawExecute(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::CalculateExecute(TObject *Sender)
{
int i,j,l,pts=1024,pts2,pos,len;
double val[1024],res[1024],a,b,z;
// Кол-во точек
pts2=TrackBar1->Position*pts/(2*TrackBar1->Max);
// Корректируем позицию
if (POS4<0) POS4=0;
if (POS4>=AudioDataSpectre->AllItems-50000) POS4=AudioDataSpectre->AllItems-50000;
// Определяем размер данных
/*len=480*(Packets->Data[AudioData->CurrentPacket].Len
	+Packets->Data[AudioData->CurrentPacket].LeftPause
	+Packets->Data[AudioData->CurrentPacket].RightPause);*/
len=50000; // Чуть более 1 секунды
// Читаем данные
AudioDataSpectre->read(POS4,len);
TTFRes->max=0.;
TTFRes2->max=0.;
for (i=0;i<TTFRes->T;i++) {
	// Находим положение начала области звуковых данных в зависимости от времени
	l=48*i;
	switch (TabControl1->TabIndex) {
		case 0:
				// Данные
				for (j=0;j<pts;j++) val[j]=1.*AudioDataSpectre->Data[l+j]/32768; // Читаем данные и преобразовываем в double
				FFTAnalysis(val,res,pts,pts); // Вычисляем частоты
				TTFRes->Add(res,i); // Запоминаем результат
		case 1:
				// Производная
				for (j=0;j<pts;j++) val[j]=1.*AudioDataSpectre->DataP(l+j)/32768; // Читаем данные и преобразовываем в double
				FFTAnalysis(val,res,pts,pts); // Вычисляем частоты
				TTFRes->Add(res,i); // Запоминаем результат
		case 2:
				// Вторая производная
				for (j=0;j<pts;j++) val[j]=1.*AudioDataSpectre->DataP2(l+j)/32768; // Читаем данные и преобразовываем в double
				FFTAnalysis(val,res,pts,pts); // Вычисляем частоты
				TTFRes->Add(res,i); // Запоминаем результат
	}
}
//  Вычисляем усреднённые значения
int DM=0,DN=0;
double *Buf=new double[TTFRes->N*TTFRes->T];
RecalculateArray(TTFRes->Data,Buf,TTFRes->N,TTFRes->T,DM,DN);
// Рисуем картинку
TBitmap *bmp=new TBitmap;
unsigned char *p;
bmp->PixelFormat=pf24bit;
bmp->SetSize(pts2,TTFRes->T);
for (j=0;j<TTFRes->T;j++) {
	p=(unsigned char*)bmp->ScanLine[j];
	l=0;
	for (i=0;i<pts2;i++) {
		//z=255.*TrackBar2->Position*TTFRes->Data[TTFRes->N*j+i]/TTFRes->max;
        z=255.*TrackBar2->Position*Buf[TTFRes->N*j+i]/TTFRes->max;
		z=z*(1.+i*TrackBar4->Position/pts2); // Подсветка верхних частот
		if (z>255.) z=255.; // Проверка переполлнения
		p[l++]=(unsigned char)(z);
		p[l++]=(unsigned char)(z);
		p[l++]=0;
		//p[l++]=(unsigned char)(z);
	}
}
Image1->Picture->Bitmap->Assign(bmp);
delete bmp;
delete[] Buf;
StatusBar1->Panels[0].Items[0]->Text="Позиция: "+GetTimeForMovieRus_double(1.*POS4/48000);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::BitBtn1Click(TObject *Sender)
{ // Предыдущий пакет
if (Form1->StringGrid1->Row>1) Form1->StringGrid1->Row--;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::BitBtn2Click(TObject *Sender)
{ // Следующий пакет
if (Form1->StringGrid1->Row<Form1->StringGrid1->RowCount-1) Form1->StringGrid1->Row++;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::TabControl1Change(TObject *Sender)
{
CalculateExecute(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::ShowPacketExecute(TObject *Sender)
{
//POS4=480*(Packets->Data[AudioDataSpectre->CurrentPacket].Pos-Packets->Data[AudioDataSpectre->CurrentPacket].LeftPause);
POS4=480*Packets->Data[AudioDataSpectre->CurrentPacket].Pos;
CalculateExecute(this);
StatusBar1->Panels[0].Items[1]->Text="Пакет: "+UnicodeString(AudioDataSpectre->CurrentPacket);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::BitBtn3Click(TObject *Sender)
{ // Назад на 50 мс
POS4-=480*5;
CalculateExecute(this);
StatusBar1->Panels[0].Items[1]->Text="";
}
//---------------------------------------------------------------------------
void __fastcall TForm4::BitBtn4Click(TObject *Sender)
{ // Далее на 50 мс
POS4+=480*5;
CalculateExecute(this);
StatusBar1->Panels[0].Items[1]->Text="";
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
int t;
t=TTFRes->T*Y/Image1->Height;
if (t!=T) {
	T=t;
	int i,sx,sy,y,y0,dy,k,m,pts=1024,pts2;
	// Кол-во точек
	pts2=TrackBar1->Position*pts/(2*TrackBar1->Max);
	// Очистка фона
	TCanvas *canvas=PaintBox1->Canvas;
	canvas->Brush->Color=clWhite;
	canvas->FillRect(canvas->ClipRect);
	//
	sx=canvas->ClipRect.Right;
	sy=canvas->ClipRect.Bottom;
	dy=sy;
	k=dy-10;
	y0=dy-1;
	// Рисуем сетку
	canvas->Pen->Color=TColor(220+(220<<8)+(220<<16));
	for (i=0;i<sx;i+=10) {
		canvas->MoveTo(i,0);
		canvas->LineTo(i,sy);
	}
	// Рисуем разложение по частотам
	canvas->Pen->Color=TColor(100<<8);
	m=T*TTFRes->N; // Индекс начала массива
	y=k*TTFRes->Data[m];
	canvas->MoveTo(0,y0-y);
	for (i=1;i<pts2;i++) {
		y=k*TTFRes->Data[m+i]/TTFRes->max;
		canvas->LineTo(i*sx/pts2,y0-y);
	}
	// Рисуем ось
	canvas->Pen->Color=clBlack;
	canvas->MoveTo(0,y0);
	canvas->LineTo(sx,y0);
	// Рисуем надписи
	canvas->Brush->Color=clWhite;
	canvas->Font->Color=TColor(100<<8);
	canvas->TextOut(10,0,"Частотный спектр");
}
}
//---------------------------------------------------------------------------

