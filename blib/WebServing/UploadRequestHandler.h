#ifndef BLIB_UPLOADREQUESTHANDLER_H
#define BLIB_UPLOADREQUESTHANDLER_H

#include "FileIO.h"
#include "WebRequestHandler.h"

namespace blib{

class UploadRequestHandler:public WebRequestHandler,public Base{
protected:
	FileInterface* fi;
  std::string uploadFolder;
	std::string tempFolder;
	EnumResult_t HandleRequest(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseResponse &response,std::string uri,std::vector<std::pair<std::string,std::string>> &variables);
public:
	UploadRequestHandler();
	std::string GetUploadFolder();
	std::string GetTempFolder();
	EnumResult_t SetUploadFolder(std::string uploadFolder);
	EnumResult_t SetTempFolder(std::string tempFolder);
};

};

#endif
