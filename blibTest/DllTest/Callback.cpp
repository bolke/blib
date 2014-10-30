#include "Callback.h"
#include "RawParser.h"
#include "StringParser.h"

using namespace blib;

CallbackTemp::CallbackTemp(){
  returnRef=NULL;
	returnTypeInfo=&typeid(void);
}

size_t CallbackTemp::GetNrOfParameters(void){
	return parameters.size();
}

void* CallbackTemp::GetReturnRef(){
  return returnRef;
}

const std::type_info* CallbackTemp::GetParamTypeInfo(size_t nr){
	const std::type_info* result;
	if(parametersTypeInfo.size()>nr)
		result=parametersTypeInfo[nr];
	else
		result=&typeid(void);
	return result;
}

EnumResult_t CallbackTemp::SetParameter(size_t nr,void* a){	
	EnumResult_t result=FAIL;
	if(parameters.size()>nr){
		parameters[nr]=a;
		result=SUCCESS;
	}
	return result;
}

EnumResult_t CallbackTemp::SetParamFromString(size_t nr,std::string value){
  return RawParser::SetVariable(value,GetEnumVar(GetParamTypeInfo(nr)),*((char*)parameters[nr]),0);
}

EnumResult_t CallbackTemp::SetParamsFromString(std::string value){
  EnumResult_t result=FAIL;
  std::vector<std::string> parameters=StringParser::SplitIntoArguments(value);
  if(parameters.size()==GetNrOfParameters()){
    for(size_t i=0;i<parameters.size();i++){
      if(SetParamFromString(i,parameters[i])==FAIL){
        result=FAIL;
        break;
      }
    }
  }
  return result;
}

const std::type_info* CallbackTemp::GetReturnTypeInfo(void){								
  return returnTypeInfo;
}
