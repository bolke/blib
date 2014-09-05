#include "Device.h"

using namespace blib;

Device::Device(ThreadItem& item,bool destroyLockpad):ThreadSafe(item,destroyLockpad){
	isOpen=false;
}

Device::Device(ThreadLock& lock):ThreadSafe(lock){
	this->lock->Lock();
	isOpen=false;
	this->lock->Unlock();
}

Device::~Device(){ 	
}

size_t Device::Pop(std::string& data){
  size_t result=0;
  if(lock->Lock()){		
		result=Data::Pop(data);
    lock->Unlock();
  }
  return result;
}

size_t Device::Push(const std::string& data){
	size_t result=0;
	if(lock->Lock()){
		result=Data::Push(data);
	  lock->Unlock();
	}
	return result;
}

bool Device::IsOpen(){
	bool result=false;
	if(lock->Lock()){
		result=isOpen;
		lock->Unlock();
	}
  return result;
}

EnumResult_t Device::Open(){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
	  isOpen=true;
	  result=SUCCESS;
	  lock->Unlock();
	}
  return result;
}

EnumResult_t Device::Close(){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
	  isOpen=false;
	  result=SUCCESS;
	  lock->Unlock();
	}
  return result;
}

Device& Device::operator>>(Device& device){    	
	if(lock->Lock()){		
		((Data&)*this)>>(Data&)device;
		lock->Unlock();
	}
  return *this;
}

Device& Device::operator<<(Device& device){
	if(lock->Lock()){
		((Data&)*this)<<(Data&)device;
	  lock->Unlock();
	}
  return *this;
}

Device& Device::operator>>(std::string& data){
	Pop(data);
  return *this;
}

Device& Device::operator<<(const std::string& data){
	Push(data);
	return *this;
}
