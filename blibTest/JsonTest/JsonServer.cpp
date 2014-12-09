#include "JsonServer.h"
#include "json.h"

using namespace blib;

Thread serverThread;	
WebServer web;

void JsonStartServer(){  
	serverThread.SetRunCallback(new Callback0<void>(&JsonServerSocketRun));
	serverThread.Start();
}

void JsonServerSocketRun(){
	json::Object object;
	object["this is int"]=(uint8_t)12;
	object["this is zloat"]=13.37f;
	object["this is string"]="Hello world";	

	std::string serializedJson=json::Serialize(object);

  TcpSocket server;	
	server.Listen(1200);
	while(server.Accept()==FAIL)
		SleepMs(10);

	while(server.IsOpen()){
		server.Push(serializedJson);
	  SleepMs(100);
	}
	server.Close();
}
