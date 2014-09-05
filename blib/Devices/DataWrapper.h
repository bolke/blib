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
  DataWrapper(Data& d,bool destroyData=false);										//add data, default don't destroy
  virtual ~DataWrapper();																					//check destroyData, destroys accordingly
  virtual size_t Size();																					//size of data available
	virtual EnumResult_t SetDestroyData(bool value);								
	virtual bool GetDestroyData();
  virtual size_t Pop(char_t& c,size_t size=1);  
  virtual size_t Pop(std::string& data);	
  virtual size_t Push(const char_t &c,size_t size=1);  
	virtual size_t Push(const std::string& data);
};

};

#endif
