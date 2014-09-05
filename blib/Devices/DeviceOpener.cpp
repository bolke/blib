#include "DeviceOpener.h"

using namespace blib;

DeviceOpener::DeviceOpener(Device& d,bool autoOpen):DeviceWrapper(d){
  this->autoOpen=autoOpen;
	IsOpen();
}

bool DeviceOpener::IsOpen(){
  if(autoOpen){
    if(!device->IsOpen())
      Open();
  }
	return DeviceWrapper::IsOpen();
}

size_t DeviceOpener::Pop(char_t& c,size_t size){
  IsOpen();
  return DeviceWrapper::Pop(c,size);
}  

size_t DeviceOpener::Pop(std::string& data){
  IsOpen();
  return DeviceWrapper::Pop(data);
}

size_t DeviceOpener::Push(const char_t &c,size_t size){
  IsOpen();
  return DeviceWrapper::Push(c,size);
}  

size_t DeviceOpener::Push(const std::string& data){
  IsOpen();
  return DeviceWrapper::Push(data);  
} 

Device& DeviceOpener::operator>>(Device& device){
  IsOpen();
  return DeviceWrapper::operator>>(device);
}

Device& DeviceOpener::operator<<(Device& device){
  IsOpen();
  return DeviceWrapper::operator<<(device);
}

bool DeviceOpener::GetAutoOpen(){
  return autoOpen;
}

EnumResult_t DeviceOpener::SetAutoOpen(bool autoOpen){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    this->autoOpen=autoOpen;
    result=SUCCESS;
    lock->Unlock();
  }
  return result;
}
