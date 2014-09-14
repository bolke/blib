#ifndef BLIB_SECURITY_H
#define BLIB_SECURITY_H

#include "Core.h"
#include "AESDevice.h"

namespace blib{
  uint8_t GetCrc8(const char_t* c,size_t size=0);	
	uint16_t GetCrc16(const char_t* c,size_t size=0);	
	uint32_t GetCrc32(const char_t* c,size_t size=0);	
	uint64_t GetCrc64(const char_t* c,size_t size=0);
	EnumResult_t GeneratePassword(char_t* c,size_t size=0);
};

#endif
