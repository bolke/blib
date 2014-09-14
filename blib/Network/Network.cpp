#include "Network.h"

#include <Iphlpapi.h>

using namespace blib;

EnumResult_t blib::GetIpAddress(char* ip,size_t charLen){
  EnumResult_t result=FAIL;  
  
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
 
  return result;
};

EnumResult_t blib::GetIpAddress(std::string* ip){
  EnumResult_t result=FAIL;
  char buf[]="255.255.255.255";

  result=GetIpAddress(buf,sizeof(buf)-1);
  if(result==SUCCESS && ip)
    ip->assign(buf);
  return result;
};

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