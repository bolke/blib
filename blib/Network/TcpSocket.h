#ifndef BLIB_TCPSOCKET_H
#define BLIB_TCPSOCKET_H

#include "Socket.h"

namespace blib{

class TcpSocket:public Socket,public Base{
protected:
  virtual EnumResult_t CreateSocket(int32_t af=AF_INET,int32_t type=SOCK_STREAM,int32_t protocol=IPPROTO_TCP); //socket creation settings
public:  
  TcpSocket(uint16_t port=0);																												//if created with a port>0 opens a socket ready to accept connection
  TcpSocket(std::string ip,uint16_t port);																					//if created with an address and port>0 a socket tries to connect to that address

  virtual EnumResult_t Open();																														//calls Connect

  virtual size_t Pop(char_t& c,size_t size=1);																			//get data from the socket, if blocking, blocks
  virtual size_t Pop(std::string& data);																						//same

  virtual size_t Push(const char_t &c,size_t size=1);																//push data onto the socket
  virtual size_t Push(const std::string& data);																			//same

  virtual bool IsConnected();																												//are we connected?

  virtual EnumResult_t Connect(std::string targetIp="",uint16_t targetPort=0);				  	//connect to the given address and port
  virtual EnumResult_t Listen(uint16_t targetPort=0);																		//listen on the given port for connection
  virtual EnumResult_t Accept(TcpSocket& client);																				//multi server mode, accept a connection and put the accepted connection in the socket given
	virtual EnumResult_t Accept();																													//single server mode, accept a single connection and put the accepted connection into this socket
};

};

#endif
