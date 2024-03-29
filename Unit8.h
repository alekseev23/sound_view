//---------------------------------------------------------------------------

#ifndef Unit8H
#define Unit8H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class SPECTR_ANALYZER_FOR_DETECT_PACKETS : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall SPECTR_ANALYZER_FOR_DETECT_PACKETS(bool CreateSuspended);
	UnicodeString FileName;
};
//---------------------------------------------------------------------------
#endif
