#ifndef BLIB_NETWORK_H
#define BLIB_NETWORK_H

#include "Core.h"

#include "Socket.h"
#include "TcpSocket.h"
#include "UdpSocket.h"
#include "MultiSocket.h"

namespace blib{

EnumResult_t GetIpAddress(char* ip,size_t charLen);
EnumResult_t GetIpAddress(std::string* ip);
EnumResult_t InitNetwork(WORD* version=NULL,WSADATA* data=NULL);
EnumResult_t DeInitNetwork(WORD* version=NULL,WSADATA* data=NULL);

};

#endif
