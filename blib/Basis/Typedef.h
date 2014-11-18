#ifndef BLIB_TYPEDEF_H
#define BLIB_TYPEDEF_H

#include <map>

#if (!defined(_WINDOWS) && !defined(WIN32) && !defined(__unix__))
#define _WINDOWS 1
#endif

#if (defined(_WINDOWS) || defined(WIN32))

#define WINDOWS 1

#ifndef _MSC_VER
#define NO_VISUAL_STUDIO
#include <stdint.h>
#endif

#include <windows.h>

#ifdef BLIB_DLL
#define BLIB_LIB_API  __declspec(dllexport) 
#elif defined BLIB_DLL_IMPORT
#define BLIB_LIB_API  __declspec(dllimport) 
#else
#define BLIB_LIB_API
#endif

#ifndef _STDINT_H
  typedef __int8 int8_t;
  typedef unsigned __int8 uint8_t;
  typedef __int16 int16_t;
  typedef unsigned __int16 uint16_t;
  typedef __int32 int32_t;
  typedef unsigned __int32 uint32_t;
  typedef __int64 int64_t;
  typedef unsigned __int64 uint64_t;
#endif

  typedef signed long long_t;
  typedef unsigned long ulong_t;
  typedef int64_t llong_t;
  typedef uint64_t ullong_t;

  typedef float float32_t;
  typedef double float64_t;
  typedef long double lfloat64_t;
  typedef ulong_t threadId_t;

#ifdef NO_VISUAL_STUDIO
  #define _strtoui64(a,b,c) strtoull(a,b,c)
#endif

#endif

#if defined __unix__

//#ifdef BLIB_DLL
//#define BLIB_LIB_API  __declspec(dllexport) 
//#elif defined BLIB_LIB
#define BLIB_LIB_API
//#else
//#define BLIB_LIB_API __declspec(dllimport)  
//#endif

  #define LINUX 1

  #include <stdint.h>   //might need to be cstdint.h
  #include <pthread.h>
  #include <signal.h>
  #include <unistd.h>

	#define INFINITE            0xFFFFFFFF
	
  typedef signed long long_t;
  typedef unsigned long ulong_t;
  typedef int64_t llong_t;
  typedef uint64_t ullong_t;

  typedef float float32_t;
  typedef double float64_t;
  typedef long double lfloat64_t;
  
  typedef uint32_t DWORD;
  typedef pthread_t threadId_t;

#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef char char_t;

namespace blib{

typedef struct{
	union{
		uint8_t u_value;
		int8_t value;
		char_t c[1];
	};
}union8_t;

typedef struct{
	union{
		uint16_t u_value;
	  int16_t value;
		char_t c[2];
	};
}union16_t;

typedef struct{
	union{
		uint32_t u_value;
	  int32_t value;
		float32_t f_value;
		char_t c[4];
	};
}union32_t;

typedef struct{
	union{
		uint64_t u_value;
	  int64_t value;
		float64_t f_value;
		char_t c[8];
	};
}union64_t;

typedef enum{
	UNKNOWN_T,
	BOOL_T,
  CHAR_T,
  INT8_T,
	UINT8_T,
	INT16_T,
	UINT16_T,
	INT32_T,
	UINT32_T,
	INT64_T,
	UINT64_T,
	LONG_T,
	ULONG_T,
	LLONG_T,
	ULLONG_T,
	FLOAT32_T,
	FLOAT64_T,
	LFLOAT64_T,
	STRING_T,
	VOID_T,
  PBOOL_T,
	PCHAR_T,
	PINT8_T,
	PUINT8_T,
	PINT16_T,
	PUINT16_T,
	PINT32_T,
	PUINT32_T,
	PINT64_T,
	PUINT64_T,
	PLONG_T,
	PULONG_T,
	PLLONG_T,
	PULLONG_T,
	PFLOAT32_T,
	PFLOAT64_T,
	PLFLOAT64_T,
	PSTRING_T,
	PVOID_T,
} EnumVar_t;

typedef enum{
  FAIL=FALSE,
	SUCCESS=TRUE
} EnumResult_t;

BLIB_LIB_API std::multimap<EnumVar_t,size_t>& GetVarHashMap();
BLIB_LIB_API std::multimap<size_t,EnumVar_t>& GetHashVarMap();
BLIB_LIB_API std::multimap<EnumVar_t,const std::type_info*>& GetVarTypeInfoMap();
BLIB_LIB_API std::multimap<const std::type_info*,EnumVar_t>& GetTypeInfoVarMap();

BLIB_LIB_API size_t GetHash(EnumVar_t type);
BLIB_LIB_API size_t GetHash(const std::type_info* type);

BLIB_LIB_API EnumVar_t GetEnumVar(size_t hash);
BLIB_LIB_API EnumVar_t GetEnumVar(const std::type_info* type);

BLIB_LIB_API const std::type_info* GetTypeInfo(EnumVar_t type);
BLIB_LIB_API const std::type_info* GetTypeInfo(size_t hash);

BLIB_LIB_API size_t GetSize(const std::type_info* type);
BLIB_LIB_API size_t GetSize(const EnumVar_t type);
BLIB_LIB_API size_t GetSize(const size_t hash);

BLIB_LIB_API EnumResult_t InitTypeMaps();

};

#endif
