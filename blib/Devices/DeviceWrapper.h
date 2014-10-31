#ifndef BLIB_DEVICEWRAPPER_H
#define BLIB_DEVICEWRAPPER_H

#include "Device.h"

namespace blib{
class DeviceWrapper:public Device, public Base{
protected:	
	bool destroyDevice;
  Device* device;
public:	
  BLIB_LIB_API DeviceWrapper(Device& d,bool destroyDevice=false);							//give a device and if we should destroy it
  BLIB_LIB_API virtual ~DeviceWrapper();
  BLIB_LIB_API virtual size_t Size();
  BLIB_LIB_API virtual bool IsOpen();
  BLIB_LIB_API virtual EnumResult_t Open();
  BLIB_LIB_API virtual EnumResult_t Close();
	BLIB_LIB_API virtual EnumResult_t SetDestroyDevice(bool value);					
	BLIB_LIB_API virtual bool GetDestroyDevice();
  BLIB_LIB_API virtual size_t Pop(char_t& c,size_t size=1);  
  BLIB_LIB_API virtual size_t Pop(std::string& data);	
  BLIB_LIB_API virtual size_t Push(const char_t &c,size_t size=1);  
	BLIB_LIB_API virtual size_t Push(const std::string& data);
};

};

#endif
