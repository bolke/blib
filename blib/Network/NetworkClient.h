#ifndef BLIB_NETWORKCLIENT_H
#define BLIB_NETWORKCLIENT_H

#include "TcpSocket.h"
#include "MultiSocket.h"
#include "Core.h"

namespace blib{

class NetworkClient:public Device{
protected:
	uint16_t port;
  Thread broadcastThread;  
  TcpSocket* clientSocket;
  MultiSocket* broadcastSocket;
	std::string broadcastAddress;
  std::string broadcastMessage;
  virtual void BroadcastSetup();
  virtual void BroadcastRun();
  virtual void BroadcastCleanup();
public:
	NetworkClient(uint16_t port=0);
	uint16_t GetPort();
  EnumResult_t SetPort(const uint16_t port);
  virtual EnumResult_t Open();
  virtual EnumResult_t Close();
  virtual size_t Size();
  virtual size_t Pop(std::string& data);
  virtual size_t Pop(char_t& c,size_t size=1);
  virtual size_t Push(const std::string& data);
  virtual size_t Push(const char_t &c,size_t size=1);
  virtual bool IsOpen();	
	EnumResult_t StopBroadcastThread();
	EnumResult_t StartBroadcastThread();
};

};

#endif
