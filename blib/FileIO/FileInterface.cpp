#include "FileInterface.h"

using namespace blib;

#define F_OK 00
#include <io.h>
	
FileInterface::FileInterface(std::string filename,int32_t filemode):Device(*(new ThreadLock(false))){
	if(lock->Lock()){
		SetFilename(filename);
		SetFilemode(filemode);
		lock->Unlock();
	}
}

EnumResult_t FileInterface::Open(void){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(!IsOpen()){
			file.open(filename.c_str(),filemode);
			if(IsOpen())				
			  result=SUCCESS;
		}
	  lock->Unlock();
	}
	return result;
}

EnumResult_t FileInterface::Close(void){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(IsOpen()){
			file.close();
      file.clear();
			if(!IsOpen())
				result=SUCCESS;
		}
		lock->Unlock();
	}
	return result;
}

size_t FileInterface::Size(void){
  size_t result=0;
	if(lock->Lock()){
		if(IsOpen()){
			size_t start=file.tellg();
			file.seekg(0,std::ios::end);
			result=file.tellg();
			if(result>start)
			  result=result-start;
			else
				result=0;
			file.seekg(start);
		}
		lock->Unlock();
	};
	return result;
}

bool FileInterface::IsOpen(void){
  bool result=false;
	if(lock->Lock()){
		isOpen=file.is_open();
		result=isOpen;
		lock->Unlock();
	}
	return result;
}

std::string FileInterface::GetFilename(){
	std::string result;
	if(lock->Lock()){
		result=filename;
		lock->Unlock();
	}
	return result;
}

EnumResult_t FileInterface::SetFilename(std::string filename){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(!IsOpen()){
			this->filename=filename;
			result=SUCCESS;
		}
		lock->Unlock();
	}
	return result;
}

int32_t FileInterface::GetFilemode(){
  int32_t result=0;
	if(lock->Lock()){
		result=filemode;	
		lock->Unlock();
	}
	return result;
}

EnumResult_t FileInterface::SetFilemode(int32_t filemode){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		bool reopen=false;
		if(IsOpen()){
			Close();
			reopen=true;
		}
		if(!IsOpen()){
			this->filemode=filemode;
		  if(reopen)
			  result=this->Open();
		  else
			  result=SUCCESS;
		}
	  lock->Unlock();
	}
	return result;
}

size_t FileInterface::Pop(char_t& c,size_t size){
  size_t result=0;
	if(size>0){
		if(lock->Lock()){
			file.read(&c,size);
			result=file.gcount();      
			lock->Unlock();
		}
	}
	return result;
}

size_t FileInterface::Pop(std::string& data){
	return Device::Pop(data);
}

size_t FileInterface::Push(const char_t &c,size_t size){
  size_t result=FAIL;
	if(size>0){
	  if(lock->Lock()){
			if(IsOpen()){
				size_t before=file.tellp();
				file.write(&c,size);
				file.flush();
				result=file.tellp();
				result=result-before;
			}
	    lock->Unlock();
	  }
	}
	return result;
}

size_t FileInterface::Push(const std::string& data){
	return Device::Push(data);
}

std::fstream& FileInterface::GetFileStream(){
	return file;
}
