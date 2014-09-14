#include "SerialPort.h" 

using namespace blib;

SerialPort::~SerialPort(){
  Close();
}

SerialPort::SerialPort(std::string port,int32_t baud,int32_t stop,int32_t parity,int32_t byteSize){
  if(lock->Lock()){
    hComm=0;
    SetBaud(baud);
    SetStop(stop);  
    SetParity(parity);
    SetByteSize(byteSize); 
    if(port.size()>0){
      SetPort(port);
      Open();
    }
    lock->Unlock();
  }  
}

bool SerialPort::IsOpen(){
	bool result=false;
	if(lock->Lock()){
    isOpen=hComm!=0;
		result=isOpen;
		lock->Unlock();
	}
	return result;
}

EnumResult_t SerialPort::Open(){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){
    std::wstring wName;
    wName.assign(port.begin(),port.end());    

    if(IsOpen())
      Close();
    if(!IsOpen()){

      hComm = CreateFile(wName.c_str(),  
                          GENERIC_READ | GENERIC_WRITE, 
                          0, 
                          NULL, 
                          OPEN_EXISTING,
                          0,
                          NULL);  

      DWORD error=GetLastError();
      error=error;

      if (hComm != INVALID_HANDLE_VALUE){
        memset(&dcb,0,sizeof(dcb));
        dcb.DCBlength=sizeof(dcb);
        if(!GetCommState(hComm,&dcb)){      
           CloseHandle(hComm); 
        }else if(GetCommTimeouts(hComm,&timeouts)){      
          dcb.BaudRate=baud; 
          dcb.StopBits=stop;
          dcb.Parity=parity;
          dcb.ByteSize=byteSize;           
          if(SetCommState(hComm,&dcb)){                          
            if(GetCommTimeouts(hComm,&timeouts)){
              timeouts.ReadIntervalTimeout=0xffffffff;
              timeouts.ReadTotalTimeoutMultiplier=0;
              timeouts.ReadTotalTimeoutConstant=0;
              timeouts.WriteTotalTimeoutMultiplier=0;
              timeouts.WriteTotalTimeoutConstant=0;        
              if(SetCommTimeouts(hComm,&timeouts))
                result=SUCCESS;
            }                      
          }
        }
      }
    }

    if(result==FAIL){
      if(hComm!=NULL){
        CloseHandle(hComm);
        hComm=NULL;
      }
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t SerialPort::Close(){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(IsOpen()){
      if(CloseHandle(hComm)){
        result=SUCCESS;
        hComm=NULL;
      }
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t SerialPort::SetPort(std::string port){
  EnumResult_t result=FAIL;        
  if(lock->Lock()){
    if(!IsOpen()){      
      this->port.assign("\\\\.\\"+port);
      result=SUCCESS;
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t SerialPort::SetBaud(int32_t baud){
  EnumResult_t result=FAIL;
  if(lock->Lock()){    
    if(IsOpen()){    
      dcb.BaudRate=baud;
      if(SetCommState(hComm,&dcb))
        result=SUCCESS;    
    }else{
      this->baud=baud;
      result=SUCCESS;         
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t SerialPort::SetStop(int32_t stop){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(IsOpen()){
      dcb.StopBits=stop;
      if(SetCommState(hComm,&dcb))
        result=SUCCESS;
    }else{
      this->stop=stop;
      result=SUCCESS;
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t SerialPort::SetParity(int32_t parity){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){
    if(IsOpen()){
      dcb.Parity=parity;
      if(SetCommState(hComm,&dcb))
        result=SUCCESS;    
    }else{
      this->parity=parity;
      result=SUCCESS;
    }      
    lock->Unlock();
  }
  return result;
}

EnumResult_t SerialPort::SetByteSize(int32_t byteSize){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){
    if(IsOpen()){
      dcb.ByteSize=byteSize;
      if(SetCommState(hComm,&dcb))
        result=SUCCESS;
    }else{
      this->byteSize=byteSize;
      result=SUCCESS;
    }
    lock->Unlock();
  }
  return result;
}

size_t SerialPort::Push(const char_t& c,size_t size){
  DWORD bytesWritten=0;
  int32_t result=FAIL;
  if(lock->Lock()){
    if(IsOpen()){         
      DWORD dwordSize=size;
      if(WriteFile(hComm,&c,dwordSize,&bytesWritten,NULL)){
        result=bytesWritten;
      }else{
        if(GetLastError()==ERROR_ACCESS_DENIED){        
          Close();
        }
      }      
    }
    lock->Unlock();
  }
  return result;
}

size_t SerialPort::Pop(std::string& data){
  return Device::Pop(data);
}

size_t SerialPort::Push(const std::string& data){
  return Device::Push(data);
}

size_t SerialPort::Pop(char_t& c, size_t size){
  size_t result=FAIL;
  if(lock->Lock()){
    if(IsOpen()){
      memset(&c,0,size);
      DWORD bytesRead=0;
      DWORD bufSize=size;
      if(ReadFile(hComm,&c,bufSize,&bytesRead,NULL)){
        if((bytesRead>=0)&&(size>=bytesRead))
          result=bytesRead;        
      }else{
        if(GetLastError()==ERROR_ACCESS_DENIED)                
          Close();        
      }
    }
    lock->Unlock();
  }
  return result;
}

size_t SerialPort::Size(){
  return DEFAULT_BUFFER_SIZE;
}

std::string SerialPort::GetPort(){
  std::string result;
  if(lock->Lock()){
		std::string preface="\\\\.\\";
		StringParser sp;
		result=sp.After(port,preface);    
    lock->Unlock();
  }
  return result;
}

int32_t SerialPort::GetBaud(){
  int32_t result=FAIL;
  if(lock->Lock()){
    result=baud;
    lock->Unlock();
  }
  return result;
}

int32_t SerialPort::GetStop(){
  int32_t result=FAIL;
  if(lock->Lock()){		
    result=stop;
    lock->Unlock();
  }
  return result;
}

int32_t SerialPort::GetParity(){
  int32_t result=FAIL;
  if(lock->Lock()){
    result=parity;
    lock->Unlock();
  }
  return result;
}

int32_t SerialPort::GetByteSize(){
  int32_t result=FAIL;
  if(lock->Lock()){
    result=byteSize;
    lock->Unlock();
  }
  return result;
}
