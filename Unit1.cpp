//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "Unit7.h"
#include "Unit8.h"
#include "common.h"
#include "../_Common_/Lib/bitmap.h"
#include "../_Common_/Lib/strings.h"
#include <mmsystem.h>
#include "bass.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
UnicodeString CurPath,Command,
	SOX="X:\\Soft\\sox-14.4.2\\sox.exe",
	PHP="c:\\php\\php.exe",
	SCRIPTS="X:\\Work\\CPP\\2023\\Sound\\scripts\\";
bool BUSY=false,LOADED=false;
FILENAMES Filenames;
ENVELOPE *Envelope;
PACKETS *Packets;
AUDIO_DATA *AudioData,*AudioDataSpectre;
FFT_RESULT *TTFRes;
SPECTR_ANALYZER *SpectrAnalyzer;
SPECTR_ANALYZER_FOR_DETECT_PACKETS *SpectrAnalyzerForPackets;
SPECTR_BASE *SpectrBase;
SPECTR_BASE_FOR_DETECT_PACKETS *SpectrBaseChanges;
int AudioDataPos,PlayTime=500,PaintBox1_X,PaintBox1_Y;
HWND win=NULL;
HSTREAM fn=0;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{// ������� �������
CurPath=ExtractFileDir(Application->ExeName);
Envelope=new ENVELOPE;
Packets=new PACKETS;
AudioData=new AUDIO_DATA;
AudioDataSpectre=new AUDIO_DATA;
TTFRes=new FFT_RESULT;
SpectrBase=new SPECTR_BASE;
SpectrBaseChanges=new SPECTR_BASE_FOR_DETECT_PACKETS;
// ������������� �����
if (!BASS_Init(-1,44100,0,win,NULL)) {
	// ���� �� ������� ���������������� ����
	if (!BASS_Init(-2,44100,0,win,NULL)) ShowMessage("Oblom!");
}
// ���� �� �����, ��� ����� ���r� �� ��������
BASS_Start();
BASS_SetVolume(1.);
TrackBar1Change(this);
TrackBar2Change(this);
PageControl1Change(this);
// ������� �������
StringGrid1->Cells[0][0]="�";
StringGrid1->Cells[1][0]="�������";
StringGrid1->Cells[2][0]="�����";
StringGrid1->Cells[3][0]="���. �����";
StringGrid1->Cells[4][0]="���������";
StringGrid1->Cells[5][0]="���. ���������";      StringGrid1->ColWidths[5]=100;
StringGrid1->Cells[6][0]="���. ���������";      StringGrid1->ColWidths[6]=100;
StringGrid1->Cells[7][0]="������� ���������";   StringGrid1->ColWidths[7]=110;
StringGrid1->Cells[8][0]="����� ��";
StringGrid1->Cells[9][0]="���. ����� ��";       StringGrid1->ColWidths[9]=100;
StringGrid1->Cells[10][0]="����� �����";        StringGrid1->ColWidths[10]=100;
StringGrid1->Cells[11][0]="���. ����� �����";   StringGrid1->ColWidths[11]=100;
// ������� ������� �������
StringGrid2->Cells[0][0]="�";
StringGrid2->Cells[1][0]="�������";
StringGrid2->Cells[2][0]="� ������";
StringGrid2->Cells[3][0]="�������";
StringGrid2->Cells[4][0]="�����";
StringGrid2->Cells[5][0]="���. �����";
StringGrid2->Cells[6][0]="���������";
StringGrid2->Cells[7][0]="���. ���������";      StringGrid2->ColWidths[7]=100;
StringGrid2->Cells[8][0]="���. ���������";      StringGrid2->ColWidths[8]=100;
StringGrid2->Cells[9][0]="������� ���������";   StringGrid2->ColWidths[9]=110;
StringGrid2->Cells[10][0]="����� ��";
StringGrid2->Cells[11][0]="���. ����� ��";       StringGrid2->ColWidths[11]=100;
StringGrid2->Cells[12][0]="����� �����";        StringGrid2->ColWidths[12]=100;
StringGrid2->Cells[13][0]="���. ����� �����";   StringGrid2->ColWidths[13]=100;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{ // �������
int i,j;
if (OpenDialog1->Execute()) {
	Form1->Caption="Sound View";
	Form2->ShowModal();
	// ������ �����������
	read_bitmap(Image1->Picture->Bitmap,Filenames.HistogramLen);
	Image1->Width=Image1->Picture->Bitmap->Width;
	Image1->Height=Image1->Picture->Bitmap->Height;
	//
	read_bitmap(Image2->Picture->Bitmap,Filenames.HistogramPause);
	Image2->Width=Image2->Picture->Bitmap->Width;
	Image2->Height=Image2->Picture->Bitmap->Height;
	//
	read_bitmap(Image3->Picture->Bitmap,Filenames.HistogramMaxPos);
	Image3->Width=Image3->Picture->Bitmap->Width;
	Image3->Height=Image3->Picture->Bitmap->Height;
	// ������ ���������
	Envelope->read(Filenames.Envelope);
	ScrollBar1->Max=Envelope->Items;
	ScrollBar1->Position=0;
	Envelope->draw(ScrollBar1->Position,PaintBox1->Canvas);
	// ������ ������ �� ������ �������
	Packets->read(Filenames.Packets);
	Packets->draw(ScrollBar1->Position,PaintBox1->Canvas);
	//
	ScrollBar2->Max=Packets->Items;
	ScrollBar2->Position=0;
	Packets->drawRel(ScrollBar2->Position,PaintBox2->Canvas);
	// ��������� ������� � ��������
	StringGrid1->RowCount=Packets->Items+1;
	for (i=0;i<Packets->Items;i++) {
		j=i+1;
		StringGrid1->Cells[0][j]=j;
		StringGrid1->Cells[1][j]=Packets->Data[i].Pos;
		StringGrid1->Cells[2][j]=Packets->Data[i].Len;
		StringGrid1->Cells[3][j]=Packets->Data[i].LenRel;
		StringGrid1->Cells[4][j]=Packets->Data[i].Amp;
		StringGrid1->Cells[5][j]=Packets->Data[i].AmpRel;
		StringGrid1->Cells[6][j]=Packets->Data[i].AmpMin;
		StringGrid1->Cells[7][j]=Packets->Data[i].MaxPos;
		StringGrid1->Cells[8][j]=Packets->Data[i].LeftPause;
		StringGrid1->Cells[9][j]=Packets->Data[i].LeftPauseRel;
		StringGrid1->Cells[10][j]=Packets->Data[i].RightPause;
		StringGrid1->Cells[11][j]=Packets->Data[i].RightPauseRel;
	}
	// ������ �������� ������
	AudioData->open(Filenames.Dat);
	AudioDataSpectre->open(Filenames.Dat);
	Timer1->Enabled=true;
	//
	/*SpectrAnalyzerForPackets=new SPECTR_ANALYZER_FOR_DETECT_PACKETS(true);
	SpectrAnalyzerForPackets->FileName=Filenames.Dat;
	SpectrAnalyzerForPackets->Execute();*/
    SpectrAnalyzerForPackets=new SPECTR_ANALYZER_FOR_DETECT_PACKETS(false);
	// ������� ����������
	LOADED=true;
	StatusBar1->Panels[0].Items[0]->Text="�����������������: "+GetTimeForMovieRus_double(0.01*Envelope->Items);
	StatusBar2->Panels[0].Items[0]->Text="����� �������: "+UnicodeString(Packets->Items);
	if (fn!=0) {
		// ������������� �����
		BASS_ChannelStop(fn);
		// ��������� �����
		BASS_StreamFree(fn);
	}
	// ������ �����
	fn=BASS_StreamCreateFile(false,OpenDialog1->FileName.w_str(),0,0,BASS_MP3_SETPOS|BASS_UNICODE);
    if (fn==0) ShowMessage("fn=0 "+UnicodeString(OpenDialog1->FileName.c_str()));
	// ������ �����
	//BASS_ChannelPlay(fn, false);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N5Click(TObject *Sender)
{ // �����
Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{
if (!LOADED) return;
Envelope->draw(ScrollBar1->Position,PaintBox1->Canvas);
SpectrBaseChanges->Draw(ScrollBar1->Position,PaintBox1->Canvas);
Packets->draw(ScrollBar1->Position,PaintBox1->Canvas);
StatusBar1->Panels[0].Items[1]->Text="�������: "+GetTimeForMovieRus_double(0.01*ScrollBar1->Position);
// �������� ������ � ���������
Timer1->Enabled=false;
Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar2Change(TObject *Sender)
{
if (!LOADED) return;
Packets->drawRel(ScrollBar2->Position,PaintBox2->Canvas);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox1Paint(TObject *Sender)
{
ScrollBar1Change(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox2Paint(TObject *Sender)
{
ScrollBar2Change(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
if (!LOADED) return;
if ((PaintBox1_X==X)&&(PaintBox1_Y==Y)) return;
StatusBar1->Panels[0].Items[1]->Text="�������: "+GetTimeForMovieRus_double(0.01*(ScrollBar1->Position+X));
AudioData->draw(X*480,PaintBox1->Canvas,TrackBar2->Position/10);
PaintBox1_X=X;
PaintBox1_Y=Y;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox2MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
if (!LOADED) return;
int packet;
packet=ScrollBar2->Position+(X/Packets->BoxSize);
if (packet>=Packets->Items) packet=Packets->Items-1;
StatusBar2->Panels[0].Items[0]->Text="����� "+UnicodeString(packet)+" �� "+UnicodeString(Packets->Items);
StatusBar2->Panels[0].Items[1]->Text="��������� �� "+UnicodeString(int(100*Packets->Data[packet].AmpMin/32768))
	+"% �� "+UnicodeString(int(100*Packets->Data[packet].Amp/32768))+"%";
StatusBar2->Panels[0].Items[2]->Text="����� "+UnicodeString(10*Packets->Data[packet].Len)+" ��";
StatusBar2->Panels[0].Items[3]->Text="�����: ��="+UnicodeString(10*Packets->Data[packet].LeftPause)
	+" ��, �����="+UnicodeString(Packets->Data[packet].RightPause)+" ��";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
AudioData->read(ScrollBar1->Position*480,PaintBox1->Width*480);
Timer1->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
if (!LOADED) return;
int pos,len;
pos=ScrollBar1->Position+X;
len=Envelope->Items;
BASS_ChannelSetPosition(fn,BASS_ChannelGetLength(fn,BASS_POS_BYTE)*pos/len,BASS_POS_BYTE);
BASS_ChannelPlay(fn,false);
Timer2->Interval=PlayTime;
Timer2->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{ // ������������� �����
Timer2->Enabled=false;
BASS_ChannelStop(fn);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
BASS_SetVolume(0.01*TrackBar1->Position);
Edit1->Text=UnicodeString(TrackBar1->Position)+" %";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
PlayTime=TrackBar2->Position;
Edit2->Text=UnicodeString(TrackBar2->Position)+" ��";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
if (!LOADED) return;
int packet,pos,len;
packet=ScrollBar2->Position+(X/Packets->BoxSize);
if (packet>=Packets->Items) packet=Packets->Items-1;
pos=Packets->Data[packet].Pos;
len=Envelope->Items;
BASS_ChannelSetPosition(fn,BASS_ChannelGetLength(fn,BASS_POS_BYTE)*pos/len,BASS_POS_BYTE);
BASS_ChannelPlay(fn,false);
if (Shift.Contains(ssShift)) Timer2->Interval=Packets->Data[packet].Len;
else Timer2->Interval=PlayTime;
Timer2->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PageControl1Change(TObject *Sender)
{
StatusBar1->Visible=false;
StatusBar2->Visible=false;
StatusBar3->Visible=false;
StatusBar4->Visible=false;
StatusBar5->Visible=false;
switch (PageControl1->ActivePageIndex) {
	case 0: StatusBar1->Visible=true; StatusBar1->Top=Form1->Height; break;
	case 1: StatusBar2->Visible=true; StatusBar2->Top=Form1->Height; break;
	case 2: StatusBar3->Visible=true; StatusBar3->Top=Form1->Height; break;
	case 3: StatusBar4->Visible=true; StatusBar4->Top=Form1->Height;
			PageControl2->Align=alClient;
			break;
	case 4: StatusBar5->Visible=true; StatusBar5->Top=Form1->Height; break;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1Click(TObject *Sender)
{
if (!LOADED) return;
int packet,pos,len;
packet=StringGrid1->Row-1;
if (packet>=Packets->Items) packet=Packets->Items-1;
pos=Packets->Data[packet].Pos-Packets->Data[packet].LeftPause;
len=Packets->Data[packet].Len+Packets->Data[packet].LeftPause+Packets->Data[packet].RightPause;
BASS_ChannelSetPosition(fn,BASS_ChannelGetLength(fn,BASS_POS_BYTE)*pos/Envelope->Items,BASS_POS_BYTE);
BASS_ChannelPlay(fn,false);
Timer2->Interval=10*len;
Timer2->Enabled=true;
//
AudioDataSpectre->CurrentPacket=packet;
// ��������� �����
if (!Form4->Visible) Form4->Show();
// ������ ����������
Form4->ShowPacketExecute(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{ // ������� ���� �������� ���� �������
if (!LOADED) return;
SpectrBase->init(Packets->Items);
SpectrAnalyzer=new SPECTR_ANALYZER(false);
Form5->ProgressBar1->Position=0;
Form5->ProgressBar1->Max=Packets->Items;
Form5->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{ // ����� ������� �������
int i,j,packet;
if (!LOADED) return;
if (!SpectrBase->LOADED) return;
PageControl1->ActivePageIndex=4;
packet=StringGrid1->Row-1;
SpectrBase->FindBestMatch(&SpectrBase->Sample[packet]);
// ���������� � ������� ������
StringGrid2->Cells[0][1]="";
StringGrid2->Cells[1][1]="";
for (i=0;i<StringGrid1->ColCount;i++) {
	StringGrid2->Cells[2+i][1]=StringGrid1->Cells[i][packet+1];
}
// ���������� � ��������� �������
for (j=0;j<SpectrBase->Result->Items;j++) {
	StringGrid2->Cells[0][j+2]=(j+1);
	StringGrid2->Cells[1][j+2]=SpectrBase->Result->Delta[j];
	packet=SpectrBase->Result->RecID[j];
	for (i=0;i<StringGrid1->ColCount;i++) {
		StringGrid2->Cells[2+i][j+2]=StringGrid1->Cells[i][packet+1];
	}
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid2Click(TObject *Sender)
{ //
if (!LOADED) return;
if (!SpectrBase->LOADED) return;
PaintBox3Paint(this);
int packet,pos,len;
packet=StringGrid2->Cells[2][StringGrid2->Row].ToIntDef(0);
if (packet>=Packets->Items) packet=Packets->Items-1;
pos=Packets->Data[packet].Pos-Packets->Data[packet].LeftPause;
len=Packets->Data[packet].Len+Packets->Data[packet].LeftPause+Packets->Data[packet].RightPause;
BASS_ChannelSetPosition(fn,BASS_ChannelGetLength(fn,BASS_POS_BYTE)*pos/Envelope->Items,BASS_POS_BYTE);
BASS_ChannelPlay(fn,false);
Timer2->Interval=10*len;
Timer2->Enabled=true;
//
AudioDataSpectre->CurrentPacket=packet;
// ��������� �����
if (!Form4->Visible) Form4->Show();
// ������ ����������
Form4->ShowPacketExecute(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox3Paint(TObject *Sender)
{
int sx,sy,i,j,k,l,packet1,packet2;
double dx,dy,x,y,max=0.,sum1=0.,sum2=0.;
if (!LOADED) return;
if (!SpectrBase->LOADED) return;
// ������
k=StringGrid2->Row;
if (k<1) k=1;
packet1=StringGrid2->Cells[2][1].ToIntDef(0);
packet2=StringGrid2->Cells[2][k].ToIntDef(0);
// ������� ��������
for (j=0;j<3;j++) {
	for (i=0;i<SPECTR_ITEMS;i++) {
		if (SpectrBase->Sample[packet1].Data[j][i]>max) {
			max=SpectrBase->Sample[packet1].Data[j][i];
		}
		sum1+=SpectrBase->Sample[packet1].Data[j][i];
		if (SpectrBase->Sample[packet2].Data[j][i]>max) {
			max=SpectrBase->Sample[packet2].Data[j][i];
		}
		sum2+=SpectrBase->Sample[packet1].Data[j][i];
	}
}
// ������� ����
sx=PaintBox3->Width;
sy=PaintBox3->Height;
PaintBox3->Canvas->Brush->Color=clWhite;
PaintBox3->Canvas->FillRect(TRect(0,0,sx,sy));
//
dx=1.*sx/SPECTR_ITEMS;
dy=1.*sy/max;
for (i=1;i<SPECTR_ITEMS;i++) {
	// ��������� ����� �������
	PaintBox3->Canvas->Pen->Color=TColor(180);
	PaintBox3->Canvas->MoveTo(dx*(i-1),1.*sy-dy*SpectrBase->Sample[packet1].Data[0][i-1]);
	PaintBox3->Canvas->LineTo(dx*i,1.*sy-dy*SpectrBase->Sample[packet1].Data[0][i]);
	// ��������� ����� ������� �����
	PaintBox3->Canvas->Pen->Color=TColor(250);
	PaintBox3->Canvas->MoveTo(dx*(i-1),1.*sy-dy*SpectrBase->Sample[packet2].Data[0][i-1]);
	PaintBox3->Canvas->LineTo(dx*i,1.*sy-dy*SpectrBase->Sample[packet2].Data[0][i]);
	// ������� ����� �������
	PaintBox3->Canvas->Pen->Color=TColor(180<<8);
	PaintBox3->Canvas->MoveTo(dx*(i-1),1.*sy-dy*SpectrBase->Sample[packet1].Data[1][i-1]);
	PaintBox3->Canvas->LineTo(dx*i,1.*sy-dy*SpectrBase->Sample[packet1].Data[1][i]);
	// ������� ����� ������� �����
	PaintBox3->Canvas->Pen->Color=TColor(250<<8);
	PaintBox3->Canvas->MoveTo(dx*(i-1),1.*sy-dy*SpectrBase->Sample[packet2].Data[1][i-1]);
	PaintBox3->Canvas->LineTo(dx*i,1.*sy-dy*SpectrBase->Sample[packet2].Data[1][i]);
	// �������� ����� �������
	PaintBox3->Canvas->Pen->Color=TColor(180<<16);
	PaintBox3->Canvas->MoveTo(dx*(i-1),1.*sy-dy*SpectrBase->Sample[packet1].Data[2][i-1]);
	PaintBox3->Canvas->LineTo(dx*i,1.*sy-dy*SpectrBase->Sample[packet1].Data[2][i]);
	// �������� ����� ������� �����
	PaintBox3->Canvas->Pen->Color=TColor(250<<16);
	PaintBox3->Canvas->MoveTo(dx*(i-1),1.*sy-dy*SpectrBase->Sample[packet2].Data[2][i-1]);
	PaintBox3->Canvas->LineTo(dx*i,1.*sy-dy*SpectrBase->Sample[packet2].Data[2][i]);
}
StatusBar5->Panels[0].Items[0]->Text="����� 3 �������� �������: "+UnicodeString(sum1);
StatusBar5->Panels[0].Items[1]->Text="����� 3 �������� �������� ������: "+UnicodeString(sum1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N12Click(TObject *Sender)
{ // �������� ��
N7->Checked=true;
N8->Checked=true;
N9->Checked=true;
N10->Checked=true;
AudioData->Show=true;
AudioData->Show1=true;
AudioData->Show2=true;
AudioData->Show3=true;
AudioData->draw(PaintBox1_X*480,PaintBox1->Canvas,TrackBar2->Position/10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N13Click(TObject *Sender)
{ // ������ ��
N7->Checked=false;
N8->Checked=false;
N9->Checked=false;
N10->Checked=false;
AudioData->Show=false;
AudioData->Show1=false;
AudioData->Show2=false;
AudioData->Show3=false;
AudioData->draw(PaintBox1_X*480,PaintBox1->Canvas,TrackBar2->Position/10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N7Click(TObject *Sender)
{ // �������� ������
AudioData->Show=N7->Checked;
AudioData->draw(PaintBox1_X*480,PaintBox1->Canvas,TrackBar2->Position/10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N8Click(TObject *Sender)
{ // ������ �����������
AudioData->Show1=N8->Checked;
AudioData->draw(PaintBox1_X*480,PaintBox1->Canvas,TrackBar2->Position/10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N9Click(TObject *Sender)
{ // ������ �����������
AudioData->Show2=N9->Checked;
AudioData->draw(PaintBox1_X*480,PaintBox1->Canvas,TrackBar2->Position/10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N10Click(TObject *Sender)
{ // ������ �����������
AudioData->Show3=N10->Checked;
AudioData->draw(PaintBox1_X*480,PaintBox1->Canvas,TrackBar2->Position/10);
}
//---------------------------------------------------------------------------

