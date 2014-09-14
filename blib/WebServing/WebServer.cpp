#include "WebServer.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <sstream>
#include <algorithm>

using namespace blib;
using namespace mongoose;

#include <tchar.h>

std::string CurrentPath(){
  std::string result;
  TCHAR pBuf[2049];
  int32_t len=2048;
  int bytes = GetModuleFileName(NULL, pBuf, len);
  if(bytes>0){
    std::wstring wstr(pBuf);
    result.assign(wstr.begin(),wstr.end());
    std::replace(result.begin(),result.end(),'\\','/');
    uint32_t pos=result.find_last_of("/");
    result=result.substr(0,result.find_last_of("/"));    
  }
  return result;
}

WebServer::WebServer(){
  setOption("document_root","www");
  setOption("listening_ports","8888");
  setOption("num_threads","5");
  webRequestHandler=NULL;
}

WebServer::~WebServer(){
}

size_t WebServer::Size(){
  return 0;
}

bool WebServer::handleEvent(ServerHandlingEvent eventCode,MongooseConnection &connection,const MongooseRequest &request, MongooseResponse &response){
  bool result=false;    
  if(lock->Lock()){
   // if(eventCode==MG_NEW_REQUEST){
			if(webRequestHandler!=NULL){
				this->connection=&connection;
				this->request=&request;
				this->response=&response;
        result=webRequestHandler->ParseRequest(eventCode,connection,request,response);
				this->connection=NULL;
				this->request=NULL;
				this->response=NULL;				
			}
   // }
    lock->Unlock();
  }
  return result;
}

EnumResult_t WebServer::Open(){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(!IsOpen()){
      start();
			if(IsOpen()){
				isOpen=true;
        result=SUCCESS;
			}
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t WebServer::Close(){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){
    if(IsOpen())
      stop();     
    if(!IsOpen())
      result=SUCCESS;
    lock->Unlock();
  }
  return result;
}

bool WebServer::IsOpen(){
  bool result=false;
  if(lock->Lock()){
    result=isRunning();
		isOpen=result;
    lock->Unlock();
  }
  return result;
}

EnumResult_t WebServer::SetRelativePath(std::string relativePath){
  EnumResult_t result=FAIL;
  if(!IsOpen()){
    std::string path=CurrentPath();
    if(relativePath.size()>0){
      if(relativePath[0]!='/')
        path.append("/");        
      if(relativePath.size()>1){
        if(relativePath[relativePath.length()-1]!='/')
          relativePath.append("/");
      }        
      path.append(relativePath);
    }
    setOption("document_root",path.c_str());
  }      
  return result;
}

size_t WebServer::Push(const char_t& c,size_t size){
  return 0;
}

size_t WebServer::Pop(std::string& data){
  return Device::Pop(data);
}

size_t WebServer::Pop(char_t& c,size_t size){
  return 0;
}

size_t WebServer::Push(const std::string& data){
  return Device::Push(data);
}

EnumResult_t WebServer::SetParameter(const std::string parameter,const std::string value){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    setOption(parameter,value);
    result=SUCCESS;
    lock->Unlock();
  }
  return result;
}

EnumResult_t WebServer::SetWebRequestHandler(WebRequestHandler* handler){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    this->webRequestHandler=handler;
    if(handler!=NULL)
      result=SUCCESS;
    lock->Unlock();
  }
  return result;
}

WebRequestHandler* WebServer::GetWebRequestHandler(){
  WebRequestHandler* result=NULL;
  if(lock->Lock()){
    result=webRequestHandler;
    lock->Unlock();
  }
  return result;
}

mongoose::MongooseConnection* WebServer::GetMongooseConnection(){
	mongoose::MongooseConnection* result=NULL;
	if(lock->GetOwner()==GetCurrentThreadId())
		result=connection;	
	return result;
}

const mongoose::MongooseRequest* WebServer::GetMongooseRequest(){
	const mongoose::MongooseRequest* result=NULL;	
	if(lock->GetOwner()==GetCurrentThreadId())
		result=request;	
	return result;
}

mongoose::MongooseResponse* WebServer::GetMongooseResponse(){
	mongoose::MongooseResponse* result=NULL;
	if(lock->GetOwner()==GetCurrentThreadId())
		result=response;	
	return result;
}
