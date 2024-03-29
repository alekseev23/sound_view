//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class PHPExecutor : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall PHPExecutor(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
