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
	DeviceCoupler();
	virtual std::vector<Device*>& GetDevices();
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
