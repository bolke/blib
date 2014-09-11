#include "Message.h"

using namespace blib;

Message::Message():DataStructure(buffer,false){	
}

DataBuffer& Message::GetData(){
	return buffer;
}

size_t Message::Size(){
  size_t result=0;
	if(lock->Lock()){
		result=buffer.Size();
		lock->Unlock();
	}
	return result;
}

size_t Message::Pop(std::string& data){
	return DataStructure::Pop(data);
}

size_t Message::Pop(char_t& c,size_t size){
	return DataStructure::Pop(c,size);
}

size_t Message::Push(const char_t &c,size_t size){
	return DataStructure::Push(c,size);
}

size_t Message::Push(const std::string& data){
	return DataStructure::Push(data);
}

EnumResult_t Message::PushVariable(const std::string value, const EnumVar_t type){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(IsFull()||(IsEmpty()&&(structure.size()==0))){
			if(AddVariable(type)==SUCCESS){				
				if(type==STRING_T)
					Push(value);
				else{					
					size_t expectedSize=GetSize(type);
				  if(expectedSize>0){
				    char_t* c=new char_t[expectedSize];
						if(RawParser::SetVariable(value,type,c[0],0)==SUCCESS)
							if(Push(c[0],expectedSize)==expectedSize)
								result=SUCCESS;
						delete[] c;
					}
				}
			}
		}
	  lock->Unlock();
	}
	return result;
}

EnumResult_t Message::PushVariable(const void* variable,const EnumVar_t type){
  EnumResult_t result=FAIL;
	if(lock->Lock()){		
		if(IsFull()||(IsEmpty()&&(structure.size()==0))){
			if(type!=STRING_T){
				size_t expectedSize=GetSize(type);
				if(expectedSize>0){
					if(AddVariable(type)==SUCCESS)
					  if(Push(*((const char_t*)variable),expectedSize)==expectedSize)
						  result=SUCCESS;				
				}
			}else{
				result=PushVariable(*((std::string*)variable),type);
			}
		}
	  lock->Unlock();
	}
	return result;
}

bool Message::IsEmpty(){
	return Size()==0;
};

bool Message::IsFull(){
	bool result=false;
	if(lock->Lock()){
		result=(Size()>0)&&(popIt==structure.end());
		lock->Unlock();
	};
	return result;
};