#include "Serial.h" 

using namespace blib;

AutoSerialPort::AutoSerialPort(){
  identifyCallback=NULL;
};

EnumResult_t AutoSerialPort::Open(void){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(IsOpen())
      Close();
    if(port.size()>0)
      SerialPort::Open();
    if(!IsOpen()){
      std::vector<std::string> ports=GetAvailableSerialPorts();
      for(size_t i=0;i<ports.size();i++){
        SetPort(ports[i]);
        SerialPort::Open();
        if(identifyCallback!=NULL){
          if(identifyCallback->Callback()==SUCCESS){
            if(*((bool*)identifyCallback->GetReturnRef()))
              result=SUCCESS;
          }
        }else
          result=SUCCESS;
        if(result==SUCCESS)
          break;
      }
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t AutoSerialPort::SetIdentifyCallback(CallbackTemp* value){
  EnumResult_t result=FAIL;
  if(value!=NULL){
    if(lock->Lock()){
      if(value->GetReturnTypeInfo()==&typeid(bool)){
        if(identifyCallback!=NULL)
          delete identifyCallback;
        identifyCallback=value;
        result=SUCCESS;
      }
      lock->Unlock();
    }
  }
  return result;
}
