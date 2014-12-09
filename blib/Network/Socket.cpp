#include "Socket.h"

using namespace blib;

EnumResult_t Socket::CreateSocket(int32_t af,int32_t type,int32_t protocol){
  return CreateSocket(socketHandle,af,type,protocol);
}

EnumResult_t Socket::CreateSocket(uint32_t& socketHandle,int32_t af,int32_t type,int32_t protocol){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    socketHandle=(uint32_t)socket(af,type,protocol);
    if(socketHandle!=INVALID_SOCKET){
      SetBlocking(blocking,socketHandle);
      result=SUCCESS;
    }
    lock->Unlock();
  }
  return result;
}

Socket::Socket(){
  blocking=false;
  socketHandle=INVALID_SOCKET;
  std::memset(&targetAddress,0,sizeof(targetAddress));   
  targetPort=0;
  targetIp.s_addr=inet_addr("0.0.0.0");
}

Socket::~Socket(){
  Close();
}

bool Socket::IsOpen(){
  bool result=false;
  if(lock->Lock()){
    result=HasSocket()&&HasTarget();
    isOpen=result;
    lock->Unlock();
  }
  return result;
}

size_t Socket::Size(){
  return DEFAULT_BUFFER_SIZE;
}

EnumResult_t Socket::Open(){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(!HasSocket())
      CreateSocket();
    if(HasSocket()){
      if(HasTarget()){
        result=SUCCESS;
      }
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t Socket::Close(){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(HasSocket()){
#ifdef LINUX
      if(close(socketHandle)==0){
#else
      if(closesocket(socketHandle)==0){
#endif
        socketHandle=INVALID_SOCKET;
        result=SUCCESS;    
      }
    }else
      result=SUCCESS;
    lock->Unlock();
  }
  return result;
}

size_t Socket::Pop(std::string& data){
  return Device::Pop(data);
}

size_t Socket::Push(const std::string &data){
  return Device::Push(data);
}

bool Socket::HasSocket(){
  return socketHandle!=INVALID_SOCKET;
}

bool Socket::HasTarget(){
  bool result=false;
  if(lock->Lock()){
#ifdef LINUX
    result=((targetAddress.sin_port>0)&&(targetAddress.sin_addr.s_addr>0)&&(targetAddress.sin_family!=0));
#else
    result=((targetAddress.sin_port>0)&&(targetAddress.sin_addr.S_un.S_addr>0)&&(targetAddress.sin_family!=0));
#endif
    lock->Unlock();
  }
  return result;
}

bool Socket::IsConnected(){
  return false;
}

bool Socket::IsBlocking(){
  return blocking;
}

EnumResult_t Socket::SetBlocking(bool blocking,uint32_t socketHandle){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){    
    this->blocking=blocking;
    if(socketHandle==INVALID_SOCKET)
      socketHandle=this->socketHandle;
    if(socketHandle!=INVALID_SOCKET){
      ulong_t value=blocking?0:1;
#ifdef LINUX
      if(ioctl(socketHandle,FIONBIO,&value)==0)
#else
      if(ioctlsocket(socketHandle,FIONBIO,&value)==0)
#endif
        result=SUCCESS;
    }
    lock->Unlock();
  }
  return result;
}

uint32_t Socket::GetSocketHandle(){
  return socketHandle;
}

EnumResult_t Socket::SetSocketHandle(uint32_t socketHandle){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    this->socketHandle=socketHandle;
    result=SUCCESS;
    lock->Unlock();
  }
  return result;
}

std::string Socket::GetTargetIp(){
  std::string result="";
  if(lock->Lock()){
    result=inet_ntoa(targetAddress.sin_addr);
    lock->Unlock();
  }
  return result;
}

uint16_t Socket::GetTargetPort(){
  uint16_t result=0;
  if(lock->Lock()){
    result=ntohs(targetAddress.sin_port);
    lock->Unlock();
  }
  return result;
}

EnumResult_t Socket::Bind(std::string targetIp,uint16_t targetPort){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(!HasSocket())
      CreateSocket();
    if(HasSocket()){      
      if(SetTarget(targetIp,targetPort)==SUCCESS){
        if(bind(socketHandle,(struct sockaddr*) &targetAddress,sizeof(targetAddress))==0)
          result=SUCCESS;
      }      
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t Socket::SetTarget(uint16_t targetPort){
  return SetTarget("",targetPort);
}

EnumResult_t Socket::SetTarget(std::string targetIp,uint16_t targetPort){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){
    if(targetIp.length()>0)
      this->targetIp.s_addr=inet_addr(targetIp.c_str());
    if(targetPort>0)
      this->targetPort=htons(targetPort);    

    if((this->targetPort>0)&&(this->targetIp.s_addr>0)){
      std::memset(&targetAddress,0,sizeof(targetAddress));
      targetAddress.sin_family=AF_INET;
#ifdef LINUX
      targetAddress.sin_addr.s_addr=this->targetIp.s_addr;
#else
      targetAddress.sin_addr.S_un.S_addr=this->targetIp.s_addr;
#endif
      targetAddress.sin_port=this->targetPort;
      result=SUCCESS;
    }

    lock->Unlock();
  }
  return result;                    
}

EnumResult_t Socket::SetTargetAddress(const struct sockaddr_in& targetAddress){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    std::memcpy(&this->targetAddress,&targetAddress,sizeof(this->targetAddress));
    result=SUCCESS;
    lock->Unlock();
  }
  return result;
}
