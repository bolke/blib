#include "FileIO.h"

using namespace blib;

EnumResult_t blib::GetFiles(std::string path,std::vector<std::string>& files,size_t depth){
	EnumResult_t result=FAIL;
	std::wstring filename;
	std::string dir;

	do{
    WIN32_FIND_DATA ffd;

		if(path.size()>(MAX_PATH-4))
			break;
        
		if(!StringParser::EndsWith(path,"\\"))
			path=StringParser::Append(path,"\\");
		dir=path;
		path=StringParser::Append(path,"*.*");    

		filename=std::wstring(path.begin(),path.end());

		HANDLE hFind = FindFirstFile(filename.c_str(), &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
      break;   
    
    while(FindNextFile(hFind, &ffd)){
			filename=std::wstring(ffd.cFileName);
			std::string strFilename=std::string(filename.begin(),filename.end());
			if(StringParser::Compare(strFilename,"..")||(StringParser::Compare(strFilename,".")))
				continue;			
			strFilename=StringParser::Append(dir,strFilename);
			if(!IsDirectory(strFilename))
				files.push_back(strFilename);
			else if(depth>0)
				GetFiles(strFilename,files,depth-1);			
		}

		FindClose(hFind);

		result=SUCCESS;
	}while(0);

	return result;
}

EnumResult_t blib::GetDirectories(std::string path,std::vector<std::string>& paths,size_t depth){
  EnumResult_t result=FAIL;
	std::wstring filename;
	std::string dir;

	do{
    WIN32_FIND_DATA ffd;

		if(path.size()>(MAX_PATH-4))
			break;
        
		if(!StringParser::EndsWith(path,"\\"))
			path=StringParser::Append(path,"\\");
		dir=path;
		path=StringParser::Append(path,"*.*");    

		filename=std::wstring(path.begin(),path.end());

		HANDLE hFind = FindFirstFile(filename.c_str(), &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
      break;   
    
    while(FindNextFile(hFind, &ffd)){
			filename=std::wstring(ffd.cFileName);
			std::string strFilename=std::string(filename.begin(),filename.end());
			if(StringParser::Compare(strFilename,"..")||(StringParser::Compare(strFilename,".")))
				continue;			
			strFilename=StringParser::Append(dir,strFilename);
			if(IsDirectory(strFilename)){
				paths.push_back(strFilename);
				if(depth>0)
					GetDirectories(paths.back(),paths,depth-1);
			}
		}

		FindClose(hFind);

		result=SUCCESS;
	}while(0);

	return result;
}

bool blib::IsDirectory(std::string path){
  bool result=false;
#ifdef WINDOWS	
  if(!StringParser::EndsWith(path,"\\"))
	  path=StringParser::Append(path,"\\");
  path=StringParser::Append(path,"*.*");
	std::wstring wPath=std::wstring(path.begin(),path.end());
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(wPath.c_str(), &ffd);
	if(hFind != INVALID_HANDLE_VALUE){
		FindClose(hFind);
	  result=true;
	}
#endif
  return result;	
}
	
bool blib::IsFile(std::string path){
  bool result=false;
#ifdef WINDOWS	
  FileInterface f;
	f.SetFilename(path);
	if(f.Open()==SUCCESS){
		result=true;
		f.Close();
	}
#endif
  return result;	
}

bool blib::DoesItExists(std::string path){
  return IsDirectory(path)||IsFile(path);
}
