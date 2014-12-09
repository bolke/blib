#ifndef BLIB_FILEINTERFACE_H
#define BLIB_FILEINTERFACE_H

#include <stdio.h>
#include <iostream>
#include <fstream>

#ifdef LINUX
#include <sys/io.h>
#else
#include <io.h>
#define F_OK 00
#endif

#include "Core.h"

namespace blib{

class FileInterface:public Device,public Base{
protected:
  std::ios_base::openmode filemode;
  std::string filename;
  std::fstream file;
public:
  FileInterface(std::string filename="",std::ios_base::openmode filemode=std::ios::in);

  virtual EnumResult_t Open(void);
  virtual EnumResult_t Close(void);
  virtual size_t Size(void);
  virtual bool IsOpen(void);
 
  virtual std::string GetFilename();
  virtual EnumResult_t SetFilename(std::string filename);
  virtual std::ios_base::openmode GetFilemode();
  virtual EnumResult_t SetFilemode(std::ios_base::openmode filemode=std::ios::in);

  virtual size_t Pop(char_t& c,size_t size=1);  
  virtual size_t Pop(std::string& data);
  
  virtual size_t Push(const char_t &c,size_t size=1);  
  virtual size_t Push(const std::string& data);

	virtual std::fstream& GetFileStream();
};

};

#endif
