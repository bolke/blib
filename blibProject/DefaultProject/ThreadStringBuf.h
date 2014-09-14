#ifndef BLIB_THREADSTRINGBUF_H
#define BLIB_THREADSTRINGBUF_H

#include "blib.h"
#include <sstream>

namespace blib{

class ThreadStringBuf:public std::stringbuf,public Device,public Base{
protected:
	virtual void imbue(const std::locale& loc);
	virtual std::streambuf* setbuf(char* s,std::streamsize n);
	virtual std::streampos seekoff(std::streamoff off,std::ios_base::seekdir way,
								                  std::ios_base::openmode which=std::ios_base::in|std::ios_base::out);
	virtual std::streampos seekpos(std::streampos sp,std::ios_base::openmode which=
																	std::ios_base::in|std::ios_base::out);
	virtual int sync();
	virtual std::streamsize showmanyc();
	virtual std::streamsize xsgetn(char* s,std::streamsize n);
	virtual int underflow(); 
	virtual int uflow();
  virtual int pbackfail(int c=EOF);
	virtual std::streamsize xsputn(const char* s,std::streamsize n);
	virtual int overflow(int c=EOF);
public:
	ThreadStringBuf();
  virtual size_t Size();
	virtual size_t Pop(char_t& c,size_t size);
	virtual size_t Pop(std::string& data);
  virtual size_t Push(const char_t &c,size_t size=1);  
  virtual size_t Push(const std::string& data); 
};

};

#endif
