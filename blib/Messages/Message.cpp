#include "Message.h"

using namespace blib;

Message::Message():DataStructure(*this,false){	
}

std::vector<char_t>& Message::GetData(){
	return buffer;
}

size_t Message::Size(){
  size_t result=0;
	if(lock->Lock()){
		result=buffer.size();
		lock->Unlock();
	}
	return result;
}

size_t Message::Pop(std::string& data){
	return DataStructure::Pop(data);
}

size_t Message::Pop(char_t& c,size_t size){
	return size;
}

size_t Message::Push(const char_t &c,size_t size){
	return DataStructure::Push(c,size);
}

size_t Message::Push(const std::string& data){
	return DataStructure::Push(data);
}

EnumResult_t Message::PushVariable(const std::string value, const EnumVar_t type){
  EnumResult_t result=FAIL;
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