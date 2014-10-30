#include "Basis.h"

#include <functional>
#include <typeinfo>

using namespace blib;

size_t GetDjbHash(const char_t* toHash){
	size_t result=5381;  
  char_t* c=(char*)toHash;

	while(*c!=0){
    result=((result<<5)+result)+*c;
		c++;
	}

  return result;
}

uint64_t blib::GetRunTimeMs(){
#ifdef WINDOWS
	return GetTickCount();
#elif LINUX
#error IMPLEMENT THIS FEATURE FOR LINUX
	return 0;
#endif
}

void blib::SleepMs(uint64_t ms){
#ifdef WINDOWS)
	Sleep(ms);
#elif LINUX
	usleep(ms*1000);
#endif
}

size_t blib::GetHashCode(const std::type_info* classType){
	size_t result=0;
	if(classType!=NULL)
		result=GetDjbHash(classType->name());	
	return result;
}

size_t blib::GetHashSize(){
	return sizeof(size_t);
}
