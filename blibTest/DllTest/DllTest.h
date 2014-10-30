#ifdef BLIB_DLL
#define BLIBDLL_API __declspec(dllexport) 
#elif defined _LIB
#define BLIBDLL_API
#else
#define BLIBDLL_API __declspec(dllimport) 
#endif
