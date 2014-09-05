#include "Message.h"

using namespace blib;

Message::Message(){	
}

std::vector<char_t>& Message::GetData(){
	return data;
}

size_t Message::Size(){
	size_t result=data.size();
	return result;
}

size_t Message::Pop(std::string& data){
	return Data::Pop(data);
}

size_t Message::Pop(char_t& c,size_t size){

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

EnumResult_t Message::PushVariable(const std::string value, const EnumVar_t type){
  EnumResult_t result=FAIL;
	return result;
}

std::vector<EnumVar_t> Message::GetStructure(){
	std::vector<EnumVar_t> result;
	std::map<size_t,EnumVar_t>::iterator mIt=structure.begin();
	while(mIt!=structure.end()){
		result.push_back(mIt->second);
		mIt++;
	}
	return result;
}

