#include "DeviceBuffer.h"

using namespace blib;

DeviceBuffer::DeviceBuffer(blib::Device &d,size_t popSize,size_t pushSize):DeviceWrapper(d){
	this->popSize=popSize;
	this->pushSize=pushSize;
}

size_t DeviceBuffer::Pop(char_t& c,size_t size){
	size_t result=0;
	if(size>0){
		if(lock->Lock()){	
			if(popSize>=1){
				if(popBuffer.size()<popSize){
					size_t toRead=popSize-popBuffer.size();
				  char_t* temp=new char_t[toRead];
					size_t tempRead=device->Pop(*temp,toRead);
					for(size_t i=0;i<tempRead;i++){
						popBuffer.push(temp[i]);
					}
				}
				if(popBuffer.size()>=popSize){
					size_t toWrite=popSize;
					for(size_t i=0;i<popSize;i++){
						(&c)[i]=popBuffer.front();
					  popBuffer.pop();
				  }
					result=popSize;
				}
			}else
			  result=Pop(c,size);
			lock->Unlock();
		}
	}
	return result;
}

size_t DeviceBuffer::Pop(std::string& data){
	return DeviceWrapper::Pop(data);
}

size_t DeviceBuffer::Push(const char_t &c,size_t size){
	size_t result=0;
	if(size>0){
		if(lock->Lock()){
			if(pushBuffer.size()<pushSize){
				size_t toPush=pushSize-pushBuffer.size();
			  if(toPush>size)
					toPush=size;
				for(size_t i=0;i<toPush;i++)
					pushBuffer.push((&c)[i]);
			}
			if(pushBuffer.size()>=pushSize){
			  char_t* temp=new char_t[pushSize];
				for(size_t i=0;i<pushSize;i++){
				  temp[i]=pushBuffer.front();
				  pushBuffer.pop();
				}
				result=device->Push(*temp,pushSize);
				delete[] temp;
			}
			lock->Unlock();
		}
	}
	return result;
}

size_t DeviceBuffer::Push(const std::string& data){
	return DeviceWrapper::Push(data);
}
