#include <stdio.h>

#include "blib.h"

using namespace blib;

void Test1(){
	std::cout<<"test1\r\n";
}

void Test2(){
	std::cout<<"test2\r\n";
}

void Test3(){
	std::cout<<"test3\r\n";
}

int32_t main(int32_t argc, char_t* argv[]){
	WebServer web;
	CallbackRequestHandler* crh=new CallbackRequestHandler();
	crh->GetCallbacks()["test1"]=new Callback0<void>(&Test1);
	crh->GetCallbacks()["test2"]=new Callback0<void>(&Test2);
	crh->GetCallbacks()["test3"]=new Callback0<void>(&Test3);
	crh->SetTriggerOnUri(true);
	web.SetWebRequestHandler(crh);
	web.Open();
	while(1){
	  SleepMs(100);
	}
	return 0;
}
