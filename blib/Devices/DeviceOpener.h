#ifndef BLIB_DEVICEOPENER_H
#define BLIB_DEVICEOPENER_H

#include "DeviceWrapper.h"

namespace blib{
class DeviceOpener:public DeviceWrapper{
protected:
  bool autoOpen;																						//if set, will try to open the device at any action
public:
  DeviceOpener(Device& d,bool autoOpen=true);								//connect device and set autoOpen
  virtual bool IsOpen();																		//if autoOpen, try to open the device and return if it's open
  virtual size_t Pop(char_t& c,size_t size=1);							//if autoOpen, open and pop
  virtual size_t Pop(std::string& data);										//if autoOpen, open and pop
  virtual size_t Push(const char_t &c,size_t size=1);				//if autoOpen, open and push
  virtual size_t Push(const std::string& data);							//if autoOpen, open and push
  virtual Device& operator>>(Device& device);								
  virtual Device& operator<<(Device& device);
  virtual bool GetAutoOpen();
  virtual EnumResult_t SetAutoOpen(bool autoOpen);
};
};

#endif
