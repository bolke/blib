#ifndef BLIB_DATABUFFER_H
#define BLIB_DATABUFFER_H

#include "Data.h"

namespace blib{

class DataBuffer:public Data{
protected:
	std::vector<char_t> buffer;
public:
	virtual size_t Size();
	virtual size_t Pop(char_t& c,size_t size=1);		
  virtual size_t Push(const char_t &c,size_t size=1);
  virtual std::vector<char_t>& GetBuffer();
};

};

#endif
