#include "main.h"
#include <stdio.h>

using namespace blib;
int32_t main(int32_t argc, char_t* argv[]){
  std::string address;
  NetworkHub hub;
  char_t c[32]={0};
  GetIpAddress(c,32);
  std::cout<<c<<"\r\n";
  hub.SetPort(1234);
  //hub.Open();
  while(1){
  //if(hub.GetClients().size()>0)
  //  hub.Push("Hello world\r\n");
  //
    SleepMs(500);
  }
  return 0;
}
