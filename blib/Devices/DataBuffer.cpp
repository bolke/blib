#include "DataBuffer.h"

using namespace blib;

size_t DataBuffer::Size(){
	return buffer.size();
};

size_t DataBuffer::Pop(char_t& c,size_t size){
	if(Size()<size)
		size=Size();
	if(size>0){
		std::copy(buffer.begin(),buffer.begin()+size,&c);
		buffer.erase(buffer.begin(),buffer.begin()+size);
	}
	return size;
};

size_t DataBuffer::Push(const char_t &c,size_t size){
	buffer.insert(buffer.end(),&c,&c+size);
	return size;
};
											 
std::vector<char_t>& DataBuffer::GetBuffer(){
  return buffer;
}
