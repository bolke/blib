#ifndef BLIB_FILEIO_H
#define BLIB_FILEIO_H

#include "Core.h"
#include "FileInterface.h"
#include "ReplayFile.h"
#include "SaveFile.h"

namespace blib{
	EnumResult_t GetFiles(std::string path,std::vector<std::string>& files,size_t depth=9999);
	EnumResult_t GetDirectories(std::string path,std::vector<std::string>& paths,size_t depth=9999);
	bool IsDirectory(std::string path);
};

#endif
