#include "MultiRequestHandler.h"

using namespace blib;

std::map<mongoose::ServerHandlingEvent,WebRequestHandler*>& MultiRequestHandler::GetHandlers(){
  return handlers;
}

EnumResult_t MultiRequestHandler::HandleRequest(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseResponse &response,std::string uri,std::vector<std::pair<std::string,std::string>> &variables){
  EnumResult_t result=FAIL;
  return result;
}

bool MultiRequestHandler::ParseRequest(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseConnection &connection,const mongoose::MongooseRequest &request, mongoose::MongooseResponse &response){
  EnumResult_t result=FAIL;
  std::map<mongoose::ServerHandlingEvent,WebRequestHandler*>::iterator wIt;
  wIt=handlers.find(eventCode);
  if(wIt!=handlers.end())
    if(wIt->second->ParseRequest(eventCode,connection,request,response))
      result=SUCCESS;
  return result==SUCCESS;  
}
