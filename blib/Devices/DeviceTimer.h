#ifndef BLIB_DEVICETIMER_H
#define BLIB_DEVICETIMER_H

#include "DeviceWrapper.h"

namespace blib{

class DeviceTimer:public DeviceWrapper{
protected:	
	uint64_t lastPop;
	uint64_t lastPush;
	uint64_t popDelay;
	uint64_t pushDelay;
public:
	BLIB_LIB_API DeviceTimer(Device& d,uint64_t popDelay=0,uint64_t pushDelay=0);  
  BLIB_LIB_API virtual size_t Pop(char_t& c,size_t size=1);  
  BLIB_LIB_API virtual size_t Pop(std::string& data);	
  BLIB_LIB_API virtual size_t Push(const char_t &c,size_t size=1);  
	BLIB_LIB_API virtual size_t Push(const std::string& data);
};

};

#endif
