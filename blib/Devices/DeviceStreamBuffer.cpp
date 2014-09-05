#include "DeviceStreamBuffer.h"

using namespace blib;

DeviceStreamBuffer::DeviceStreamBuffer(Device& d,bool destroyDevice):DeviceWrapper(d,destroyDevice){
	buffer.reserve(DEFAULT_BUFFER_SIZE);
	char_t* end=(&(buffer.front()))+buffer.size();
	setg(end,end,end);
}
