#include "blib.h"

using namespace blib;

void ReadEepromBytes(uint16_t address,uint8_t* value,uint16_t cnt);
void ReadEepromByte(uint16_t address,uint8_t* value);
void WriteEepromByte(uint16_t address,uint8_t value);
void WriteEepromBytes(uint16_t address,uint8_t* value,uint16_t cnt);

uint8_t GetEepromByte(uint16_t address);

void LcdWriteLine(char_t* c);
void LcdPos(uint8_t x,uint8_t y);
void LcdClear();
