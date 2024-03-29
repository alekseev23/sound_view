#include <vcl.h>

struct FILENAMES {
	UnicodeString Audio,Dat,Envelope,Packets,BaseName,
		HistogramLen,HistogramPause,HistogramMaxPos;
};

//------------------------------------------------------------------------
class ENVELOPE {

public:
int Items;
short *Data;

ENVELOPE();
~ENVELOPE();
bool read(UnicodeString filename);
void draw(int pos, TCanvas *canvas);

};
//------------------------------------------------------------------------
struct Packet {
	int Pos;
	short Len;
	short LenRel;
	short Amp;
	short AmpRel;
	short AmpMin;
	short MaxPos;
	short LeftPause;
	short LeftPauseRel;
	short RightPause;
	short RightPauseRel;
};
//------------------------------------------------------------------------
class PACKETS {

public:
int Items,RecSize,BoxSize;
Packet *Data;

PACKETS();
~PACKETS();
bool read(UnicodeString filename);
void draw(int pos, TCanvas *canvas);
void drawRel(int pos, TCanvas *canvas);

};
//------------------------------------------------------------------------
class AUDIO_DATA {

public:
int Items,AllItems,CurrentPacket;
short *Data;
FILE *fd;
bool Show,Show1,Show2,Show3;

AUDIO_DATA();
~AUDIO_DATA();
bool open(UnicodeString filename);
bool read(int pos,int items);
void draw(int pos, TCanvas *canvas,int len);
short DataP(int n);     // Первая производная
short DataP2(int n);    // Вторая производная
short DataP3(int n);    // Третья производная

};
//------------------------------------------------------------------------
#define  NUMBER_IS_2_POW_K(x)   ((!((x)&((x)-1)))&&((x)>1))  // x is pow(2, k), k=1,2, ...
#define  FT_DIRECT        -1    // Direct transform.
#define  FT_INVERSE        1    // Inverse transform.
bool  FFT(double *Rdat, double *Idat, int N, int LogN, int Ft_Flag);

void Test_FFT();

void FFTAnalysis(double *AVal, double *FTvl, int Nvl, int Nft);
//------------------------------------------------------------------------
class FFT_RESULT {

public:
int N, // Кол-во точек по частоте
	T; // Кол-во точек по времени
double max;   // Максимальное значение
double *Data; // Данные [T*N]

FFT_RESULT();
~FFT_RESULT();
bool init(int n,int t);
bool Add(double *arr,int index);

};
//------------------------------------------------------------------------
#define SPECTR_ITEMS 512
struct SPECTR_SAMPLE {
	float Data[3][SPECTR_ITEMS];
};
//------------------------------------------------------------------------
class SPECTR_BASE_RESULT {

public:
	int Items,MaxItems;
	int *RecID;
	float *Delta;

	SPECTR_BASE_RESULT();
	~SPECTR_BASE_RESULT();
	void Init(int max_items);
	void Add(int rec_id,float delta);
	int FindPos(float delta);
	void Insert(int n,int rec_id,float delta);
};
//------------------------------------------------------------------------
class SPECTR_BASE {

public:
	int Items;
	bool LOADED;
	SPECTR_SAMPLE *Sample;
	SPECTR_BASE_RESULT *Result;

	SPECTR_BASE();
	~SPECTR_BASE();
	void init(int packets);
	void AddSample(AUDIO_DATA *adata,PACKETS *packets,int n);
	float Compare(float *sample,float *base);
	bool FindBestMatch(SPECTR_SAMPLE *sample);
};
//------------------------------------------------------------------------
class SPECTR_BASE_FOR_DETECT_PACKETS {

public:
	int Items,Current,Step,N;
	bool LOADED;
	float *Data,max;
    double *Prev;

	SPECTR_BASE_FOR_DETECT_PACKETS();
	~SPECTR_BASE_FOR_DETECT_PACKETS();
	void Init(AUDIO_DATA *adata);
	bool ReadNext(AUDIO_DATA *adata);
	float Get(int pos);
	bool Read(UnicodeString filename,ENVELOPE *env);
	void Draw(int pos,TCanvas *canvas);
};
//------------------------------------------------------------------------
// Пересчёт значений массива
// A[m*n] - входной массив
// B[m*n] - входной массив
// dm*dn - область для обработки каждого элемента
void RecalculateArray(double *A,double *B,int M,int N,int DM,int DN);
//------------------------------------------------------------------------
class COMPARE_FREQUENCES {

public:
	float IfZero=0.001;

	COMPARE_FREQUENCES();
	~COMPARE_FREQUENCES();
	void Correct(float *a,int items); // Коррекция значений частот
	double CountSum(float *a,int items); // Подсчёт суммы
	double Compare(float *a,float *b,int items); // Сравнение двух наборов частот
	double Compare3(float *a1,float *a2,float *a3,float *b1,float *b2,float *b3,int items);

	void CountDynamics(float *a1,float *a2,float *a3,int items,float *left,float *right);
	int CompareDynamics(float *left1,float *right1,float *left2,float *rtight2,int items);

private:
	float CompareItem(float a,float b);
};
//------------------------------------------------------------------------

