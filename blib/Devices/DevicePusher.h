#ifndef BLIB_DEVICEPUSHER_H
#define BLIB_DEVICEPUSHER_H

#include "DeviceCoupler.h"

namespace blib{

class DevicePusher:public DeviceCoupler{
public:
	BLIB_LIB_API DevicePusher();
  BLIB_LIB_API virtual size_t Size();
  BLIB_LIB_API virtual size_t Pop(char_t& c,size_t size=1);  
  BLIB_LIB_API virtual size_t Pop(std::string& data);
  BLIB_LIB_API virtual size_t Push(const char_t &c,size_t size=1);  
  BLIB_LIB_API virtual size_t Push(const std::string& data); 
	BLIB_LIB_API virtual bool IsOpen();
  BLIB_LIB_API virtual EnumResult_t Open();
  BLIB_LIB_API virtual EnumResult_t Close();		
};

};

#endif
