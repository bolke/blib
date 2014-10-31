#ifndef BLIB_DEVICECOUPLER_H
#define BLIB_DEVICECOUPLER_H

#include "Base.h"
#include "Threading.h"
#include "Device.h"

namespace blib{

class DeviceCoupler:public Device,public Base{
protected:
	std::vector<Device*> devices;
public:
	BLIB_LIB_API DeviceCoupler();
	BLIB_LIB_API virtual std::vector<Device*>& GetDevices();
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
