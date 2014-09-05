#include "Threading.h"

using namespace blib;

DWORD blib::GetThreadId(){
	DWORD result=0;
#ifdef WINDOWS
	result=GetCurrentThreadId();
#endif
	return result;
}
