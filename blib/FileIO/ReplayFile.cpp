#include "ReplayFile.h"

using namespace blib;

ReplayFile::ReplayFile(std::string filename):DeviceOpener(*(new FileInterface(filename))){
  file=(FileInterface*)device;
  file->SetFilename(filename);
  file->SetFilemode(std::fstream::in|std::fstream::binary);
}

std::string ReplayFile::GetFilename(){
  return file->GetFilename();
}

EnumResult_t ReplayFile::SetFilename(std::string filename){
  return file->SetFilename(filename);
}

int32_t ReplayFile::GetFilemode(){
  return file->GetFilemode();
}

size_t ReplayFile::Pop(char_t& c,size_t size){
  if(lock->Lock()){
    if(Size()==0){
      Close();
    }
    lock->Unlock();
  }
  size_t result=DeviceOpener::Pop(c,size);
  if((result==0)&&(size>0))
    Close();
  return result;
}

size_t ReplayFile::Pop(std::string& data){
  return Device::Pop(data);
}

size_t ReplayFile::Push(const char_t &c,size_t size){
  return 0;
}

size_t ReplayFile::Push(const std::string& data){
  return DeviceOpener::Push(data);
}

bool ReplayFile::IsBinairy(){
  bool result=false;
  if(lock->Lock()){
    result=file->GetFilemode()&std::fstream::binary;
    lock->Unlock();
  }
  return result;
}

EnumResult_t ReplayFile::SetBinairy(bool value){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    Close();
    if(!IsOpen()){
      if(value)
        file->SetFilemode(file->GetFilemode()|std::fstream::binary);
      else if(IsBinairy())
        file->SetFilemode(file->GetFilemode()&(~(std::fstream::binary)));
      result=SUCCESS;
    }
    lock->Unlock();
  }
  return result;
}
