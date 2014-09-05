#ifndef BLIB_BASIS_H
#define BLIB_BASIS_H

#include <typeinfo>

#include "Typedef.h"																							//type definition for all platforms
#include "BaseDefines.h"																					//constants and defines, like FAIL and SUCCESS
#include "Base.h"																									//base class
#include "Data.h"																									//data class
#include "StringParser.h"																					//string editing and parsing tools
#include "Callback.h"																							//callback classes,max 8 arguments, can be extended for more
#include "RawParser.h"																						//data conversion, char array to other, void* to other

namespace blib{

uint64_t GetRunTimeMs();																					//universal GetTickCount function (windows, unix, etc)
void SleepMs(uint64_t ms);																				//universal Sleep function

size_t GetHashCode(const std::type_info* classType);							//get a hash of a class type
size_t GetHashSize();																							//get size of hash, sizeof(size_t)

};
#endif
