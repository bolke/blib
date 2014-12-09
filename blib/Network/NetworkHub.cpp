#include "NetworkHub.h"

using namespace blib;

NetworkHub::NetworkHub(){  
  port=0;
  clientSocket=NULL;
  broadcastSocket=NULL;
  serverSocket=NULL;
  killClientsOnClose=true;
  broadcastMessage="";
  
  broadcastThread.SetRunDelay(1000);
  broadcastThread.SetSetupCallback(new Callback0<void,NetworkHub>(this,&NetworkHub::BroadcastSetup));
  broadcastThread.SetRunCallback(new Callback0<void,NetworkHub>(this,&NetworkHub::BroadcastRun));
  broadcastThread.SetCleanupCallback(new Callback0<void,NetworkHub>(this,&NetworkHub::BroadcastCleanup));

  serverThread.SetRunDelay(50);
  serverThread.SetSetupCallback(new Callback0<void,NetworkHub>(this,&NetworkHub::ServerSetup));
  serverThread.SetRunCallback(new Callback0<void,NetworkHub>(this,&NetworkHub::ServerRun));
  serverThread.SetCleanupCallback(new Callback0<void,NetworkHub>(this,&NetworkHub::ServerCleanup));
}

void NetworkHub::BroadcastSetup(){
  std::string broadcastAddress;
  std::string address;
  InitNetwork();
  GetIpAddress(address);
  broadcastAddress=StringParser::BeforeLast(address,".");
  broadcastAddress=StringParser::Append(broadcastAddress,".255");

  if(broadcastMessage.size()==0)
    broadcastMessage=StringParser::ToString("#@[%s][%u]$#",address.c_str(),port);
  broadcastSocket=new MultiSocket();
  broadcastSocket->SetTarget(broadcastAddress,port);
}

void NetworkHub::BroadcastRun(){
  broadcastSocket->Push(broadcastMessage);
}

void NetworkHub::BroadcastCleanup(){
  delete broadcastSocket;
  broadcastSocket=NULL;
}

void NetworkHub::ServerSetup(){
  InitNetwork();
  serverSocket=new TcpSocket();
  serverSocket->SetTarget(port);  
}

void NetworkHub::ServerRun(){
  if(clientSocket==NULL)
    clientSocket=new TcpSocket();
  if(serverSocket->Accept(*clientSocket)==SUCCESS){
    if(lock->Lock()){
      clients.push_back(clientSocket);
      lock->Unlock();
      clientSocket=NULL;
    }
  }
}

void NetworkHub::ServerCleanup(){
  if(lock->Lock()){
    delete serverSocket;
    serverSocket=NULL;
    if(clientSocket!=NULL)
      delete clientSocket;
    clientSocket=NULL;
    if(killClientsOnClose){
      std::vector<TcpSocket*>::iterator cIt=clients.begin();
      while(cIt!=clients.end()){
        delete *cIt;
        cIt=clients.erase(cIt);
      }
    }
    lock->Unlock();
  }
}

uint16_t NetworkHub::GetPort(){
  uint16_t result=0;
  if(lock->Lock()){
    result=port;
    lock->Unlock();
  }
  return result;
}

EnumResult_t NetworkHub::SetPort(const uint16_t port){
  EnumResult_t result=FAIL;
  if(port>0){
    if(lock->Lock()){
      if(!IsOpen()){
        this->port=port;
        result=SUCCESS;
      }
    }
  }
  return result;
}

EnumResult_t NetworkHub::Open(){
  EnumResult_t result=FAIL;    
  if(lock->Lock()){
    if(IsOpen())
      Close();
    broadcastThread.Start();
    serverThread.Start();
    result=SUCCESS;
    lock->Unlock();
  }
  return result;
}

EnumResult_t NetworkHub::Close(){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    broadcastThread.Stop();
    serverThread.Stop();
    lock->Unlock();
  }
  return result;
}

size_t NetworkHub::Size(){
  size_t result=0;
  return result;
}

size_t NetworkHub::Pop(std::string& data){
  return Device::Pop(data);
}

size_t NetworkHub::Pop(char_t& c,size_t size){
  size_t result=0;
  return result;
}

size_t NetworkHub::Push(const std::string& data){
  return Device::Push(data);
}

size_t NetworkHub::Push(const char_t &c,size_t size){
  size_t result=0;
  if(lock->Lock()){
    std::vector<TcpSocket*>::iterator cIt=clients.begin();
    while(cIt!=clients.end()){
      if((*cIt)->Push(c,size)==size)
        result++;
      cIt++;
    }
    lock->Unlock();
  }
  return result;
}

bool NetworkHub::GetKillClientsOnClose(){
  bool result=false;
  if(lock->Lock()){
    result=killClientsOnClose;
    lock->Unlock();
  }
  return result;
}

EnumResult_t NetworkHub::SetKillClientsOnClose(const bool value){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    killClientsOnClose=value;
    result=SUCCESS;
    lock->Unlock();
  }
  return result;
}

std::vector<TcpSocket*>& NetworkHub::GetClients(){
  return clients;
}

std::string NetworkHub::GetBroadcastMessage(){
  std::string result="";
  if(lock->Lock()){
    result=broadcastMessage;
    lock->Unlock();
  }
  return result;
}

EnumResult_t NetworkHub::SetBroadcastMessage(const std::string value){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    broadcastMessage=value;
    result=SUCCESS;
    lock->Unlock();
  }
  return result;
}
