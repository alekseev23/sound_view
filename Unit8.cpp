//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit8.h"
#include "Unit1.h"
#include "common.h"
#pragma package(smart_init)

extern SPECTR_BASE_FOR_DETECT_PACKETS *SpectrBaseChanges;
extern FILENAMES Filenames;
extern ENVELOPE *Envelope;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SPECTR_ANALYZER_FOR_DETECT_PACKETS::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall SPECTR_ANALYZER_FOR_DETECT_PACKETS::SPECTR_ANALYZER_FOR_DETECT_PACKETS(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall SPECTR_ANALYZER_FOR_DETECT_PACKETS::Execute()
{
	//---- Place thread code here ----
	SpectrBaseChanges->Read(Filenames.Dat,Envelope);
}
//---------------------------------------------------------------------------
