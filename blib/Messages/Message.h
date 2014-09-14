#ifndef BLIB_MESSAGE_H
#define BLIB_MESSAGE_H

#include "Core.h"

namespace blib{

class Message:public DataStructure{
protected:
	DataBuffer buffer;	
public:
	Message();																											
	virtual size_t Size();																					//size of data
  virtual size_t Pop(char_t& c,size_t size=1);										//pop data according to preformed structure, according to structure
  virtual size_t Pop(std::string& data);													//pop data according to preformed structure
  virtual size_t Push(const char_t &c,size_t size=1);							//push data in preformed structure
  virtual size_t Push(const std::string& data);										//push data in preformed structure
	
	virtual DataBuffer& GetData();																	//returns data vector reference

	virtual EnumResult_t AddVariable(const void* variable,const EnumVar_t type);				//push variable of given data type
	virtual EnumResult_t AddVariable(const std::string value, const EnumVar_t type);		//push data of given type in string form
	
	virtual EnumResult_t PushVariable(const void* variable);        //add variable of expected type
	virtual EnumResult_t PushVariable(const std::string& value);    //add variable in string form
	virtual EnumResult_t PopVariable(void* variable);               //pop variable pointer to expected type
	virtual EnumResult_t PopVariable(std::string& value);						//pop variable to string

	virtual EnumVar_t NextVariable();																//what is the next variable

	virtual bool IsEmpty();																					//buffer empty?
	virtual bool IsFull();																					//buffer full?
};

};

#endif
