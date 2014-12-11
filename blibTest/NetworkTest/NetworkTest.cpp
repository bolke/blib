#include <stdio.h>

#include "blib.h"

using namespace blib;

int32_t main(int32_t argc, char_t* argv[]){  
	InitNetwork();
	TcpSocket s;
  s.SetTarget("192.168.178.24",1234);
	while(1){		
    s.Connect();
	  SleepMs(1000);
    std::cout<<s;
    s.Close();
    SleepMs(1000);
	}

	return 0;
}
