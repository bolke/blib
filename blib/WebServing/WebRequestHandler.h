#ifndef BLIB_WEBREQUESTHANDLER_H
#define BLIB_WEBREQUESTHANDLER_H

#include "Core.h"
#include "Mongoose.h"
#include "mongcpp.h"
#include "Network.h"

namespace blib{

class WebRequestHandler{
protected:
  mongoose::MongooseRequest* request;
  mongoose::MongooseConnection* connection;
  mongoose::MongooseResponse* response;
	virtual size_t ExtractVariables(std::string queryString,const mongoose::MongooseRequest &request,std::vector<std::pair<std::string,std::string>> &variables);
	virtual EnumResult_t HandleRequest(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseResponse &response,std::string uri,std::vector<std::pair<std::string,std::string>> &variables)=0;
public:
  virtual ~WebRequestHandler();
  virtual bool ParseRequest(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseConnection &connection,const mongoose::MongooseRequest &request, mongoose::MongooseResponse &response);
};

/*void WebServer::handleInfo(const MongooseRequest &request,MongooseResponse &response){
  response.setStatus(200);
  response.setConnectionAlive(false);
  response.setCacheDisabled();
  response.setContentType("text/html");
  response.addContent(generateInfoContent(request));
  response.write();
}

const std::string WebServer::generateInfoContent(const MongooseRequest &request){
  std::string result;
  result = "<h1>Sample Info Page</h1>";
  result += "<br />Request URI: " + request.getUri();
  result += "<br />Your IP: " + IpToString(request.getRemoteIp());

  time_t tim;
  time(&tim);

  result += "<br />Current date & time: " + toString(ctime(&tim));
  result += "<br /><br /><a href=\"/\">Index page</a>";

  return result;
}
*/

};

#endif
