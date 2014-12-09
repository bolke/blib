#include <stdio.h>

#include "blib.h"

using namespace blib;

std::vector<std::string> webJsons;

class JsonWebRequestHandler:public WebRequestHandler{
protected:
	virtual EnumResult_t HandleRequest(mongoose::ServerHandlingEvent eventCode,mongoose::MongooseResponse &response,std::string uri,std::vector<std::pair<std::string,std::string>> &variables){
		if(variables.size()>0){
			if(StringParser::Compare(variables[0].first,"jsonValue")){				
				std::cout<<"WEB JSON\r\n";
				response.setStatus(200);
				response.setConnectionAlive(false);
				response.setCacheDisabled();
				response.setContentType("text/html");
				response.addContent("OK");
				response.write();
				webJsons.push_back(variables[0].second);				
			}else{
				std::cout<<"NO WEB JSON\r\n";
			}
		}
	  return FAIL;
	};
public:
};

int32_t main(int32_t argc, char_t* argv[]){
	WebServer web;
	web.SetWebRequestHandler(new JsonWebRequestHandler());
	web.Open();
	SerialPort s("COM13");
	DeviceOpener serial(s);		
	while(1){
		std::string data;
		while(serial.Pop(data)>0){
			std::cout<<data;
	    SleepMs(100);
	  }

		if(webJsons.size()>0){
			serial.Push(StringParser::Append(webJsons.back(),"\n"));
			webJsons.pop_back();
			SleepMs(2500);
		}
		SleepMs(1);
//		serial.Push("{\"action\":2,\"target\":1,\"column\":4,\"row\":1,\"text\":\"INTERAY   \"}\n");
//		SleepMs(2500);
//		serial.Push("{\"action\":2,\"target\":1,\"column\":4,\"row\":1,\"text\":\"HELLOWORLD\"}\n");
//		SleepMs(2500);

	}
	return 0;
}
