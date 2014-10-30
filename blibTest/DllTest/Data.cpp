#include "Data.h"

using namespace blib;

Data::Data(){
}

size_t Data::Pop(std::string& data){
  size_t result=0;
	result=Size();
	if(result>DEFAULT_BUFFER_SIZE)
		result=DEFAULT_BUFFER_SIZE;
	char_t* buffer=new char_t[result];
	result=Pop(*buffer,result);
	if(result>DEFAULT_BUFFER_SIZE)
		result=0;
	if(result>0)
		data.assign(buffer,result);
	else
		data.assign("");
	delete buffer;
  return result;
}

size_t Data::Push(const std::string& data){  
  return Push(*(data.c_str()),data.length());
}


Data& Data::operator>>(Data& device){  
	char_t data[DEFAULT_BUFFER_SIZE];	
  size_t read=Pop(data[0],DEFAULT_BUFFER_SIZE);
  if(read>0)
    device.Push(data[0],read);
  return *this;
}

Data& Data::operator<<(Data& device){
  device>>(*this);
  return *this;
}

Data& Data::operator>>(std::string& data){
	Pop(data);
  return *this;
}

Data& Data::operator<<(const std::string& data){
	Push(data);
	return *this;
}