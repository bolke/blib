#include "MultiSocket.h"

using namespace blib;

MultiSocket::MultiSocket(std::string ip,uint16_t port){			
  if((ip.size()>0)&&(port>0))
    Bind(ip,port);
}

MultiSocket::~MultiSocket(){
	if(lock->Lock()){
		if(sendSocket!=INVALID_SOCKET)
			closesocket(sendSocket);
		lock->Unlock();
	}
}

EnumResult_t MultiSocket::CreateSocket(int32_t af, int32_t type, int32_t protocol){
  return Socket::CreateSocket(af,type,protocol);
}

EnumResult_t MultiSocket::Bind(std::string targetIp,uint16_t targetPort){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
    if(!HasSocket())
      CreateSocket();
    if(HasSocket()){      
      if(SetTarget(targetIp,targetPort)==SUCCESS){
				if(bind(socketHandle,(struct sockaddr*) &recvAddress,sizeof(targetAddress))==0){
					int32_t value=1;
					mreq.imr_multiaddr.s_addr=inet_addr(targetIp.c_str());    
					mreq.imr_interface.s_addr=htonl(INADDR_ANY);    
					if(setsockopt(socketHandle,IPPROTO_IP,IP_ADD_MEMBERSHIP,(const char *) &mreq,sizeof(struct ip_mreq))==SUCCESS)
						if(setsockopt(socketHandle,IPPROTO_IP,SO_REUSEADDR,(const char *)&value,sizeof(value)==SUCCESS))
							result=SUCCESS;
				}
      }  
		}
    lock->Unlock();
  }
  return result;
}

EnumResult_t MultiSocket::SetTarget(uint16_t targetPort){
  return SetTarget("",targetPort);
}

EnumResult_t MultiSocket::SetTarget(std::string targetIp,uint16_t targetPort){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(UdpSocket::SetTarget(targetIp,targetPort)==SUCCESS){ 
			memcpy(&recvAddress,&targetAddress,sizeof(recvAddress));
      mreq.imr_multiaddr.s_addr=recvAddress.sin_addr.S_un.S_addr;
			recvAddress.sin_addr.S_un.S_addr=htonl(INADDR_ANY);      
      mreq.imr_interface.s_addr=htonl(INADDR_ANY);
			result=SUCCESS;
		}
		lock->Unlock();
	}
	return result;
}
