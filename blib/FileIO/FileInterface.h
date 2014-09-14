#ifndef BLIB_FILEINTERFACE_H
#define BLIB_FILEINTERFACE_H

#include <stdio.h>
#include <iostream>
#include <fstream>

#include "Core.h"

namespace blib{

class FileInterface:public Device,public Base{
protected:
	int32_t filemode;  
  std::string filename;
  std::fstream file;
public:
  FileInterface(std::string filename="",int32_t filemode=std::fstream::in);

  virtual EnumResult_t Open(void);
  virtual EnumResult_t Close(void);
  virtual size_t Size(void);
  virtual bool IsOpen(void);
 
  virtual std::string GetFilename();
  virtual EnumResult_t SetFilename(std::string filename);
  virtual int32_t GetFilemode();
  virtual EnumResult_t SetFilemode(int32_t filemode);

  virtual size_t Pop(char_t& c,size_t size=1);  
  virtual size_t Pop(std::string& data);
  
  virtual size_t Push(const char_t &c,size_t size=1);  
  virtual size_t Push(const std::string& data);

	virtual std::fstream& GetFileStream();
};

};

#endif
