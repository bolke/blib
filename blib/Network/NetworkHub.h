#ifndef BLIB_NETWORKHUB_H
#define BLIB_NETWORKHUB_H

#include "Network.h"
#include "Core.h"

namespace blib{

class NetworkHub:public Device{
protected:  
  uint16_t port;
  Thread broadcastThread;
  Thread serverThread;    
  TcpSocket* clientSocket;
  MultiSocket* broadcastSocket;
  TcpSocket* serverSocket;
  std::vector<TcpSocket*> clients;
  std::string broadcastMessage;
  bool killClientsOnClose;
  void BroadcastSetup();
  void BroadcastRun();
  void BroadcastCleanup();
  void ServerSetup();
  void ServerRun();
  void ServerCleanup();
public:
  NetworkHub();
  uint16_t GetPort();
  EnumResult_t SetPort(const uint16_t port);  
  virtual EnumResult_t Open();
  virtual EnumResult_t Close();
  virtual size_t Size();
  virtual size_t Pop(std::string& data);
  virtual size_t Pop(char_t& c,size_t size=1);
  virtual size_t Push(const std::string& data);
  virtual size_t Push(const char_t &c,size_t size=1);
  bool GetKillClientsOnClose();
  EnumResult_t SetKillClientsOnClose(const bool value);
  std::vector<TcpSocket*>& GetClients();
  std::string GetBroadcastMessage();
  EnumResult_t SetBroadcastMessage(const std::string value);
};

};

#endif
