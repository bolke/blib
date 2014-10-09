#include <map>
#include <algorithm>

#include "Basis.h"
#include "Typedef.h"

using namespace blib;

static std::multimap<EnumVar_t,size_t> varHashMap;
static std::multimap<size_t,EnumVar_t> hashVarMap;
static std::multimap<EnumVar_t,const std::type_info*> varTypeInfoMap;
static std::multimap<const std::type_info*,EnumVar_t> typeInfoVarMap;

std::multimap<EnumVar_t,size_t>& blib::GetVarHashMap(){
	std::multimap<EnumVar_t,size_t>* result=&varHashMap;
	if(result->size()==0){
		(*result).insert(std::pair<EnumVar_t,size_t>(UNKNOWN_T,0));
    (*result).insert(std::pair<EnumVar_t,size_t>(BOOL_T,GetHashCode(&typeid(bool))));
    (*result).insert(std::pair<EnumVar_t,size_t>(CHAR_T,GetHashCode(&typeid(char_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(INT8_T,GetHashCode(&typeid(int8_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(UINT8_T,GetHashCode(&typeid(uint8_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(INT16_T,GetHashCode(&typeid(int16_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(UINT16_T,GetHashCode(&typeid(uint16_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(INT32_T,GetHashCode(&typeid(int32_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(UINT32_T,GetHashCode(&typeid(uint32_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(INT64_T,GetHashCode(&typeid(int64_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(UINT64_T,GetHashCode(&typeid(uint64_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(LONG_T,GetHashCode(&typeid(long_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(ULONG_T,GetHashCode(&typeid(ulong_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(LLONG_T,GetHashCode(&typeid(llong_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(ULLONG_T,GetHashCode(&typeid(ullong_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(FLOAT32_T,GetHashCode(&typeid(float32_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(FLOAT64_T,GetHashCode(&typeid(float64_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(LFLOAT64_T,GetHashCode(&typeid(lfloat64_t))));
		(*result).insert(std::pair<EnumVar_t,size_t>(STRING_T,GetHashCode(&typeid(std::string))));
		(*result).insert(std::pair<EnumVar_t,size_t>(VOID_T,GetHashCode(&typeid(void))));	
    (*result).insert(std::pair<EnumVar_t,size_t>(PBOOL_T,GetHashCode(&typeid(bool*))));
    (*result).insert(std::pair<EnumVar_t,size_t>(PCHAR_T,GetHashCode(&typeid(char_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PINT8_T,GetHashCode(&typeid(int8_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PUINT8_T,GetHashCode(&typeid(uint8_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PINT16_T,GetHashCode(&typeid(int16_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PUINT16_T,GetHashCode(&typeid(uint16_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PINT32_T,GetHashCode(&typeid(int32_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PUINT32_T,GetHashCode(&typeid(uint32_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PINT64_T,GetHashCode(&typeid(int64_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PUINT64_T,GetHashCode(&typeid(uint64_t*))));	
		(*result).insert(std::pair<EnumVar_t,size_t>(PLONG_T,GetHashCode(&typeid(long_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PULONG_T,GetHashCode(&typeid(ulong_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PLLONG_T,GetHashCode(&typeid(llong_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PULLONG_T,GetHashCode(&typeid(ullong_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PFLOAT32_T,GetHashCode(&typeid(float32_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PFLOAT64_T,GetHashCode(&typeid(float64_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PLFLOAT64_T,GetHashCode(&typeid(lfloat64_t*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PSTRING_T,GetHashCode(&typeid(std::string*))));
		(*result).insert(std::pair<EnumVar_t,size_t>(PVOID_T,GetHashCode(&typeid(void*))));
	}
	return *result;
}

std::multimap<size_t,EnumVar_t>& blib::GetHashVarMap(){
	std::multimap<size_t,EnumVar_t>* result=&hashVarMap;
	if(result->size()==0){
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(0)),UNKNOWN_T));
    (*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(bool)),BOOL_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(char_t)),CHAR_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(int8_t)),INT8_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(uint8_t)),UINT8_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(int16_t)),INT16_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(uint16_t)),UINT16_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(int32_t)),INT32_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(uint32_t)),UINT32_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(int64_t)),INT64_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(uint64_t)),UINT64_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(long_t)),LONG_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(ulong_t)),ULONG_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(llong_t)),LLONG_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(ullong_t)),ULLONG_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(float32_t)),FLOAT32_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(float64_t)),FLOAT64_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(lfloat64_t)),LFLOAT64_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(std::string)),STRING_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(void)),VOID_T));
    (*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(bool*)),PBOOL_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(char_t*)),PCHAR_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(int8_t*)),PINT8_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(uint8_t*)),PUINT8_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(int16_t*)),PINT16_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(uint16_t*)),PUINT32_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(int32_t*)),PINT32_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(uint32_t*)),PUINT32_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(int64_t*)),PINT64_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(uint64_t*)),PUINT64_T));	
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(long_t*)),PLONG_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(ulong_t*)),PULONG_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(llong_t*)),PLLONG_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(ullong_t*)),PULLONG_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(float32_t*)),PFLOAT32_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(float64_t*)),PFLOAT64_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(lfloat64_t*)),PLFLOAT64_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(std::string*)),PSTRING_T));
		(*result).insert(std::pair<size_t,EnumVar_t>(GetHashCode(&typeid(void*)),PVOID_T));
	};
	return *result;
}

std::multimap<EnumVar_t,const std::type_info*>& blib::GetVarTypeInfoMap(){
	std::multimap<EnumVar_t,const std::type_info*>* result=&varTypeInfoMap;
	if(result->size()==0){
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(UNKNOWN_T,&typeid(void)));
    (*result).insert(std::pair<EnumVar_t,const std::type_info*>(BOOL_T,&typeid(bool)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(CHAR_T,&typeid(char_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(INT8_T,&typeid(int8_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(UINT8_T,&typeid(uint8_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(INT16_T,&typeid(int16_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(UINT16_T,&typeid(uint16_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(INT32_T,&typeid(int32_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(UINT32_T,&typeid(uint32_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(INT64_T,&typeid(int64_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(UINT64_T,&typeid(uint64_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(LONG_T,&typeid(long_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(ULONG_T,&typeid(ulong_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(LLONG_T,&typeid(llong_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(ULLONG_T,&typeid(ullong_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(FLOAT32_T,&typeid(float32_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(FLOAT64_T,&typeid(float64_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(LFLOAT64_T,&typeid(lfloat64_t)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(STRING_T,&typeid(std::string)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(VOID_T,&typeid(void)));
    (*result).insert(std::pair<EnumVar_t,const std::type_info*>(BOOL_T,&typeid(bool*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PCHAR_T,&typeid(char_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PINT8_T,&typeid(int8_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PUINT8_T,&typeid(uint8_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PINT16_T,&typeid(int16_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PUINT16_T,&typeid(uint16_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PINT32_T,&typeid(int32_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PUINT32_T,&typeid(uint32_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PINT64_T,&typeid(int64_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PUINT64_T,&typeid(uint64_t*)));	
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PLONG_T,&typeid(long_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PULONG_T,&typeid(ulong_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PLLONG_T,&typeid(llong_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PULLONG_T,&typeid(ullong_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PFLOAT32_T,&typeid(float32_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PFLOAT64_T,&typeid(float64_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PLFLOAT64_T,&typeid(lfloat64_t*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PSTRING_T,&typeid(std::string*)));
		(*result).insert(std::pair<EnumVar_t,const std::type_info*>(PVOID_T,&typeid(void*)));
	}
	return *result;
}

std::multimap<const std::type_info*,EnumVar_t>& blib::GetTypeInfoVarMap(){
	std::multimap<const std::type_info*,EnumVar_t>* result=&typeInfoVarMap;
	if(result->size()==0){
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(void),UNKNOWN_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(bool),BOOL_T));
    (*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(char_t),CHAR_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(int8_t),INT8_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(uint8_t),UINT8_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(int16_t),INT16_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(uint16_t),UINT16_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(int32_t),INT32_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(uint32_t),UINT32_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(int64_t),INT64_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(uint64_t),UINT64_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(long_t),LONG_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(ulong_t),ULONG_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(llong_t),LLONG_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(ullong_t),ULLONG_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(float32_t),FLOAT32_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(float64_t),FLOAT64_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(lfloat64_t),LFLOAT64_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(std::string),STRING_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(void),VOID_T));		
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(bool*),PBOOL_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(char_t*),PCHAR_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(int8_t*),PINT8_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(uint8_t*),PUINT8_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(int16_t*),PINT16_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(uint16_t*),PUINT16_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(int32_t*),PINT32_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(uint32_t*),PUINT32_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(int64_t*),PINT64_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(uint64_t*),PUINT64_T));	
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(long_t*),PLONG_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(ulong_t*),PULONG_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(llong_t*),PLLONG_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(ullong_t*),PULLONG_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(float32_t*),PFLOAT32_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(float64_t*),PFLOAT64_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(lfloat64_t*),PLFLOAT64_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(std::string*),PSTRING_T));
		(*result).insert(std::pair<const std::type_info*,EnumVar_t>(&typeid(void*),PVOID_T));
	}
	return *result;
}

EnumResult_t InitTypeMaps(){
  GetVarHashMap();
	GetHashVarMap();
	GetVarTypeInfoMap();
	GetTypeInfoVarMap();
	return SUCCESS;
}

size_t blib::GetHash(EnumVar_t type){
  size_t result=0;
  if(GetVarHashMap().find(type)!=GetVarHashMap().end())
    result=GetVarHashMap().find(type)->second;
  return result;
}

size_t blib::GetHash(const std::type_info* type){
  size_t result=0;
  if(GetTypeInfoVarMap().find(type)!=GetTypeInfoVarMap().end())
    result=GetHash(GetTypeInfoVarMap().find(type)->second);
  return result;
}

EnumVar_t blib::GetEnumVar(size_t hash){
  EnumVar_t result=UNKNOWN_T;
  if(GetHashVarMap().find(hash)!=GetHashVarMap().end())
    result=GetHashVarMap().find(hash)->second;
  return result;
}

EnumVar_t blib::GetEnumVar(const std::type_info* type){
  EnumVar_t result=UNKNOWN_T;
  if(GetTypeInfoVarMap().find(type)!=GetTypeInfoVarMap().end())
    result=GetTypeInfoVarMap().find(type)->second;
  return result;
}

const std::type_info* blib::GetTypeInfo(EnumVar_t type){
  const std::type_info* result=&typeid(void);
  if(GetVarTypeInfoMap().find(type)!=GetVarTypeInfoMap().end())
    result=GetVarTypeInfoMap().find(type)->second;
  return result;
}

const std::type_info* blib::GetTypeInfo(size_t hash){
  return GetTypeInfo(GetEnumVar(hash));
}

size_t blib::GetSize(const EnumVar_t type){
	size_t result=0;
	switch(type){
    case BOOL_T:
      result=sizeof(bool);
      break;
    case CHAR_T:
			result=sizeof(char_t);
      break;
    case INT8_T:
			result=sizeof(int8_t);
      break;
    case UINT8_T:
			result=sizeof(uint8_t);
      break;
    case INT16_T:
			result=sizeof(int16_t);
      break;
    case UINT16_T:
			result=sizeof(uint16_t);
      break;
    case INT32_T:
			result=sizeof(int32_t);
      break;
    case UINT32_T:
			result=sizeof(uint32_t);
      break;
    case INT64_T:
			result=sizeof(int64_t);
      break;
    case UINT64_T:
			result=sizeof(uint64_t);
      break;
    case LONG_T:
			result=sizeof(long_t);
      break;
    case ULONG_T:
			result=sizeof(ulong_t);
      break;
    case LLONG_T:
			result=sizeof(llong_t);
      break;
    case ULLONG_T:
			result=sizeof(ullong_t);
      break;
    case FLOAT32_T:
			result=sizeof(float32_t);
      break;
    case FLOAT64_T:
			result=sizeof(float64_t);
      break;
    case LFLOAT64_T:
			result=sizeof(lfloat64_t);
      break;
	}
	return result;
}

size_t blib::GetSize(const std::type_info* type){
	return GetSize(GetEnumVar(type));
}

size_t blib::GetSize(const size_t hash){
  return GetSize(GetEnumVar(hash));
}
