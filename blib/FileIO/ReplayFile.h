#ifndef BLIB_REPLAYFILE_H
#define BLIB_REPLAYFILE_H

#include "FileInterface.h"

namespace blib{

class ReplayFile:public DeviceOpener{
protected:
  FileInterface* file;																						//connection to the file
public:
  ReplayFile(std::string filename="");
  
  virtual size_t Pop(char_t& c,size_t size=1);  
  virtual size_t Pop(std::string& data);
  virtual size_t Push(const char_t &c,size_t size=1);  
  virtual size_t Push(const std::string& data); 
  
  virtual std::string GetFilename();
  virtual EnumResult_t SetFilename(std::string filename);

  virtual int32_t GetFilemode();

  virtual bool IsBinairy();
  virtual EnumResult_t SetBinairy(bool value);
};

};

#endif
