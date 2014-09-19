#ifndef BLIB_MultiSOCKET_H
#define BLIB_MultiSOCKET_H

#include "UdpSocket.h"

namespace blib{

class MultiSocket:public UdpSocket{
protected:	
	struct ip_mreq mreq;
	virtual EnumResult_t CreateSocket(int32_t af=AF_INET,int32_t type=SOCK_DGRAM,int32_t protocol=0); 
public:
	MultiSocket(std::string ip="",uint16_t port=0);	
	~MultiSocket();
  virtual EnumResult_t Bind(std::string targetIp="",uint16_t targetPort=0);
	virtual EnumResult_t SetTarget(uint16_t targetPort);
  virtual EnumResult_t SetTarget(std::string targetIp,uint16_t targetPort=0);  
};

};

#endif
