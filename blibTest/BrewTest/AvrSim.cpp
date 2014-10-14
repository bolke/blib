#include "AvrSim.h"

static uint8_t eeprom[1024];

uint8_t lcdX=0;
uint8_t lcdY=0;
uint8_t lcdW=20;
uint8_t lcdH=4;
char_t lcdLines[4][20];
FileInterface fEeprom;

void ReadSimEeprom(){
	fEeprom.SetFilename("eeprom");
	fEeprom.SetFilemode(std::ios::in|std::ios::binary);
	fEeprom.Open();
	fEeprom.Pop(*((char_t*)eeprom),1024);
	fEeprom.Close();
}

void WriteSimEeprom(){
	fEeprom.SetFilename("eeprom");
	fEeprom.SetFilemode(std::ios::out|std::ios::binary);
	fEeprom.Open();
	fEeprom.Push(((char_t)eeprom[0]),1024);
	fEeprom.Close();
}

void ReadEepromBytes(uint16_t address,uint8_t* value,uint16_t cnt){	
	if((address<1024)&&(value!=NULL)){
		if(address+cnt>=1024)
			cnt=1023-address;	
		memcpy(value,&(eeprom[address]),cnt);		
	}
}

void ReadEepromByte(uint16_t address,uint8_t* value){
	if((address<1024)&&(value!=NULL))
		*value=eeprom[address];
}

void WriteEepromByte(uint16_t address,uint8_t value){
	if((address<1024)&&(value!=NULL)){
		eeprom[address]=value;
		WriteSimEeprom();
	}
}

void WriteEepromBytes(uint16_t address,uint8_t* value,uint16_t cnt){
  if((address<1024)&&(value!=NULL)){
		if(address+cnt>=1024)
			cnt=1023-address;	
		memcpy(&(eeprom[address]),value,cnt);		
		WriteSimEeprom();
	}
}

uint8_t GetEepromByte(uint16_t address){
  uint8_t result=0;
	ReadEepromByte(address,&result);
	return result;
}

void LcdWriteLine(char_t* c){
//  lcdLines[y][x]
}

void LcdPos(uint8_t x,uint8_t y){
	if(x>=lcdW)
	  x=lcdW-1;
	if(y>=lcdH)
		y=lcdH-1;
  lcdX=x;
	lcdY=y;
}

void LcdClear(){
	LcdPos(0,0);
	LcdWriteLine("                    ");
	LcdWriteLine("                    ");
	LcdWriteLine("                    ");
	LcdWriteLine("                    ");
}