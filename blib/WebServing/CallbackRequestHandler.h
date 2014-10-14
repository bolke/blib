#ifndef BLIB_CALLBACKREQUESTHANDLER_H
#define BLIB_CALLBACKREQUESTHANDLER_H

#include "WebRequestHandler.h"

namespace blib{

class CallbackRequestHandler:public WebRequestHandler,public Base{
protected:
	bool triggerOnUri;
	std::string triggerVar;
	std::map<std::string,CallbackTemp*> callbacks;
	virtual EnumResult_t HandleRequest(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseResponse &response,std::string uri,std::vector<std::pair<std::string,std::string>> &variables);
public:
	CallbackRequestHandler();
  std::map<std::string,CallbackTemp*>& GetCallbacks();
	bool GetTriggerOnUri();
	EnumResult_t SetTriggerOnUri(bool value);
	EnumResult_t SetTriggerVar(const std::string value);
	std::string GetTriggerVar();
};

};

#endif
