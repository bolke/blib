#include "WebRequestHandler.h"

using namespace blib;

size_t WebRequestHandler::ExtractVariables(std::string queryString,const mongoose::MongooseRequest &request,std::vector<std::pair<std::string,std::string>> &variables){
  size_t result=0;  
  StringParser sp;
  if(queryString.size()>0){
    std::string variable;
    size_t bufLength=queryString.size();
    size_t pos=0;
    char_t* buffer=new char_t[bufLength];
    while(queryString.size()>0){
      pos=sp.Position(queryString,"&");
      variable=sp.Before(queryString,"=");
      if(pos<variable.size())
        variable=sp.Before(variable,"&");
      mg_get_var(queryString.c_str(),bufLength,variable.c_str(),buffer,bufLength);
      variables.push_back(std::pair<std::string,std::string>(variable,buffer));
      queryString=sp.After(queryString,"&");
      result++;
    }            
    delete[] buffer;    
  }
  return result;
}

bool WebRequestHandler::ParseRequest(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseConnection &connection,const mongoose::MongooseRequest &request, mongoose::MongooseResponse &response){
  bool result=false;
  if(std::find(lastCalls.begin(),lastCalls.end(),(long int)connection.GetCreationTime())==lastCalls.end()){
    lastCalls.push_back(connection.GetCreationTime());
    this->request=&((mongoose::MongooseRequest)request);
    this->connection=&connection;
    this->response=&response;
    if(request.getRequestMethodCode()==mongoose::MongooseRequestMethodCode::rmcPost){
      std::vector<std::pair<std::string,std::string>> variables;
      std::string uri=request.getUri();
      ExtractVariables(request.readQueryString(),request,variables);
      result=HandleRequest(eventCode,response,uri,variables)==SUCCESS;    
    }else if(request.getRequestMethodCode()==mongoose::MongooseRequestMethodCode::rmcGet){            
      std::vector<std::pair<std::string,std::string>> variables;
      std::string uri=request.getUri();
      ExtractVariables(request.getQueryString(),request,variables);
      result=HandleRequest(eventCode,response,uri,variables)==SUCCESS;
    }
    this->request=NULL;
    this->connection=NULL;
    this->response=NULL;
  }else{
    if(lastCalls.size()>64)
      lastCalls.erase(lastCalls.begin());
  }
  return result;
}

WebRequestHandler::~WebRequestHandler(){
}
