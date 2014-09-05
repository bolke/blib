#include "DevicePusher.h"

using namespace blib;

DevicePusher::DevicePusher(){
}

size_t DevicePusher::Size(){
	return 0;
}

size_t DevicePusher::Pop(char_t& c,size_t size){
	return 0;
}  

size_t DevicePusher::Pop(std::string& data){
	return 0;
}

size_t DevicePusher::Push(const char_t &c,size_t size){
	size_t result=0;
	if(lock->Lock()){
		std::vector<Device*>::iterator it=devices.begin();
		while(it!=devices.end()){
			if((*it)->Push(c,size)==size)
				result++;
			it++;
		}
		lock->Unlock();
	}
	return result;
}  

size_t DevicePusher::Push(const std::string& data){
	return Push(*(data.c_str()),data.size());
} 

bool DevicePusher::IsOpen(){
	bool result=false;
	if(lock->Lock()){
		std::vector<Device*>::iterator it=devices.begin();
		while(it!=devices.end()){
			if((*it)->IsOpen()){				
				result=true;
				break;
			}
		  it++;
		}
		lock->Unlock();
	}
	return result;
}

EnumResult_t DevicePusher::Open(){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		std::vector<Device*>::iterator it=devices.begin();
		while(it!=devices.end()){
			if((!(*it)->IsOpen())&&((*it)->Open()))
				result=SUCCESS;
		  it++;
		}
		lock->Unlock();
	}
	return result;
}

EnumResult_t DevicePusher::Close(){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		std::vector<Device*>::iterator it=devices.begin();
		while(it!=devices.end()){
			if(((*it)->IsOpen())&&((*it)->Close()))
				result=SUCCESS;
		  it++;
		}
		lock->Unlock();
	}
	return result;
}	
