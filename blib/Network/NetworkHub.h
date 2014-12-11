#ifndef BLIB_NETWORKHUB_H
#define BLIB_NETWORKHUB_H

#include "NetworkClient.h"
#include "Core.h"

namespace blib{

class NetworkHub:public NetworkClient{
protected:	
  Thread serverThread;																							
  TcpSocket* serverSocket;																					
  std::vector<TcpSocket*> clients;																	
  std::string broadcastMessage;																				
  bool killClientsOnClose;
  virtual void BroadcastSetup();
  virtual void BroadcastRun();
  virtual void BroadcastCleanup();
  virtual void ServerSetup();
  virtual void ServerRun();
  virtual void ServerCleanup();
public:
  NetworkHub(uint16_t port=0);
  virtual EnumResult_t Open();
  virtual EnumResult_t Close();
  virtual size_t Size();
  virtual size_t Pop(std::string& data);
  virtual size_t Pop(char_t& c,size_t size=1);
  virtual size_t Push(const std::string& data);
  virtual size_t Push(const char_t &c,size_t size=1);
  virtual bool IsOpen();
  bool GetKillClientsOnClose();
  EnumResult_t SetKillClientsOnClose(const bool value);
  TcpSocket* GetClient(const uint32_t id);
  TcpSocket* PopClient(const uint32_t id);
  size_t ClearClosedClients();
  size_t GetNrOfClients();
	virtual EnumResult_t StartBroadcastThread();
};

};

#endif
