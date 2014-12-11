#include "TcpSocket.h"

using namespace blib;

TcpSocket::TcpSocket(uint16_t port){
  if(port>0){
    SetBlocking(false);
    if(Listen(port)==SUCCESS)
      Accept(*this);    
  }
}

TcpSocket::TcpSocket(std::string ip,uint16_t port){
  if(ip.size()>0){
    if(port>0){
      Connect(ip,port);
    }
  }
}

EnumResult_t TcpSocket::Open(){  
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(HasTarget())
      result=Connect();
    else{
      Listen();
      result=Accept();
    }
    lock->Unlock();
  }
  return result;
}

bool TcpSocket::IsConnected(){
  return HasSocket();
}

size_t TcpSocket::Pop(char_t& c,size_t size){
  size_t result=0;
  if(lock->Lock()){
    if(HasSocket()){
      result=recv(socketHandle,&c,size,0);      
      if(result>size){        
        result=0;
      }
    }
    lock->Unlock();
  }
  return result;
}

size_t TcpSocket::Pop(std::string& data){
  return Socket::Pop(data);
}

size_t TcpSocket::Push(const char_t &c,size_t size){
  size_t result=0;
  if(lock->Lock()){
    if(HasSocket()){ 
#ifdef WINDOWS    
      result=send(socketHandle,&c,size,0);
#elif defined(LINUX)
      result=send(socketHandle,&c,size,MSG_NOSIGNAL);
#endif
      if(result>size){
        Close();
        result=0;
      }
    }
    lock->Unlock();
  }
  return result;
}

size_t TcpSocket::Push(const std::string& data){
  return Socket::Push(data);
}

EnumResult_t TcpSocket::CreateSocket(int32_t af,int32_t type,int32_t protocol){
  return Socket::CreateSocket(af,type,protocol);
}

EnumResult_t TcpSocket::Connect(std::string targetIp,uint16_t port){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(!HasSocket())
      CreateSocket();
    if(HasSocket()){
      SetTarget(targetIp,port);
    } 
    
    if(!blocking){
      if(connect(socketHandle,(struct sockaddr *) &targetAddress,sizeof(targetAddress))>=0)
        result=SUCCESS;
      else{
        SetBlocking(true);
        fd_set fd;
        timeval tv;
        tv.tv_sec=1;
        tv.tv_usec=0;
        FD_ZERO(&fd);
        FD_SET(socketHandle,&fd);
        select(socketHandle+1,NULL,&fd,NULL,&tv);
        SetBlocking(false);
        if(FD_ISSET(socketHandle,&fd))
          result=SUCCESS;
      }
    }else if(connect(socketHandle,(struct sockaddr *) &targetAddress,sizeof(targetAddress))>=0)
      result=SUCCESS;
    else{            
      Close();
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t TcpSocket::Listen(uint16_t targetPort){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(!HasSocket())
      CreateSocket();
    if(HasSocket()){
      targetAddress.sin_family=AF_INET;
#ifdef LINUX
      targetAddress.sin_addr.s_addr=htonl(INADDR_ANY);
#else
      targetAddress.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
#endif
      if(targetPort>0)
        targetAddress.sin_port=htons(targetPort);
      else
        targetAddress.sin_port=this->targetPort;

      if(bind(socketHandle,(struct sockaddr *) &targetAddress,sizeof(targetAddress))==0){      
        if(listen(socketHandle,SOMAXCONN)==0){         
          result=SUCCESS;
        }
      }
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t TcpSocket::Accept(TcpSocket& client){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(!HasSocket())
      CreateSocket();
    if(HasSocket()){
      bool oldBlocking=blocking;      
      this->SetBlocking(true);
      struct sockaddr_in clientAddress;
#ifdef LINUX
      socklen_t addrSize=sizeof(clientAddress);
#else
      int32_t addrSize=sizeof(clientAddress);
#endif
      uint32_t clientSocket=accept(socketHandle,(struct sockaddr*) &clientAddress,&addrSize);
      if(clientSocket!=INVALID_SOCKET){
        if(clientSocket>=0){        
          if(client.HasSocket())
            client.Close();
          client.SetSocketHandle(clientSocket);
          client.SetTargetAddress(clientAddress);
          client.SetBlocking(oldBlocking);
          result=SUCCESS;
        }
        std::cout<<"arse\r\n";
      }else{
        std::cout<<strerror(errno)<<"\r\n";
        std::cout<<"socket handle:"<<socketHandle<<"\r\n";
        std::cout<<"client handle:"<<clientSocket<<"\r\n";
      }
      if(!oldBlocking)
        this->SetBlocking(false);
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t TcpSocket::Accept(){  
  return Accept(*this);
}
