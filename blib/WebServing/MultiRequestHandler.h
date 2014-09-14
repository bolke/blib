#ifndef BLIB_MULTIREQUESTHANDLER_H
#define BLIB_MULTIREQUESTHANDLER_H

#include "Core.h" 
#include "WebRequestHandler.h" 

namespace blib{

class MultiRequestHandler:public WebRequestHandler,public Base{
protected:
  std::map<mongoose::ServerHandlingEvent,WebRequestHandler*> handlers;
  virtual EnumResult_t HandleRequest(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseResponse &response,std::string uri,std::vector<std::pair<std::string,std::string>> &variables);
public:
  virtual bool ParseRequest(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseConnection &connection,const mongoose::MongooseRequest &request, mongoose::MongooseResponse &response);
  std::map<mongoose::ServerHandlingEvent,WebRequestHandler*>& GetHandlers();
};

};

#endif