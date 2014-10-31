#ifndef BLIB_RAWPARSER_H
#define BLIB_RAWPARSER_H

#include <typeinfo>
#include <string>
#include "Base.h"

namespace blib{

class RawParser:public Base{
public:
	BLIB_LIB_API static uint8_t GetUInt8_t(const char_t& buffer,const size_t start=0);												//put 1 bytes into uint8		return (char_t -> uint8_t)
	BLIB_LIB_API static int8_t GetInt8_t(const char_t& buffer,const size_t start=0);													//put 1 bytes into int8     return (char_t -> int8_t)
	BLIB_LIB_API static uint16_t GetUInt16_t(const char_t& buffer,const size_t start=0);											//put 2 bytes into uint16		return (char_t -> uint16_t)
	BLIB_LIB_API static int16_t GetInt16_t(const char_t& buffer,const size_t start=0);												//put 2 bytes into int16    return (char_t -> int16_t)
	BLIB_LIB_API static uint32_t GetUInt32_t(const char_t& buffer,const size_t start=0);											//put 4 bytes into uint32   return (char_t -> uint32_t)
	BLIB_LIB_API static int32_t GetInt32_t(const char_t& buffer,const size_t start=0);												//put 4 bytes into int32    return (char_t -> int32_t)
	BLIB_LIB_API static uint64_t GetUInt64_t(const char_t& buffer,const size_t start=0);											//put 8 bytes into uint64   return (char_t -> uint64_t)
	BLIB_LIB_API static int64_t GetInt64_t(const char_t& buffer,const size_t start=0);												//put 8 bytes into int64    return (char_t -> int64_t)
	BLIB_LIB_API static float32_t GetFloat32_t(const char_t& buffer,const size_t start=0);										//put 4 bytes into float32  return (char_t -> float32_t)
	BLIB_LIB_API static float64_t GetFloat64_t(const char_t& buffer,const size_t start=0);										//put 8 bytes into float64  return (char_t -> float64_t)
	BLIB_LIB_API static std::string GetString(const char_t& buffer,const size_t start=0,const size_t size=0);	//if size==0, stop on null value in buffer, or on default size
	BLIB_LIB_API static EnumResult_t GetVariable(const char_t& buffer,const size_t start,const std::type_info* info,void* variable,const size_t size=0); //grab data from buffer according to typeinfo		

	BLIB_LIB_API static EnumResult_t FromString(const std::string& source,const EnumVar_t type,void* target);				//convert value of type from string to type, inserted into a void pointer (string -> type -> void*)
	BLIB_LIB_API static EnumResult_t FromString(const std::string& source,const std::type_info* type,void* target);	//convert value of type from string to type, inserted into a void pointer (string -> type -> void*)

	BLIB_LIB_API static EnumResult_t SetUInt8_t(const uint8_t value,char_t& target,const size_t start=0);			//put uint8_t into char array, start at start			
	BLIB_LIB_API static EnumResult_t SetInt8_t(const int8_t value,char_t& target,const size_t start=0);				//put int8_t into char array, start at start
	BLIB_LIB_API static EnumResult_t SetUInt16_t(const uint16_t value,char_t& target,const size_t start=0);		//put uint16_t into char array, start at start
	BLIB_LIB_API static EnumResult_t SetInt16_t(const int16_t value,char_t& target,const size_t start=0);			//put int16_t into char array, start at start
	BLIB_LIB_API static EnumResult_t SetUInt32_t(const uint32_t value,char_t& target,const size_t start=0);		//put uint32_t into char array, start at start
	BLIB_LIB_API static EnumResult_t SetInt32_t(const int32_t value,char_t& target,const size_t start=0);			//put int32_t into char array, start at start
	BLIB_LIB_API static EnumResult_t SetUInt64_t(const uint64_t value,char_t& target,const size_t start=0);		//put uint64_t into char array, start at start
	BLIB_LIB_API static EnumResult_t SetInt64_t(const int64_t value,char_t& target,const size_t start=0);			//put int64_t into char array, start at start
	BLIB_LIB_API static EnumResult_t SetFloat32_t(const float32_t value,char_t& target,const size_t start=0);	//put float32_t into char array, start at start
	BLIB_LIB_API static EnumResult_t SetFloat64_t(const float64_t value,char_t& target,const size_t start=0);	//put float64_t into char array, start at start
	BLIB_LIB_API static EnumResult_t SetString(const std::string& value,char_t& target,const size_t start=0);	//put string into char array, start at start, buffer has to be large enough
	BLIB_LIB_API static EnumResult_t SetVariable(const std::string& value,const EnumVar_t type,char_t& target,const size_t start=0); //set var according to type, converted from string

	BLIB_LIB_API static EnumResult_t ToString(const void* source,const EnumVar_t type,std::string& target);				//convert source of given type to string, base types and pointers to base type accepted, pointer != NULL
  BLIB_LIB_API static EnumResult_t ToString(const void* source,const std::type_info* type,std::string& target);	//convert source to given type to string, base types and pointers to base type accepted, pointer != NULL
};

};

#endif
