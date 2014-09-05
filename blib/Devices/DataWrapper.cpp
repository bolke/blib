#include "DataWrapper.h"

using namespace blib;

DataWrapper::DataWrapper(Data& d,bool destroyData){
	this->destroyData=destroyData;
	data=&d;
}

DataWrapper::~DataWrapper(){ 
	if(destroyData){					
		delete data;		
	}
}

size_t DataWrapper::Size(){
  return data->Size();
}

size_t DataWrapper::Pop(char_t& c,size_t size){
  size_t result=0;
	if(lock->Lock()){
	  result=data->Pop(c,size);
  	lock->Unlock();
	}
	return result;
}

size_t DataWrapper::Pop(std::string& data){
	size_t result=0;
	if(lock->Lock()){
	  result=this->data->Pop(data);
  	lock->Unlock();
	}
	return result;
}

size_t DataWrapper::Push(const char_t &c,size_t size){
	size_t result=0;
	if(lock->Lock()){
    result=data->Push(c,size);
  	lock->Unlock();
 	}
	return result;
}

size_t DataWrapper::Push(const std::string& data){
	size_t result=0;
	if(lock->Lock()){
		result=this->data->Push(data);
		lock->Unlock();
	}
	return result;
}

EnumResult_t DataWrapper::SetDestroyData(bool value){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		destroyData=value;
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
}

bool DataWrapper::GetDestroyData(){
  return destroyData;
}
