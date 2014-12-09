#ifndef BLIB_SERIALPORT_H
#define BLIB_SERIALPORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Core.h"

#ifdef WINDOWS
#include <windows.h>
#elif defined(LINUX)
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#else
#error unknown operating system
#endif

namespace blib{

class SerialPort: public Device,public Base{
protected:
#ifdef WINDOWS
  HANDLE hComm;
  DCB dcb;
  _COMMTIMEOUTS timeouts;
#elif defined(LINUX)
  int32_t hComm;
  struct termios oldSettings;
  struct termios newSettings;  
#endif
  std::string port;        
  int32_t baud;
  int32_t stop;
  int32_t parity;
  int32_t byteSize;
public:    
  SerialPort(std::string port="",int32_t baud=9600,int32_t stop=0,int32_t parity=0,int32_t byteSize=8);  
  ~SerialPort(void);  

  virtual EnumResult_t Open(void);
  virtual EnumResult_t Close(void);
  virtual size_t Size(void);
  virtual bool IsOpen(void);
  
  virtual size_t Pop(char_t& c,size_t size=1);  
  virtual size_t Pop(std::string& data);
  
  virtual size_t Push(const char_t &c,size_t size=1);  
  virtual size_t Push(const std::string& data);

  std::string GetPort();
  int32_t GetBaud();
  int32_t GetStop();
  int32_t GetParity();
  int32_t GetByteSize();
  EnumResult_t SetPort(std::string port);
  EnumResult_t SetByteSize(int32_t byteSize);
  EnumResult_t SetBaud(int32_t baud);
  EnumResult_t SetStop(int32_t stop);
  EnumResult_t SetParity(int32_t parity);          
};

};

#endif
