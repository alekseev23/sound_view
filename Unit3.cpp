//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit3.h"
#include "Unit2.h"
#include "Unit1.h"
#include "common.h"
#include "../_Common_/Lib/RunProcess.h"

#pragma package(smart_init)

extern UnicodeString CurPath,Command;
extern bool BUSY;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall PHPExecutor::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall PHPExecutor::PHPExecutor(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall PHPExecutor::Execute()
{
	//---- Place thread code here ----
	RunProcess(Command,CurPath);
    BUSY=false;
}
//---------------------------------------------------------------------------
