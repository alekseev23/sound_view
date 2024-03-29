//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class SPECTR_ANALYZER : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall SPECTR_ANALYZER(bool CreateSuspended);
	void __fastcall ShowStat();
	void __fastcall ShowFinish();
};
//---------------------------------------------------------------------------
#endif
