//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "common.h"
#include "Unit6.h"
#include "Unit1.h"
#include "Unit5.h"
#pragma package(smart_init)

extern FILENAMES Filenames;
extern PACKETS *Packets;
extern AUDIO_DATA *AudioData;
extern SPECTR_BASE *SpectrBase;
int I;

//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SPECTR_ANALYZER::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall SPECTR_ANALYZER::SPECTR_ANALYZER(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall SPECTR_ANALYZER::Execute()
{
	//---- Place thread code here ----
for (I=0;I<SpectrBase->Items;I++) {
	SpectrBase->AddSample(AudioData,Packets,I);
	Synchronize(&ShowStat);
}
SpectrBase->LOADED=true;
Synchronize(&ShowFinish);
}
//---------------------------------------------------------------------------
void __fastcall SPECTR_ANALYZER::ShowStat()
{
Form5->ProgressBar1->Position=I;
Form5->Label1->Caption="Обработано "+UnicodeString(I+1)+" из "
	+UnicodeString(SpectrBase->Items)+" звуковых пакетов";
}
//---------------------------------------------------------------------------
void __fastcall SPECTR_ANALYZER::ShowFinish()
{
ShowMessage("Обработка завершена!");
Form5->Close();
}
//---------------------------------------------------------------------------
