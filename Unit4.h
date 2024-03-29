//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TPaintBox *PaintBox1;
	TStatusBar *StatusBar1;
	TPanel *Panel1;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TActionList *ActionList1;
	TAction *Draw;
	TAction *Calculate;
	TAction *DrawGraph;
	TImage *Image1;
	TSplitter *Splitter1;
	TPanel *Panel2;
	TGroupBox *GroupBox1;
	TTrackBar *TrackBar1;
	TGroupBox *GroupBox2;
	TTrackBar *TrackBar2;
	TGroupBox *GroupBox3;
	TTrackBar *TrackBar3;
	TGroupBox *GroupBox4;
	TTrackBar *TrackBar4;
	TBitBtn *BitBtn4;
	TTabControl *TabControl1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TAction *ShowPacket;
	void __fastcall DrawExecute(TObject *Sender);
	void __fastcall PaintBox1Paint(TObject *Sender);
	void __fastcall CalculateExecute(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall TabControl1Change(TObject *Sender);
	void __fastcall ShowPacketExecute(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall BitBtn4Click(TObject *Sender);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

private:	// User declarations
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
