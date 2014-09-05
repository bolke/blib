#ifndef BLIB_DEVICESTREAMBUFFER_H
#define BLIB_DEVICESTREAMBUFFER_H

#include "DeviceWrapper.h"
#include <queue>

namespace blib{

class DeviceStreamBuffer:public DeviceWrapper,public std::streambuf{
protected:
	std::vector<char_t> buffer;
public:
	DeviceStreamBuffer(Device& d,bool destroyDevice=false);
};

};

#endif
