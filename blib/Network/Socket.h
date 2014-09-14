#ifndef BLIB_SOCKET_H
#define BLIB_SOCKET_H

#include <winsock.h>
#include "Core.h"

namespace blib{

class Socket:public Device{
protected:
  bool blocking;
  uint32_t socketHandle;
  struct sockaddr_in targetAddress;  
  in_addr targetIp;
  uint16_t targetPort;
  virtual EnumResult_t CreateSocket(uint32_t& socketHandle,int32_t af=AF_INET,int32_t type=SOCK_STREAM,int32_t protocol=IPPROTO_TCP);  
  virtual EnumResult_t CreateSocket(int32_t af=AF_INET,int32_t type=SOCK_STREAM,int32_t protocol=IPPROTO_TCP);  
public:
  Socket();
  ~Socket(); 
 
  virtual bool IsOpen();
  virtual size_t Size(); 
  virtual EnumResult_t Open();
  virtual EnumResult_t Close();

  virtual size_t Pop(char_t& c,size_t size=1)=0;  
  virtual size_t Pop(std::string& data);
  
  virtual size_t Push(const char_t &c,size_t size=1)=0;  
  virtual size_t Push(const std::string& data);

  virtual EnumResult_t Bind(std::string targetIp="",uint16_t targetPort=0);

  virtual bool HasSocket();
  virtual bool HasTarget();
  virtual bool IsConnected();
  virtual bool IsBlocking();  
  virtual EnumResult_t SetBlocking(bool blocking,uint32_t socketHandle=INVALID_SOCKET);	

  virtual uint32_t GetSocketHandle();
  virtual EnumResult_t SetSocketHandle(uint32_t socketHandle);  

  virtual EnumResult_t SetTarget(uint16_t targetPort);
  virtual EnumResult_t SetTarget(std::string targetIp,uint16_t targetPort=0);  

	virtual std::string GetTargetIp();
	virtual uint16_t GetTargetPort();

  virtual EnumResult_t SetTargetAddress(const struct sockaddr_in& targetAddress);
};

};

#endif
