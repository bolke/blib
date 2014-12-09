#include <stdio.h>

#include "blib.h"
#include "json.h"
#include "JsonServer.h"
#include "JsonClient.h"

using namespace blib;


void JsonStartClient(){
	
	TcpSocket client;	
	
	while(client.Connect("127.0.0.1",1200)==FAIL){
		SleepMs(10);
	}

	while(client.IsOpen()){		
		std::string input;	
	  std::string line;

		while(client.Pop(line)>0){
			input=StringParser::Append(input,line);
			SleepMs(10);
		}

		if(input.size()>0){
			json::Object object;
			json::Value value;
			value=json::Deserialize(input);
			DeserializeJson(input.c_str(),input.length());
			object=value.ToObject();
			json::Object::ValueMap::iterator jIt=object.begin();
			while(jIt!=object.end()){
				std::cout<<jIt->first;
				if(jIt->second.GetType()==json::StringVal)
					std::cout<<" "<<jIt->second.ToString();
				std::cout<<"\r\n";
				jIt++;
			}		
		}

	  SleepMs(10);
	}

	client.Close();

};

int32_t main(int32_t argc, char_t* argv[]){
	InitNetwork();
  JsonStartServer();
	JsonStartClient();
	return 0;
}
