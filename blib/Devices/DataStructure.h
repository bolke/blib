#ifndef BLIB_DATASTRUCTURE_H
#define BLIB_DATASTRUCTURE_H

#include "DataWrapper.h"

namespace blib{

class DataStructure:public DataWrapper{
protected:
	std::vector<EnumVar_t>::iterator popIt;
	std::vector<EnumVar_t> structure;
public:
	BLIB_LIB_API DataStructure(Data& d,bool destroyData=false);
	BLIB_LIB_API virtual size_t Size();
	BLIB_LIB_API virtual size_t Pop(char_t& c,size_t size=1);
  BLIB_LIB_API virtual size_t Pop(std::string& data);	
  BLIB_LIB_API virtual size_t Push(const char_t &c,size_t size=1);  
	BLIB_LIB_API virtual size_t Push(const std::string& data);
	BLIB_LIB_API virtual EnumResult_t AddVariable(const EnumVar_t variable);
	BLIB_LIB_API virtual const std::vector<EnumVar_t>& GetStructure();
};

};

#endif
