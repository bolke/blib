#include "ThreadStringBuf.h"

using namespace blib;

ThreadStringBuf::ThreadStringBuf(){
}

void ThreadStringBuf::imbue(const std::locale& loc){
	if(lock->Lock()){
		std::stringbuf::imbue(loc);
		lock->Unlock();
	}
}

std::streambuf* ThreadStringBuf::setbuf(char* s,std::streamsize n){
	std::streambuf* result=NULL;
	if(lock->Lock()){
		result=std::stringbuf::setbuf(s,n);
		lock->Unlock();
	}
  return result;
}

std::streampos ThreadStringBuf::seekoff(std::streamoff off,std::ios_base::seekdir way,std::ios_base::openmode which){
	std::streampos result=0;
	if(lock->Lock()){
		result=std::stringbuf::seekoff(off,way,which);
		lock->Unlock();
	}
  return result;
}

std::streampos ThreadStringBuf::seekpos(std::streampos sp,std::ios_base::openmode which){
	std::streampos result=0;
	if(lock->Lock()){
		result=std::stringbuf::seekpos(sp,which);
		lock->Unlock();
	}
  return result;
}

int ThreadStringBuf::sync(){
	int result=0;
	if(lock->Lock()){
		result=std::stringbuf::sync();
		lock->Unlock();
	}
  return result;
}

std::streamsize ThreadStringBuf::showmanyc(){
	std::streamsize result=0;
	if(lock->Lock()){
		result=std::stringbuf::showmanyc();
		lock->Unlock();
	}
  return result;
}

std::streamsize ThreadStringBuf::xsgetn(char* s,std::streamsize n){
	std::streamsize result=0;
	if(lock->Lock()){
		result=std::stringbuf::xsgetn(s,n);
		lock->Unlock();
	}
  return result;
}

int ThreadStringBuf::underflow(){
	int result;
	if(lock->Lock()){
		result=std::stringbuf::underflow();
		lock->Unlock();
	}
  return result;
}

int ThreadStringBuf::uflow(){
	int result;
	if(lock->Lock()){
		result=std::stringbuf::uflow();
		lock->Unlock();
	}
  return result;
}

int ThreadStringBuf::pbackfail(int c){
	int result;
	if(lock->Lock()){
		result=std::stringbuf::pbackfail(c);
		lock->Unlock();
	}
  return result;
}

std::streamsize ThreadStringBuf::xsputn (const char* s,std::streamsize n){
	std::streamsize result=0;
	if(lock->Lock()){
		result=std::stringbuf::xsputn(s,n);
		lock->Unlock();
	}
  return result;
}

int ThreadStringBuf::overflow(int c){
	int result;
	if(lock->Lock()){
		result=std::stringbuf::overflow(c);
		lock->Unlock();
	}
  return result;
}

size_t ThreadStringBuf::Size(){
  size_t result=0;
	if(lock->Lock()){
		if(sgetc()!=EOF)
		  result=DEFAULT_BUFFER_SIZE;
		lock->Unlock();
	}
	return result;
}

size_t ThreadStringBuf::Pop(char_t& c,size_t size){
	size_t result=0;
	if(lock->Lock()){
		size_t length=in_avail();
		if(length>size)
			length=size;
		if((length==0)&&(size>0))
			length=1;
		while(length>0){
		  if(sgetc()!=EOF){
        (&c)[result]=sbumpc();
				result++;
				length--;
			}else
				length=0;
		}	
		lock->Unlock();
	}
	return result;
}

size_t ThreadStringBuf::Pop(std::string& data){
	size_t result=0;
	if(lock->Lock()){
		result=Device::Pop(data);
		lock->Unlock();
	}
	return result;
}

size_t ThreadStringBuf::Push(const char_t &c,size_t size){
	size_t result=0;
	if(lock->Lock()){
		result=sputn(&c,size);
		lock->Unlock();
	}
	return result;
}

size_t ThreadStringBuf::Push(const std::string& data){
	size_t result=0;
	if(lock->Lock()){
		result=Device::Push(data);
		lock->Unlock();
	}
	return result;
}
