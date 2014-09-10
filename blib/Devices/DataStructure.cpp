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
	if(popIt==structure.end()){
		if(data->Size()>0)
		  popIt=structure.begin();
	}
	if(popIt!=structure.end()){
		size_t expectedSize=GetSize(*popIt);
		if(size>=expectedSize){
			if(data->Size()>=expectedSize){				
			  result=data->Pop(c,expectedSize);				
				popIt++;				
				if(result==expectedSize){
					if(popIt!=structure.end()){
						expectedSize=GetSize(*popIt);
						if((size-result)>=expectedSize)
							result=result+Pop(((&c)[result]),size-result);
					}
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
	if(popIt!=structure.end()){
		if(size>=GetSize(*popIt)){
			size_t expectedSize=GetSize(*popIt);			
			result=data->Push(c,expectedSize);
			if(result==expectedSize){		
				popIt++;
				if((size-result)>0)
					result=result+Push((&c)[result],size-result);
			}
		}
	}
	return result;
}

size_t DataStructure::Push(const std::string& data){
	return DataWrapper::Push(data);
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
