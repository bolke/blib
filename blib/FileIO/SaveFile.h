#ifndef BLIB_SAVEFILE_H
#define BLIB_SAVEFILE_H

#include "FileInterface.h"

namespace blib{

class SaveFile:public FileInterface{
protected:
	int32_t fileCnt;
	bool useHardSizes;
	size_t fileSize;
	size_t maxFileSize;
	std::string realFilename;
public:
	SaveFile(std::string filename="",size_t maxFileSize=DEFAULT_BUFFER_SIZE);
 
  virtual EnumResult_t SetFilename(std::string filename);
  virtual EnumResult_t SetFilemode(int32_t filemode);

  virtual size_t Push(const char_t &c,size_t size=1);
  virtual size_t Push(const std::string& data);

	virtual bool GetUseHardSizes();
	virtual EnumResult_t SetUseHardSizes(bool useHardSizes);

	virtual size_t GetMaxFileSize();
	virtual EnumResult_t SetMaxFileSize(size_t maxFileSize);

};

};

#endif
