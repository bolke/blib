#include "Network.h"

using namespace blib;

NetworkClient::NetworkClient(uint16_t port){
	broadcastSocket=NULL;
	clientSocket=NULL;
	this->port=port;
};

uint16_t NetworkClient::GetPort(){
  uint16_t result=0;
  if(lock->Lock()){
    result=port;
    lock->Unlock();
  }
  return result;
};

EnumResult_t NetworkClient::SetPort(const uint16_t port){
  EnumResult_t result=FAIL;
  if(port>0){
    if(lock->Lock()){
      if(!IsOpen()){
        this->port=port;
        result=SUCCESS;
      }
      lock->Unlock();
    }
  }
  return result;
};

EnumResult_t NetworkClient::Open(){
	EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(IsOpen())
      Close();
		result=StartBroadcastThread();    
    isOpen=(result==SUCCESS);     
    lock->Unlock();
  }  
	return result;
};

EnumResult_t NetworkClient::Close(){
	EnumResult_t result=FAIL;
  if(lock->Lock()){
    StopBroadcastThread();
    isOpen=false;
		if(clientSocket!=NULL)
		  delete clientSocket;
		clientSocket=NULL;
    lock->Unlock();
  }
  return result;
};

size_t NetworkClient::Size(){
	size_t result=0;
	if(lock->Lock()){
	  if(clientSocket!=NULL)
		  result=clientSocket->Size();
		lock->Unlock();
	}
	return result;
};

size_t NetworkClient::Pop(std::string& data){
	return Device::Pop(data);
};

size_t NetworkClient::Pop(char_t& c,size_t size){
  size_t result=0;
	if(lock->Lock()){
		if(clientSocket!=NULL)
		  result=clientSocket->Pop(c,size);
		lock->Unlock();
	}
	return result;
};

size_t NetworkClient::Push(const std::string& data){
	return Device::Push(data);
};

size_t NetworkClient::Push(const char_t &c,size_t size){
	size_t result=0;
	if(lock->Lock()){
	  if(clientSocket!=NULL)
		  result=clientSocket->Push(c,size);		
	  lock->Unlock();
	}
	return result;
};

bool NetworkClient::IsOpen(){
	bool result=false;
  if(lock->Lock()){
    result=((broadcastThread.IsAlive())||(clientSocket!=NULL&&clientSocket->IsOpen()));
    lock->Unlock();
  }
  return result;
};

void NetworkClient::BroadcastSetup(){  
  std::string address;
  InitNetwork();
  GetIpAddress(address);
  broadcastAddress=StringParser::BeforeLast(address,".");
  broadcastAddress=StringParser::Append(broadcastAddress,".255");

  broadcastSocket=new MultiSocket(broadcastAddress,port);
  broadcastSocket->SetSendSocketHandle(broadcastSocket->GetSocketHandle());
}

void NetworkClient::BroadcastRun(){
	std::string msg;
	std::string ip;
	uint16_t port=0;
	if(broadcastSocket->Pop(msg)>0){	
		ip=StringParser::Before(StringParser::After(msg,"#@["),"]");
		port=StringParser::ToUInt16_t(StringParser::Before(StringParser::After(msg,"]["),"]"));		
		if(clientSocket==NULL){
		  clientSocket=new TcpSocket();
			if(clientSocket->Connect(ip,port)==FAIL){
			  delete clientSocket;
				clientSocket=NULL;
			}	  			 
		}
	}
	if(clientSocket!=NULL){
	}
}

void NetworkClient::BroadcastCleanup(){
  delete broadcastSocket;
  broadcastSocket=NULL;
}

EnumResult_t NetworkClient::StartBroadcastThread(){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(!broadcastThread.IsAlive()){
			broadcastThread.ClearCallbacks();
			broadcastThread.SetRunDelay(500);		
			broadcastThread.SetSetupCallback(new Callback0<void,NetworkClient>(this,&NetworkClient::BroadcastSetup));
			broadcastThread.SetRunCallback(new Callback0<void,NetworkClient>(this,&NetworkClient::BroadcastRun));
			broadcastThread.SetCleanupCallback(new Callback0<void,NetworkClient>(this,&NetworkClient::BroadcastCleanup));
			result=broadcastThread.Start();
		}
		lock->Unlock();
	}
	return result;
}

EnumResult_t NetworkClient::StopBroadcastThread(){
	return broadcastThread.Stop();
}
