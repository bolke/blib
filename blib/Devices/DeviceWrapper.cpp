#include "DeviceWrapper.h"

using namespace blib;

DeviceWrapper::DeviceWrapper(Device& d,bool destroyDevice):Device(d.GetLock()){
	this->destroyDevice=destroyDevice;
	device=&d;
}

DeviceWrapper::~DeviceWrapper(){ 
	if(destroyDevice){
		if(&(device->GetLock())==&(this->GetLock()))
			lock=NULL;
		delete device;		
	}
}

size_t DeviceWrapper::Size(){
  return device->Size();
}

bool DeviceWrapper::IsOpen(){  
	return device->IsOpen();
}

EnumResult_t DeviceWrapper::Open(){
	return device->Open();
}

EnumResult_t DeviceWrapper::Close(){
  return device->Close();
}

size_t DeviceWrapper::Pop(char_t& c,size_t size){
  return device->Pop(c,size);
}

size_t DeviceWrapper::Pop(std::string& data){
	return Device::Pop(data);
}

size_t DeviceWrapper::Push(const char_t &c,size_t size){  
  return device->Push(c,size);
}

size_t DeviceWrapper::Push(const std::string& data){
	return Device::Push(data);
}

EnumResult_t DeviceWrapper::SetDestroyDevice(bool value){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		destroyDevice=value;
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
}

bool DeviceWrapper::GetDestroyDevice(){
  return destroyDevice;
}
