#ifndef BLIB_DATAWRAPPER_H
#define BLIB_DATAWRAPPER_H

#include "Data.h"
#include "Device.h"

namespace blib{
class DataWrapper:public Device, public Base{											//wraps the data into a device, making it useable as device. open/close always toggles isOpen flag.										
protected:	
	bool destroyData;																								//destroy flag
  Data* data;																											//data pointer
public:	
  BLIB_LIB_API DataWrapper(Data& d,bool destroyData=false);										//add data, default don't destroy
  BLIB_LIB_API virtual ~DataWrapper();																					//check destroyData, destroys accordingly
  BLIB_LIB_API virtual size_t Size();																					//size of data available
	BLIB_LIB_API virtual EnumResult_t SetDestroyData(bool value);								
	BLIB_LIB_API virtual bool GetDestroyData();
  BLIB_LIB_API virtual size_t Pop(char_t& c,size_t size=1);
  BLIB_LIB_API virtual size_t Pop(std::string& data);	
  BLIB_LIB_API virtual size_t Push(const char_t &c,size_t size=1);  
	BLIB_LIB_API virtual size_t Push(const std::string& data);
};

};

#endif
