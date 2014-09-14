#include "Security.h"
#include "FileIO.h"

#include <ctime>

using namespace blib;

uint8_t blib::GetCrc8(const char_t* c,size_t size){
	uint8_t result=0;
	char_t* p=(char_t*)c;
	while((p!=0)||(size>0)){
	  p++;
		if(size!=0)
		  size--;
	}
	return result;
}

uint16_t blib::GetCrc16(const char_t* c,size_t size){
  uint16_t result=0;
	char_t* p=(char_t*)c;
	while((p!=0)||(size>0)){
	  p++;
		if(size!=0)
		  size--;
	}
	return result;
}

uint32_t blib::GetCrc32(const char_t* c,size_t size){
	uint32_t result=0;
	char_t* p=(char_t*)c;
	while((p!=0)||(size>0)){
	  p++;
		if(size!=0)
		  size--;
	}
	return result;
}

uint64_t blib::GetCrc64(const char_t* c,size_t size){
	uint64_t result=0;
	char_t* p=(char_t*)c;
	while((p!=0)||(size>0)){
	  p++;
		if(size!=0)
		  size--;
	}
	return result;
}

EnumResult_t  blib::GeneratePassword(char_t* c,size_t size){
  EnumResult_t result=FAIL;
	if(size>0){
		srand(time(NULL)%blib::GetRunTimeMs());
		uint32_t randNr=rand();
		while(size>0){
			size--;
			c[size]=randNr%255;
			randNr=rand();
		}
		result=SUCCESS;				
	}
	return result;
}
