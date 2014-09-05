#include "DeviceTimer.h"

using namespace blib;

DeviceTimer::DeviceTimer(Device& d,uint64_t popDelay,uint64_t pushDelay):DeviceWrapper(d){
	lastPop=GetRunTimeMs();
	lastPush=lastPop;
	this->popDelay=popDelay;
	this->pushDelay=pushDelay;
}

size_t DeviceTimer::Pop(char_t& c,size_t size){
  size_t result=0;
	if(lock->Lock()){
		if((GetRunTimeMs()-lastPop)>=popDelay){
		  lastPop=GetRunTimeMs();
			result=device->Pop(c,size);
		}
		lock->Unlock();
	}
	return result;
}
  
size_t DeviceTimer::Pop(std::string& data){
	return DeviceWrapper::Pop(data);
}
	
size_t DeviceTimer::Push(const char_t &c,size_t size){
  size_t result=0;
	if(lock->Lock()){
		if((GetRunTimeMs()-lastPush)>=pushDelay){
		  lastPush=GetRunTimeMs();
			result=device->Push(c,size);
		}
		lock->Unlock();
	}
	return result;
}

size_t DeviceTimer::Push(const std::string& data){
	return DeviceWrapper::Push(data);
}
