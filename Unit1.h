//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TOpenDialog *OpenDialog1;
	TStatusBar *StatusBar1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TPaintBox *PaintBox1;
	TPaintBox *PaintBox2;
	TPanel *Panel1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TTabSheet *TabSheet4;
	TPageControl *PageControl2;
	TTabSheet *TabSheet5;
	TTabSheet *TabSheet6;
	TTabSheet *TabSheet7;
	TScrollBox *ScrollBox1;
	TImage *Image1;
	TScrollBox *ScrollBox2;
	TImage *Image2;
	TScrollBox *ScrollBox3;
	TImage *Image3;
	TScrollBar *ScrollBar1;
	TTimer *Timer1;
	TScrollBar *ScrollBar2;
	TTimer *Timer2;
	TTrackBar *TrackBar1;
	TTrackBar *TrackBar2;
	TPanel *Panel2;
	TGroupBox *GroupBox1;
	TEdit *Edit1;
	TGroupBox *GroupBox2;
	TEdit *Edit2;
	TTimer *Timer3;
	TStatusBar *StatusBar2;
	TStringGrid *StringGrid1;
	TStatusBar *StatusBar3;
	TStatusBar *StatusBar4;
	TTabSheet *TabSheet8;
	TGroupBox *GroupBox3;
	TStringGrid *StringGrid2;
	TPaintBox *PaintBox3;
	TStatusBar *StatusBar5;
	TPanel *Panel3;
	TBitBtn *BitBtn1;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall PaintBox1Paint(TObject *Sender);
	void __fastcall PaintBox1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ScrollBar2Change(TObject *Sender);
	void __fastcall PaintBox2Paint(TObject *Sender);
	void __fastcall PaintBox2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall PaintBox1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall TrackBar2Change(TObject *Sender);
	void __fastcall PaintBox2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall StringGrid1Click(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall StringGrid2Click(TObject *Sender);
	void __fastcall PaintBox3Paint(TObject *Sender);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);



private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
