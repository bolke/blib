#ifndef BLIB_DEVICEWRAPPER_H
#define BLIB_DEVICEWRAPPER_H

#include "Device.h"

namespace blib{
class DeviceWrapper:public Device, public Base{
protected:	
	bool destroyDevice;
  Device* device;
public:	
  DeviceWrapper(Device& d,bool destroyDevice=false);							//give a device and if we should destroy it
  virtual ~DeviceWrapper();
  virtual size_t Size();
  virtual bool IsOpen();
  virtual EnumResult_t Open();
  virtual EnumResult_t Close();
	virtual EnumResult_t SetDestroyDevice(bool value);					
	virtual bool GetDestroyDevice();
  virtual size_t Pop(char_t& c,size_t size=1);  
  virtual size_t Pop(std::string& data);	
  virtual size_t Push(const char_t &c,size_t size=1);  
	virtual size_t Push(const std::string& data);
};

};

#endif
