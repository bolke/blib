#include <stdio.h>

#include "Core.h"

using namespace blib;

int32_t main(int32_t argc, char_t* argv[]){
	StringParser sp;
	std::string line;
	line=sp.Append(line,"hello");
	line=sp.Append(line," ");
	line=sp.Append(line,"world");
	line=sp.Append(line,"\r\n");
	while(1){	  
		std::cout<<line;
		SleepMs(1000);
	}
	return 0;
}
