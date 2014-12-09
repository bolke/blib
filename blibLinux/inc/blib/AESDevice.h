#ifndef BLIB_AESDEVICE_H
#define BLIB_AESDEVICE_H

#include "Core.h"

namespace blib{

class AESDevice:public DeviceWrapper{
protected:
	uint8_t in[16], out[16], state[4][4];
	uint8_t roundKey[240];
	size_t restDataSize;
	char_t restData[16];
	void InvCipher();
	void Cipher();
	void KeyExpansion(uint8_t* Key);
	void AddRoundKey(int32_t round);
	void InvSubBytes();
	void InvShiftRows();
	void InvMixColumns();
	void SubBytes();
	void ShiftRows();
	void MixColumns();
public:
  AESDevice(Device& device);
	~AESDevice();
	virtual EnumResult_t SetKey(uint8_t* k);
	virtual EnumResult_t SetKey(const std::string key);
  virtual size_t Pop(char_t& c,size_t size=1);  
  virtual size_t Pop(std::string& data);
  virtual size_t Push(const char_t &c,size_t size=1);  
  virtual size_t Push(const std::string& data); 
  virtual Device& operator>>(Device& d);
  virtual Device& operator<<(Device& d);
};

};


#endif
