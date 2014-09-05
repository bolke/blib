#include "Message.h"

using namespace blib;

Message::Message(uint32_t headerSize,uint32_t footerSize){
	SetHeaderSize(headerSize);
	SetFooterSize(footerSize);
}

std::vector<char_t>& Message::GetData(){
	return data;
}

uint32_t Message::GetHeaderSize(){
  return headerSize;
}

EnumResult_t Message::SetHeaderSize(uint32_t headerSize){
	this->headerSize=headerSize;
	return SUCCESS;
}

size_t Message::Size(){
	size_t result=data.size();
	if(result>=headerSize){
		result-=headerSize;
	  if(result>=footerSize)
		  result-=footerSize;
		else
			result=0;
	}else
		result=0;
	return result;
}


size_t Message::Pop(std::string& data){
	return Data::Pop(data);
}

size_t Message::Pop(char_t& c,size_t size){
	if(size>Size())
		size=Size();
	if(size>0){
		std::copy(data.begin()+headerSize,data.begin()+headerSize+size,&c);
	  data.erase(data.begin()+headerSize,data.begin()+headerSize+size);
	}
	return size;
}

size_t Message::Push(const char_t &c,size_t size){
	if(size>0)
  	data.insert(data.end(),&c,(&c)+size);	
	return size;
}

size_t Message::Push(const std::string& data){
	return Data::Push(data);
}

size_t Message::PopHeader(char_t& c,size_t size){
	size_t result=0;
	if((size>=headerSize)&&(Message::Size()>=headerSize)){
	  size=headerSize;
		if(size>0){
			result=Pop(c,size);		
		}
	}
	return result;
}

uint32_t Message::GetFooterSize(){
	return footerSize;
}

EnumResult_t Message::SetFooterSize(uint32_t footerSize){
	this->footerSize=footerSize;
	return SUCCESS;
}

size_t Message::PopFooter(char_t& c,size_t size){
	size_t result=0;
	if((size>=footerSize)&&(Message::Size()>=(headerSize+footerSize))){
	  size=footerSize;
		if(size>0){
			result=footerSize;
			std::copy(data.begin()+(data.size()-footerSize),data.end(),&c);
			data.erase(data.begin()+(data.size()-footerSize),data.end());
		}
	}
	return result;
}

bool Message::IsHeaderValid(){
	return headerSize<=data.size();
}

bool Message::IsFooterValid(){
	return (headerSize+footerSize)<=data.size();
}

bool Message::IsValid(){
  return IsHeaderValid()&&IsFooterValid();
}

EnumResult_t Message::PushVariable(const std::string value, const EnumVar_t type){
  EnumResult_t result=FAIL;
	if(value.size()>0){
		char_t* buffer=NULL;
		size_t bufferSize=8;
		switch(type){
			case CHAR_T:
			case INT8_T:
			case UINT8_T:
				bufferSize=1;
				break;
			case INT16_T:
			case UINT16_T:
				bufferSize=2;
				break;
			case INT32_T:
			case UINT32_T:
			case FLOAT32_T:
				bufferSize=4;
				break;
			case STRING_T:
				bufferSize=value.size();
				break;		
		}
		buffer=new char_t[bufferSize];
		result=RawParser::SetVariable(value,type,*buffer);
		if(result==SUCCESS){
			if(type==STRING_T){
				char8_int64_t length;
				length.u_value=bufferSize;
				Push(length.c[0],8);
			}	
			Push(*buffer,bufferSize);
		}
		delete[] buffer;
	}
	if(result==SUCCESS)
		structure.push_back(type);
	return result;
}

EnumResult_t Message::PopVariable(std::string& value,const EnumVar_t type){
  EnumResult_t result=FAIL;
	if(Size()>0){
		EnumResult_t result=FAIL;	
		char_t* buffer=NULL;
		switch(type){
			case CHAR_T:		
				buffer=new char_t[1];
				if(Pop(*buffer)==1){
					value=StringParser::Assign(*buffer,1);
				  result=SUCCESS;
				}				
				break;
			case INT8_T:
				buffer=new char_t[1];
				if(Pop(*buffer)==1){
					value=StringParser::ToString("%i",buffer[0]);
				  result=SUCCESS;
				}
				break;
			case UINT8_T:
				buffer=new char_t[1];
				if(Pop(*buffer)==1){
					value=StringParser::ToString("%u",buffer[0]);
				  result=SUCCESS;
				}
				break;
			case INT16_T:
				buffer=new char_t[2];
				if(Pop(*buffer,2)==2){
					char2_int16_t data;
					memcpy((void*)(data.c),buffer,2);
					value=StringParser::ToString("%i",data.value);
				  result=SUCCESS;
				}				
				break;
			case UINT16_T:
				buffer=new char_t[2];
				if(Pop(*buffer,2)==2){
					char2_int16_t data;
					memcpy((void*)(data.c),buffer,2);
					value=StringParser::ToString("%u",data.u_value);
				  result=SUCCESS;
				}				
				break;
			case INT32_T:
			  buffer=new char_t[4];
				if(Pop(*buffer,4)==4){
					char4_int32_t data;
					memcpy((void*)(data.c),buffer,4);
					value=StringParser::ToString("%i",data.value);
				  result=SUCCESS;
				}				
				break;
			case UINT32_T:
				buffer=new char_t[4];
				if(Pop(*buffer,4)==4){
					char4_int32_t data;
					memcpy((void*)(data.c),buffer,4);
					value=StringParser::ToString("%u",data.u_value);
				  result=SUCCESS;
				}				
				break;			
			case INT64_T:
			case LONG_T:
			case LLONG_T:
				buffer=new char_t[8];
				if(Pop(*buffer,8)==8){
					char8_int64_t data;
					memcpy((void*)(data.c),buffer,8);
					value=StringParser::ToString("%li",data.value);
				  result=SUCCESS;
				}				
				break;
			case UINT64_T:
			case ULONG_T:
			case ULLONG_T:
				buffer=new char_t[8];
				if(Pop(*buffer,8)==8){
					char8_int64_t data;
					memcpy((void*)(data.c),buffer,8);
					value=StringParser::ToString("%lu",data.u_value);
				  result=SUCCESS;
				}				
				break;
			case FLOAT32_T:
				buffer=new char_t[4];
				if(Pop(*buffer,4)==4){
					char4_float32_t data;
					memcpy((void*)(data.c),buffer,4);
					value=StringParser::ToString("%f",data.value);
				  result=SUCCESS;
				}				
				break;			
			case FLOAT64_T:
			case LFLOAT64_T:
				buffer=new char_t[8];
				if(Pop(*buffer,8)==8){
					char8_float64_t data;
					memcpy((void*)(data.c),buffer,8);
					value=StringParser::ToString("%lf",data.value);
				  result=SUCCESS;
				}				
				break;
			case STRING_T:
				buffer=new char_t[8];
				if(Pop(*buffer,8)==8){
					size_t bufferSize=0;
					char8_int64_t length;
					memcpy(length.c,buffer,8);
					bufferSize=length.u_value;
					delete[] buffer;
					buffer=new char_t[bufferSize];
					if(bufferSize>0){
						if(Pop(*buffer,bufferSize)==bufferSize){
							value=StringParser::Assign(*buffer,bufferSize);					  
					    result=SUCCESS;
						}
					}
				}
				break;
		}
		if(buffer!=NULL)
			delete[] buffer;
	}
	if((structure.size()>0)&&(result)){
		if(structure.front()==type)
		  structure.erase(structure.begin());
	}
	return result;
}

std::vector<EnumVar_t>& Message::GetStructure(){
	return structure;
}
