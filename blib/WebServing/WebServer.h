#ifndef BLIB_WEBSERVER_H
#define BLIB_WEBSERVER_H

#include "Core.h"
#include "Mongoose.h"
#include "mongcpp.h"
#include "Network.h"
#include "WebRequestHandler.h"

namespace blib{

class WebServer:public mongoose::MongooseServer,public Device,public Base{
protected:  
  WebRequestHandler* webRequestHandler;
  bool handleEvent(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseConnection &connection,const mongoose::MongooseRequest &request, mongoose::MongooseResponse &response);
	mongoose::MongooseConnection* connection;
	const mongoose::MongooseRequest* request;
	mongoose::MongooseResponse* response;
public:
  WebServer();
  ~WebServer();
  EnumResult_t SetRelativePath(std::string relativePath);
  
  virtual EnumResult_t Open(void);
  virtual EnumResult_t Close(void);

  virtual bool IsOpen(void);

  virtual size_t Size();

  virtual size_t Pop(char_t& c,size_t size=1);
  virtual size_t Pop(std::string& data);

  virtual size_t Push(const char_t &c,size_t size=1);  
  virtual size_t Push(const std::string& data); 

  virtual EnumResult_t SetWebRequestHandler(WebRequestHandler* handler);
  virtual WebRequestHandler* GetWebRequestHandler();

  virtual EnumResult_t SetParameter(const std::string parameter,const std::string value);

	mongoose::MongooseConnection* GetMongooseConnection();
	const mongoose::MongooseRequest* GetMongooseRequest();
	mongoose::MongooseResponse* GetMongooseResponse();
};

};

#endif
