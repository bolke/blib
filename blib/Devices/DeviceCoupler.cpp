#include "DeviceCoupler.h"

using namespace blib;

DeviceCoupler::DeviceCoupler(){
}

std::vector<Device*>& DeviceCoupler::GetDevices(){
  return devices;
}

size_t DeviceCoupler::Size(){
	size_t result=0;
	if(lock->Lock()){
		if(devices.size()>0)
			result=devices[0]->Size();
		lock->Unlock();
	}
	return result;	
}

size_t DeviceCoupler::Pop(char_t& c,size_t size){
	size_t result=0;
	if(lock->Lock()){
		if(devices.size()>0){
			for(size_t i=devices.size()-1;i>0;i--)
				(*(devices[i]))>>(*(devices[i-1]));		
			result=devices[0]->Pop(c,size);	  
		}
    lock->Unlock();
  }
	return result;
}

size_t DeviceCoupler::Pop(std::string& data){
	return Device::Pop(data);
}

size_t DeviceCoupler::Push(const char_t &c,size_t size){
	size_t result=0;
	if(lock->Lock()){		
		if(devices.size()>0){
		  result=devices[0]->Push(c,size);
			for(size_t i=0;i<devices.size()-2;i++)
				(*(devices[i]))<<(*(devices[i-1]));
		}
		lock->Unlock();
	}
	return result;
}

size_t DeviceCoupler::Push(const std::string& data){
	return Device::Push(data);
}

bool DeviceCoupler::IsOpen(){
	bool result=false;
	if(lock->Lock()){
		if(devices.size()>0){
			result=true;
  		std::vector<Device*>::iterator it=devices.begin();
	  	while(it!=devices.end()){
				if(!(*it)->IsOpen()){
			  	result=false;
					break;
				}
			  it++;
		  }
		}
		lock->Unlock();
	}
	return result;	
}

EnumResult_t DeviceCoupler::Open(){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(devices.size()>0){
			result=SUCCESS;
			std::vector<Device*>::iterator it=devices.begin();
			while(it!=devices.end()){
				if((!(*it)->IsOpen())&&(*it)->Open()!=SUCCESS)
					break;
				it++;
			}
		}
		lock->Unlock();
	}
	return result;
}

EnumResult_t DeviceCoupler::Close(){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		result=SUCCESS;
		if(devices.size()>0){
			std::vector<Device*>::iterator it=devices.begin();
			while(it!=devices.end()){
				if(((*it)->IsOpen())&&(*it)->Close()!=SUCCESS)
					break;
				it++;
			}
		}
		lock->Unlock();
	}
	return result;
}
