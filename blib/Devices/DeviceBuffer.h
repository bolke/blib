#ifndef BLIB_DEVICEBUFFER_H
#define BLIB_DEVICEBUFFER_H

#include <queue>
#include "DeviceWrapper.h"

namespace blib{

class DeviceBuffer:public DeviceWrapper{
protected:
	size_t popSize;
	size_t pushSize;
	std::queue<char_t> popBuffer;
	std::queue<char_t> pushBuffer;
public:	
  DeviceBuffer(Device& d,size_t popSize=1,size_t pushSize=1);  
  virtual size_t Pop(char_t& c,size_t size=1);  
  virtual size_t Pop(std::string& data);	
  virtual size_t Push(const char_t &c,size_t size=1);  
	virtual size_t Push(const std::string& data);
};

};

#endif
