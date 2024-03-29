//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include "Unit3.h"
#include "../_Common_/Lib/files.h"
#include "../_Common_/Lib/RunProcess.h"
#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
int STAGE;
extern bool BUSY;
extern UnicodeString SOX,PHP,SCRIPTS,CurPath,Command;
PHPExecutor *PHPExec;

extern FILENAMES Filenames;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
((TGIFImage*)Image1->Picture->Graphic)->Animate=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Action1Execute(TObject *Sender)
{ // �������� �����
Memo1->Clear();
STAGE=1;
BUSY=false;
Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Timer1Timer(TObject *Sender)
{
if (BUSY) return;
BUSY=true;
switch (STAGE) {
	case 1: // ���������� ��� �����, ��������� ������� DAT-�����
			Filenames.Audio=Form1->OpenDialog1->FileName;
			Filenames.BaseName=without_extension(Filenames.Audio);
			Filenames.Dat=Filenames.BaseName+".dat";
			Filenames.Envelope=Filenames.BaseName+".env";
			Filenames.Packets=Filenames.BaseName+".packets";
			Filenames.HistogramLen=Filenames.BaseName+".len-histogram.png";
			Filenames.HistogramPause=Filenames.BaseName+".pause-histogram.png";
			Filenames.HistogramMaxPos=Filenames.BaseName+".maxpos-histogram.png";
			// ��������� ������� DAT �����
			if (FileExists(Filenames.Dat)) {
				Memo1->Lines->Add("��������� ���� � �������: "+Filenames.Dat);
				BUSY=false;
			}
			else {
				Command=PHP+" \""+SCRIPTS+"convert.php\" \""+Filenames.Audio+"\" \""+Filenames.Dat+"\"";
				Memo1->Lines->Add("�������� ����� � �������: "+Filenames.Dat);
				//RunProcess(Command,CurPath);
				PHPExec=new PHPExecutor(false);
			}
			break;
	case 2: // ������� ���������
			// ��������� ������� ENV �����
			if (FileExists(Filenames.Envelope)) {
				Memo1->Lines->Add("��������� ���� � ���������: "+Filenames.Envelope);
				BUSY=false;
			}
			else {
				Command=PHP+" \""+SCRIPTS+"get_envelope.php\" -type=1 \""+Filenames.Dat+"\" \""+Filenames.Envelope+"\"";
				Memo1->Lines->Add("�������� ����� � ���������: "+Filenames.Envelope);
				//RunProcess(Command,CurPath);
				PHPExec=new PHPExecutor(false);
			}
			break;
	case 3: // ������� ������
			// ��������� ������� PACKETS �����
			if (FileExists(Filenames.Packets)) {
				Memo1->Lines->Add("��������� ���� � ��������: "+Filenames.Packets);
				BUSY=false;
			}
			else {
				Command=PHP+" \""+SCRIPTS+"get_packets.php\" \""+Filenames.Dat+"\" \""+Filenames.Packets+"\"";
				Memo1->Lines->Add("�������� ����� � ��������: "+Filenames.Packets);
				//RunProcess(Command,CurPath);
				PHPExec=new PHPExecutor(false);
			}
			break;
	case 4: // ������ �����������
			// ��������� ������� ����������
			if (FileExists(Filenames.HistogramLen)&&FileExists(Filenames.HistogramPause)&&FileExists(Filenames.HistogramMaxPos)) {
				Memo1->Lines->Add("��������� ���� � ������������: "+Filenames.HistogramLen);
				Memo1->Lines->Add("��������� ���� � ������������: "+Filenames.HistogramPause);
				Memo1->Lines->Add("��������� ���� � ������������: "+Filenames.HistogramMaxPos);
			}
			else {
				Command=PHP+" \""+SCRIPTS+"draw_packets_histogram.php\" \""+Filenames.Packets+"\"";
				Memo1->Lines->Add("�������� ����� � ������������: "+Filenames.HistogramLen);
				Memo1->Lines->Add("�������� ����� � ������������: "+Filenames.HistogramPause);
				Memo1->Lines->Add("�������� ����� � ������������: "+Filenames.HistogramMaxPos);
				//RunProcess(command,CurPath);
				PHPExec=new PHPExecutor(false);
			}
			BUSY=false;
			break;
	case 5: // ��������� ������
			Timer1->Enabled=false;
			Form1->Caption="Sound View - "+Form1->OpenDialog1->FileName;
			Form2->Close();
			BUSY=false;
			break;
}
STAGE++;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormShow(TObject *Sender)
{
Action1Execute(this);
}
//---------------------------------------------------------------------------
