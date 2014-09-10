#ifndef BLIB_DATASTRUCTURE_H
#define BLIB_DATASTRUCTURE_H

#include "DataWrapper.h"

namespace blib{

class DataStructure:public DataWrapper{
protected:
	std::vector<EnumVar_t>::iterator popIt;
	std::vector<EnumVar_t> structure;
public:
	DataStructure(Data& d,bool destroyData=false);
	virtual size_t Size();
	virtual size_t Pop(char_t& c,size_t size=1);
  virtual size_t Pop(std::string& data);	
  virtual size_t Push(const char_t &c,size_t size=1);  
	virtual size_t Push(const std::string& data);
	virtual EnumResult_t AddVariable(const EnumVar_t variable);
	virtual const std::vector<EnumVar_t>& GetStructure();
};

};

#endif
