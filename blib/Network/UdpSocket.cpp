#include "UdpSocket.h"

using namespace blib;

UdpSocket::UdpSocket(std::string ip,uint16_t port){
  sendSocket=INVALID_SOCKET;
  if((ip.size()>0)&&(port>0))
    Bind(ip,port);  
}

UdpSocket::~UdpSocket(){
  if(lock->Lock()){
    if(sendSocket!=INVALID_SOCKET)
#ifdef LINUX
    close(sendSocket);
#else
    closesocket(sendSocket);
#endif
    lock->Unlock();
  }
}

EnumResult_t UdpSocket::CreateSocket(int32_t af, int32_t type, int32_t protocol){
  return Socket::CreateSocket(af,type,protocol);
}

size_t UdpSocket::Pop(char_t& c,size_t size){
  size_t result=0;
  if(lock->Lock()){
    if(!HasSocket())
      Bind();
    if(HasSocket()){       
#ifdef LINUX
      socklen_t addrSize=sizeof(recvAddress);
#else
      int32_t addrSize=sizeof(recvAddress);
#endif
      result=recvfrom(socketHandle,&c,size,0,(struct sockaddr*) &recvAddress,&addrSize);
      if(result>size)
        result=0;
    }
    lock->Unlock();
  }
  return result;
}

size_t UdpSocket::Pop(std::string& data){
  return Socket::Pop(data);
}

size_t UdpSocket::Push(const char_t &c,size_t size){
  size_t result=0;
  if(lock->Lock()){
    if(HasTarget()){
      if(sendSocket==INVALID_SOCKET){
        uint32_t tempSocket=socketHandle;
        socketHandle=INVALID_SOCKET;                                //!todo
        CreateSocket();                                              //!todo
        sendSocket=socketHandle;                                    //!todo 
        socketHandle=tempSocket;                                    //!todo
      }
      if(sendSocket!=INVALID_SOCKET){
        result=sendto(sendSocket,&c,size,0,(struct sockaddr*)&targetAddress,sizeof(targetAddress));
      }
    }
    lock->Unlock();
  }
  return result;
}

size_t UdpSocket::Push(const std::string& data){
  return Socket::Push(data);
}

EnumResult_t UdpSocket::SetBlocking(bool blocking,uint32_t socketHandle){
  EnumResult_t result=FAIL;  
  if(socketHandle!=INVALID_SOCKET)
    result=Socket::SetBlocking(blocking,socketHandle);
  else{
    if(lock->Lock()){    
      if(this->socketHandle!=INVALID_SOCKET)
        result=Socket::SetBlocking(blocking,this->socketHandle);
      else if(sendSocket!=INVALID_SOCKET)
        result=Socket::SetBlocking(blocking,sendSocket);
      lock->Unlock();
    }
  }
  return result;
}

uint32_t UdpSocket::GetSendSocketHandle(){
  uint32_t result=0;
	if(lock->Lock()){
	  result=sendSocket;
		lock->Unlock();
  }
	return result;
}

EnumResult_t UdpSocket::SetSendSocketHandle(uint32_t socketHandle){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
	  sendSocket=socketHandle;
		result=SUCCESS;
    lock->Unlock();
  }
	return result;
}

