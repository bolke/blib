#include "Network.h"

#ifdef LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <cstring>
#elif defined(WINDOWS)
#include <Iphlpapi.h>
#endif

using namespace blib;

EnumResult_t blib::GetIpAddress(char* ip,size_t charLen){
  EnumResult_t result=FAIL;  
#ifdef LINUX
  if(charLen>=16){
		int fd;
		struct ifreq ifr;
		fd = socket(AF_INET, SOCK_DGRAM, 0);
		/* I want to get an IPv4 IP address */
		ifr.ifr_addr.sa_family = AF_INET;
		/* I want IP address attached to "eth0" */
		strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
		if(ioctl(fd, SIOCGIFADDR, &ifr)==0){
			close(fd);
			/* display result */ 
			std::string ipAddress=inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
			sprintf(ip,"%s",inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
		}
		result=SUCCESS;
	}
#elif defined(WINDOWS)
  // Determine size for IP_ADAPTER_INFO array
  DWORD len=0;
  if(GetAdaptersInfo(NULL,&len)!=ERROR_BUFFER_OVERFLOW)  
    return result;
  
  // Allocate IP_ADAPTER_INFO array
  PIP_ADAPTER_INFO adapterInfo=(PIP_ADAPTER_INFO)(new BYTE[len]);
  PIP_ADAPTER_INFO currentInfo;

  if(GetAdaptersInfo(adapterInfo,&len)==0){
    currentInfo=adapterInfo;
    bool searching=true;

    while((currentInfo)&&(searching)){      
      if(strcmp(currentInfo->IpAddressList.IpAddress.String, "0.0.0.0")){
        strncpy(ip,currentInfo->IpAddressList.IpAddress.String,charLen);
        searching=false;
        result=SUCCESS;
      }else if(currentInfo->Next!=NULL){
        currentInfo=currentInfo->Next;
      }else
        searching=false;
    }
  }          
   
  delete[] adapterInfo;
#endif
 
  return result;
};

EnumResult_t blib::GetIpAddress(std::string& ip){
  EnumResult_t result=FAIL;
  char buf[16]={0};
  result=GetIpAddress(buf,16);
  if(result==SUCCESS)
    ip.assign(buf);
  return result;
};

#ifdef WINDOWS
EnumResult_t blib::InitNetwork(WORD* version,WSADATA* data){
  WORD locVersion=MAKEWORD(2,2);
  WSADATA locData;

  if(version==NULL)
    version=&locVersion;
  
  if(data==NULL)
    data=&locData;

  WSAStartup(*version,data);

  return SUCCESS;
}

EnumResult_t blib::DeInitNetwork(WORD* version,WSADATA* data){
  return FAIL;
}
#elif defined(LINUX)
EnumResult_t blib::InitNetwork(WORD* version,WSADATA* data){
  return SUCCESS;
}

EnumResult_t blib::DeInitNetwork(WORD* version,WSADATA* data){
  return SUCCESS;
}
#endif
