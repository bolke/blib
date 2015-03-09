#ifndef BLIB_DATA_H
#define BLIB_DATA_H

#include <iostream>
#include <stdio.h>
#include "Basis.h"
#include "BaseDefines.h"

namespace blib{

class Data{
public:
	BLIB_LIB_API Data();

	BLIB_LIB_API virtual size_t Size()=0;
  BLIB_LIB_API virtual size_t Pop(char_t& c,size_t size=1)=0;
  BLIB_LIB_API virtual size_t Pop(std::string& data);
  BLIB_LIB_API virtual size_t Push(const char_t &c,size_t size=1)=0;
  BLIB_LIB_API virtual size_t Push(const std::string& data);

	BLIB_LIB_API virtual Data& operator>>(Data& device);
  BLIB_LIB_API virtual Data& operator<<(Data& device);
	BLIB_LIB_API virtual Data& operator>>(std::string& data);
	BLIB_LIB_API virtual Data& operator<<(const std::string& data);

	BLIB_LIB_API friend std::istream& operator>>(std::istream &stream,Data &output){
		char_t* data=NULL;
		size_t pos;
		size_t size;
		if(stream.good()){
			pos=stream.tellg();
			if(pos==-1){
				char_t c=stream.get();
				if(c!=EOF)
					output.Push(c,1);
			}else{
				stream.seekg(0,stream.end);
				size=stream.tellg();
				if(size>-1){
					stream.seekg(pos);
					size=size-pos;
					if(size>0){
						data=new char_t[size];
						stream.readsome(data,size);							//ignore warning, parameters are safe
						size=stream.gcount();
						output.Push(*data,size);
						delete[] data;
					}
				}
			}
		}
		return stream;
	};

	BLIB_LIB_API friend std::ostream& operator<<(std::ostream& stream,Data& input){
    size_t size=input.Size();
    if(size>0){
      char_t* data=new char_t[size];
      size_t dataRead=input.Pop(*data,size);
      if(dataRead>0)
        stream.write(data,dataRead);
      delete[] data;
    }
    return stream;
  };
};

};

#endif
