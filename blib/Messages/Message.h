#ifndef BLIB_MESSAGE_H
#define BLIB_MESSAGE_H

#include "Core.h"

namespace blib{

class Message:public Data{
protected:
  size_t pos;																											//current position of data pointer
	std::map<size_t,EnumVar_t> structure;														//data structure complete with offset	
	std::vector<char_t> data;																				//buffer for data	
public:
	Message();																											
	virtual size_t Size();																					//size of data
  virtual size_t Pop(char_t& c,size_t size=1);										//pop data
  virtual size_t Pop(std::string& data);													//pop data
  virtual size_t Push(const char_t &c,size_t size=1);							//push data in preformed structure
  virtual size_t Push(const std::string& data);										//push data in preformed structure
	
	virtual std::vector<char_t>& GetData();													//returns data vector reference
	virtual std::vector<EnumVar_t>& GetStructure();									//return data structure	
	
	virtual EnumResult_t PushVariable(const void* variable,const EnumVar_t type);				//push variable of given data type
	virtual EnumResult_t PushVariable(const void* variable,const type_info* type);			//push variable of given datatype
	virtual EnumResult_t PushVariable(const std::string value, const EnumVar_t type);		//push data of given type in string form
};

};

#endif
