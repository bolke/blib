#include "SaveFile.h"

using namespace blib;

SaveFile::SaveFile(std::string filename,size_t maxFileSize){
	fileCnt=0;
	SetMaxFileSize(maxFileSize);
	SetHardSizes(true);
	SetFilename(filename);
	SetFilemode(std::ios::out);
  fileSize=0;
}

EnumResult_t SaveFile::SetFilename(std::string filename){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(!IsOpen()){
			realFilename=filename;
  	  StringParser sp;
	  	std::string ext=sp.AfterLast(filename,".");
		  filename=sp.BeforeLast(filename,".");
		  ext=sp.Append(sp.ToString("%i.",fileCnt),ext);
		  this->filename=sp.Append(filename,ext);			
		  result=SUCCESS;		  
		}
		lock->Unlock();
	}
	return result;
}

EnumResult_t SaveFile::SetFilemode(int32_t filemode){
  EnumResult_t result=FAIL;
	if((filemode&std::ios::out)==std::ios::out)
		result=FileInterface::SetFilemode(filemode);
	return result;
}

bool SaveFile::GetHardSizes(){
  return hardSizes;
}

EnumResult_t SaveFile::SetHardSizes(bool hardSizes){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->hardSizes=hardSizes;
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
}

size_t SaveFile::GetMaxFileSize(){
	return maxFileSize;
}

EnumResult_t SaveFile::SetMaxFileSize(size_t maxFileSize){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->maxFileSize=maxFileSize;
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
}

size_t SaveFile::Push(const std::string& data){
	return Push(*data.c_str(),data.size());
}

size_t SaveFile::Push(const char_t &c,size_t size){
	size_t result=0;
	if(lock->Lock()){
		if(IsOpen()){
			if(maxFileSize==0){
				result=FileInterface::Push(c,size);
				fileSize+=result;
			}else{
				fileSize=fileSize+Size();				
				size_t writeSize=0;
				if(fileSize<maxFileSize)
					writeSize=maxFileSize-fileSize;
				if(size>writeSize){
					if(hardSizes)
						result=FileInterface::Push(c,writeSize);						
					else
				    result=FileInterface::Push(c,size);
					Close();
					fileCnt++;										
					SetFilename(realFilename);
					Open();
					fileSize=0;					
					if(hardSizes)
					  fileSize=Push((&c)[writeSize],size-writeSize);
					result+=fileSize;
				}else{
					result=FileInterface::Push(c,size);
					fileSize+=result;
				}
			}
		}
		lock->Unlock();
	};
	return result;
}
