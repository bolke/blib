#ifndef BLIB_MESSAGE_H
#define BLIB_MESSAGE_H

#include "Core.h"

namespace blib{

class Message:public Data{
protected:
	std::vector<EnumVar_t> structure;																//data structure, in case of variables
	std::vector<char_t> data;																				//buffer for data
	uint32_t headerSize;																						//size of header in bytes
	uint32_t footerSize;																						//size of footer in bytes
public:
	Message(uint32_t headerSize=0,uint32_t footerSize=0);						//size of header and footer in bytes
	virtual std::vector<char_t>& GetData();													//returns data vector reference
	virtual size_t Size();																					//size of payload, header and footer data are ignored
  virtual size_t Pop(char_t& c,size_t size=1);										//pop data from payload
  virtual size_t Pop(std::string& data);													//pop data from payload
  virtual size_t Push(const char_t &c,size_t size=1);							//push data in
  virtual size_t Push(const std::string& data);										//same 
	virtual uint32_t GetHeaderSize();																//getter headerSize
	virtual uint32_t GetFooterSize();																//getter footerSize
	virtual EnumResult_t SetHeaderSize(uint32_t headerSize);				//setter headerSize
	virtual EnumResult_t SetFooterSize(uint32_t footerSize);				//setter footerSize
  virtual size_t PopHeader(char_t& c,size_t size=1);							//pop's header if buffer is eq or lgt headerSize,on success returns headerSize
	virtual size_t PopFooter(char_t& c,size_t size=1);							//pop's footer if buffer is eq or lgt headerSize,on success returns footerSize
	virtual bool IsHeaderValid();																		//headerSize<=data size
	virtual bool IsFooterValid();																		//headerSize+footerSize<=data size
	virtual bool IsValid();																					//return IsHeaderValid()&&IsFooterValid()
	virtual std::vector<EnumVar_t>& GetStructure();									//return data structure	
	virtual EnumResult_t PushVariable(const std::string value, const EnumVar_t type);
	virtual EnumResult_t PopVariable(std::string& value,const EnumVar_t type);
};

};

#endif
