#include <stdio.h>

#include "blib.h"
#include "BrewProgram.h"

void Loop();
void Setup();

void ReadSimEeprom();
void WriteSimEeprom();

using namespace blib;

int32_t main(int32_t argc, char_t* argv[]){	
	ReadSimEeprom();
	Setup();
	while(1){
		Loop();
		SleepMs(1000);
	}
  return 0;
};