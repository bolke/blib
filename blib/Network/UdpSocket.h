#ifndef BLIB_UDPSOCKET_H
#define BLIB_UDPSOCKET_H

#include "Socket.h"

namespace blib{

class UdpSocket:public Socket,public Base{
protected:
	uint32_t sendSocket;
	struct sockaddr_in recvAddress;
	virtual EnumResult_t CreateSocket(int32_t af=AF_INET,int32_t type=SOCK_DGRAM,int32_t protocol=IPPROTO_UDP); 
public:
	UdpSocket(std::string ip="",uint16_t port=0);	
	~UdpSocket();

  virtual size_t Pop(char_t& c,size_t size=1);
  virtual size_t Pop(std::string& data);
  
  virtual size_t Push(const char_t &c,size_t size=1);  
  virtual size_t Push(const std::string& data);

	virtual EnumResult_t SetBlocking(bool blocking,uint32_t socketHandle);
	
  virtual uint32_t GetSendSocketHandle();
  virtual EnumResult_t SetSendSocketHandle(uint32_t socketHandle);  
};

};

#endif
