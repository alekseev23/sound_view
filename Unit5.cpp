//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
((TGIFImage*)Image1->Picture->Graphic)->Animate=true;

}
//---------------------------------------------------------------------------
void __fastcall TForm5::BitBtn1Click(TObject *Sender)
{
Form5->Close();
}
//---------------------------------------------------------------------------
