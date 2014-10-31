#ifndef BLIB_DATABUFFER_H
#define BLIB_DATABUFFER_H

#include "Data.h"

namespace blib{

class DataBuffer:public Data{
protected:
	std::vector<char_t> buffer;
public:
	BLIB_LIB_API virtual size_t Size();
	BLIB_LIB_API virtual size_t Pop(char_t& c,size_t size=1);		
  BLIB_LIB_API virtual size_t Push(const char_t &c,size_t size=1);
  BLIB_LIB_API virtual std::vector<char_t>& GetBuffer();
};

};

#endif
