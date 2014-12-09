#include "SerialPort.h" 
#include <cstring>

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

size_t SerialPort::Pop(std::string& data){
  return Device::Pop(data);
}

size_t SerialPort::Push(const std::string& data){
  return Device::Push(data);
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

#ifdef WINDOWS

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

size_t SerialPort::Push(const char_t& c,size_t size){
  DWORD bytesWritten=0;
  size_t result=FAIL;
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
#elif defined(LINUX)

EnumResult_t SerialPort::Open(){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){
    if(IsOpen())
      Close();
    if(!IsOpen()){

      hComm=open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
      
      if(hComm!=-1){        
        if(tcgetattr(hComm,&oldSettings)!=-1){        
          std::memset(&newSettings,0,sizeof(newSettings));
          newSettings.c_cflag=baud|CS8|CLOCAL|CREAD;
          newSettings.c_iflag=IGNPAR;
          newSettings.c_oflag=0;
          newSettings.c_lflag=0;
          newSettings.c_cc[VMIN]=0;  
          newSettings.c_cc[VTIME]=0;
          if(tcsetattr(hComm,TCSANOW,&newSettings)!=-1){          
            int32_t status;
            if(ioctl(hComm,TIOCMGET,&status)!=-1){
              status|=TIOCM_DTR;
              status|=TIOCM_RTS;
              if(ioctl(hComm,TIOCMSET,&status)!=-1){
                result=SUCCESS;  
              }              
            }
          }
        }
      }
    }

    if(result==FAIL){
      if(hComm!=0){
        close(hComm);
        hComm=0;
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
      int32_t status;
      if(ioctl(hComm,TIOCMGET,&status)!=-1){
        status&=~TIOCM_DTR;
        status&=~TIOCM_RTS;
        if(ioctl(hComm,TIOCMSET,&status)!=0){
          close(hComm);
          tcsetattr(hComm,TCSANOW,&oldSettings);
          hComm=0;
        }else
          result=SUCCESS;
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
      this->port.assign("/dev/"+port);
      result=SUCCESS;
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t SerialPort::SetBaud(int32_t baud){
  EnumResult_t result=SUCCESS;
  if(lock->Lock()){
    switch(baud){
      case 50: this->baud = B50;
               break;
      case 75: this->baud = B75;
               break;
      case 110: this->baud = B110;
                break;
      case 134: this->baud = B134;
                break;
      case 150: this->baud = B150;
                break;
      case 200: this->baud = B200;
                break;
      case 300: this->baud = B300;
                break;
      case 600: this->baud = B600;
                break;
      case 1200: this->baud = B1200;
                 break;
      case 1800: this->baud = B1800;
                 break;
      case 2400: this->baud = B2400;
                 break;
      case 4800: this->baud = B4800;
                 break;
      case 9600: this->baud = B9600;
                 break;
      case 19200: this->baud = B19200;
                  break;
      case 38400: this->baud = B38400;
                  break;
      case 57600: this->baud = B57600;
                  break;
      case 115200: this->baud = B115200;
                   break;
      case 230400: this->baud = B230400;
                   break;
      case 460800: this->baud = B460800;
                   break;
      case 500000: this->baud = B500000;
                   break;
      case 576000: this->baud = B576000;
                   break;
      case 921600: this->baud = B921600;
                   break;
      case 1000000: this->baud = B1000000;
                    break;
      default : result=FAIL;
                     break;
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t SerialPort::SetStop(int32_t stop){
  EnumResult_t result=FAIL;
  if(lock->Lock()){    
    lock->Unlock();
  }
  return result;
}

EnumResult_t SerialPort::SetParity(int32_t parity){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){    
    lock->Unlock();
  }
  return result;
}

EnumResult_t SerialPort::SetByteSize(int32_t byteSize){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){    
    lock->Unlock();
  }
  return result;
}

size_t SerialPort::Push(const char_t& c,size_t size){  
  size_t result=0;
  if(lock->Lock()){
    if(IsOpen()){               
      result=write(hComm,(void*)&c,size);
    }
    lock->Unlock();
  }
  return result;
}

size_t SerialPort::Pop(char_t& c, size_t size){
  size_t result=0;
  if(lock->Lock()){
    if(IsOpen()){
      std::memset(&c,0,size);
      uint32_t bytesRead=0;
      uint32_t bufSize=size;
      result=read(hComm,&c,bufSize);        
    }
    lock->Unlock();
  }
  return result;
}
#else
#error undefined operating system
#endif
