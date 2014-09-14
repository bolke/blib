#include "CallbackRequestHandler.h" 

using namespace blib;

EnumResult_t CallbackRequestHandler::HandleRequest(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseResponse &response,std::string uri,std::vector<std::pair<std::string,std::string>> &variables){
  EnumResult_t  result=FAIL;
	std::map<std::string,CallbackTemp*>::iterator cIt=callbacks.end();

	if(triggerOnUri)
		cIt=callbacks.find(StringParser::After(uri,"/"));    
	else if(variables.size()>0){
		cIt=callbacks.find(variables[0].second);		
		variables.erase(variables.begin());
	}

  if(cIt!=callbacks.end()){
    if(cIt->second->GetNrOfParameters()==variables.size()){
      result=SUCCESS;
      for(size_t i=0;i<variables.size();i++){
        result=cIt->second->SetParamFromString(i,variables[i].second);
        if(result==FAIL)
          break;
      }
			if(result==SUCCESS){
        result=cIt->second->Callback();
				if(result==SUCCESS){
					response.setStatus(200);
					response.write();
				}
			}
    }
  }

	return result;
};

std::map<std::string,CallbackTemp*>& CallbackRequestHandler::GetCallbacks(){
  return callbacks;
}

CallbackRequestHandler::CallbackRequestHandler(){
  triggerOnUri=false;
}

bool CallbackRequestHandler::GetTriggerOnUri(){
  return triggerOnUri;
}

EnumResult_t CallbackRequestHandler::SetTriggerOnUri(bool value){
	triggerOnUri=value;
	return SUCCESS;
}
