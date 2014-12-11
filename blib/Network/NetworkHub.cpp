#include "Network.h"

using namespace blib;

NetworkHub::NetworkHub(uint16_t port){
  this->port=port;
  clientSocket=NULL;
  broadcastSocket=NULL;
  serverSocket=NULL;
  killClientsOnClose=true;
  broadcastMessage="";
  
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
  broadcastSocket=new MultiSocket(broadcastAddress,port);
  broadcastSocket->SetSendSocketHandle(broadcastSocket->GetSocketHandle());
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
}

void NetworkHub::ServerRun(){
  if(clientSocket==NULL)
    clientSocket=new TcpSocket();
  serverSocket->Listen(port);
  if(serverSocket->Accept(*clientSocket)==SUCCESS){
    if(lock->Lock()){
      clients.push_back(clientSocket);
      ClearClosedClients();
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

bool NetworkHub::IsOpen(){
  bool result=false;
  if(lock->Lock()){
    result=((broadcastThread.IsAlive())&&(serverThread.IsAlive()));
    lock->Unlock();
  }
  return result;
}

EnumResult_t NetworkHub::Open(){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(IsOpen())
      Close();
		StartBroadcastThread();    
    serverThread.Start();
    isOpen=true;
    result=SUCCESS;
    lock->Unlock();
  }
  return result;
}

EnumResult_t NetworkHub::Close(){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    StopBroadcastThread();
    isOpen=false;
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

TcpSocket* NetworkHub::GetClient(const uint32_t id){
  TcpSocket* result=NULL;
  if(lock->Lock()){
    if(clients.size()>id)
      result=clients[id];
    lock->Unlock();
  }
  return result;
}

TcpSocket* NetworkHub::PopClient(const uint32_t id){
  TcpSocket* result=NULL;
  if(lock->Lock()){
    if(clients.size()>id){
      result=clients[id];
      clients.erase(clients.begin()+id);
    }
    lock->Unlock();
  }
  return result;
}

size_t NetworkHub::GetNrOfClients(){
  size_t result=0;
  if(lock->Lock()){
    result=clients.size();
    lock->Unlock();
  }
  return result;
}

size_t NetworkHub::ClearClosedClients(){
  size_t result=0;
  if(lock->Lock()){
    std::vector<TcpSocket*>::iterator cIt=clients.begin();
      while(cIt!=clients.end()){
        bool deleteClient=false;
        if((*cIt)->IsOpen()){
          uint32_t clientHandle=(*cIt)->GetSocketHandle();
          char_t c;
#ifdef LINUX
          ssize_t recvResult=recv(clientHandle,&c,1,MSG_DONTWAIT|MSG_PEEK);
          while(recvResult<0){
            if(errno==EINTR)
              recvResult=recv(clientHandle,&c,1,MSG_DONTWAIT|MSG_PEEK);
            else
              break;
          }
#elif defined(WINDOWS)
          int32_t recvResult=recv(clientHandle,&c,1,MSG_PEEK);
          while(recvResult<0){
            //if(errno==EINTR)
            //  recvResult=recv(clientHandle,&c,1,MSG_PEEK);
            //else
              break;
          }
#endif
          deleteClient=recvResult==0;
        }else
          deleteClient=true;
        if(deleteClient){
          delete *cIt;
          cIt=clients.erase(cIt);
          result++;
        }else
          cIt++;
      }
    lock->Unlock();
  }
  return result;
}

EnumResult_t NetworkHub::StartBroadcastThread(){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(!broadcastThread.IsAlive()){
			broadcastThread.ClearCallbacks();
			broadcastThread.SetRunDelay(500);		
			broadcastThread.SetSetupCallback(new Callback0<void,NetworkHub>(this,&NetworkHub::BroadcastSetup));
			broadcastThread.SetRunCallback(new Callback0<void,NetworkHub>(this,&NetworkHub::BroadcastRun));
			broadcastThread.SetCleanupCallback(new Callback0<void,NetworkHub>(this,&NetworkHub::BroadcastCleanup));
			result=broadcastThread.Start();
		}
		lock->Unlock();
	}
	return result;
}
