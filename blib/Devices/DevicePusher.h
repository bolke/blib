#ifndef BLIB_DEVICEPUSHER_H
#define BLIB_DEVICEPUSHER_H

#include "DeviceCoupler.h"

namespace blib{

class DevicePusher:public DeviceCoupler{
public:
	DevicePusher();
  virtual size_t Size();
  virtual size_t Pop(char_t& c,size_t size=1);  
  virtual size_t Pop(std::string& data);
  virtual size_t Push(const char_t &c,size_t size=1);  
  virtual size_t Push(const std::string& data); 
	virtual bool IsOpen();
  virtual EnumResult_t Open();
  virtual EnumResult_t Close();		
};

};

#endif
