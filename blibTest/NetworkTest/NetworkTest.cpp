#include <stdio.h>

#include "blib.h"
#include "NetworkHub.h"

using namespace blib;

int32_t main(int32_t argc, char_t* argv[]){  
	InitNetwork();
	NetworkHub hub;
	hub.SetPort(1234);
	hub.Open();

	while(1){
	  SleepMs(1000);
	}

	return 0;
}
