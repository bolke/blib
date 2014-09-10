#include "DataStructure.h"

using namespace blib;

DataStructure::DataStructure(Data& d,bool destroyData):DataWrapper(d,destroyData){
	popIt=structure.end();
}

size_t DataStructure::Size(){
	return data->Size();
}

size_t DataStructure::Pop(char_t& c,size_t size){
	size_t result=0;
	size_t expectedSize=0;
	if(popIt!=structure.end()){
		if(*popIt==STRING_T){
			char2_int16_t length;
			if(data->Pop(length.c[0],2)==2)
				expectedSize=length.u_value;
		}else
			expectedSize=GetSize(*popIt);
		if((expectedSize>0)&&(size>=expectedSize)){
			result=data->Pop(c,expectedSize);
			popIt++;
			if(popIt!=structure.end()){
				if(*popIt!=STRING_T){
					if(result<size)
			      result=result+Pop((&c)[result],size-result);
				}
			}
		}
	}
	return result;
}

size_t DataStructure::Pop(std::string& data){
	return DataWrapper::Pop(data);
}

size_t DataStructure::Push(const char_t &c,size_t size){
	size_t result=0;
	if(popIt==structure.end()){
		if(this->data->Size()==0)
			popIt=structure.begin();
	}
	if(size>0){
		if(popIt!=structure.end()){	
			size_t expectedSize=0;
			if(*popIt==STRING_T)
				expectedSize=size;
			else
				expectedSize=GetSize(*popIt);
			if((expectedSize>0)&&(expectedSize<=size)){
				result=data->Push(c,expectedSize);
			  popIt++;
				if(popIt!=structure.end()){
					if((*popIt)!=STRING_T){
						if((size-result)>0)
						  result=result+Push((&c)[result],size-result);
					}
				}
			}
		}
	}
	return result;
}

size_t DataStructure::Push(const std::string& data){
	return Push(*(data.c_str()),data.length());
}

EnumResult_t DataStructure::AddVariable(const EnumVar_t variable){
	EnumResult_t result=FAIL;
	if((structure.size()==0)||(popIt==structure.begin())){
		structure.push_back(variable);
		popIt=structure.begin();
		result=SUCCESS;
	}
	return SUCCESS;
}

const std::vector<EnumVar_t>& DataStructure::GetStructure(){
	return structure;
}
