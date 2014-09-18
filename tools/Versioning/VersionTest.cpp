#include <stdio.h>

#include "blib.h"
#include <ctime>

using namespace blib;

void ReplaceVersion(std::string path){
  time_t t=time(0);
	struct tm* now=localtime(&t);
	std::string date=StringParser::ToString("%02i.%02i.%i",(now->tm_mday),(now->tm_mon+1),(now->tm_year+1900));
	
	FileInterface f;		
	f.SetFilename(path);
	f.SetFilemode(std::fstream::in);

	std::vector<std::string> buffer;
	std::string line;

	f.Open();
	while(f.Pop(line)>0)
		buffer.push_back(line);
	f.Close();

	f.SetFilemode(std::fstream::out);
	f.Open();
	while(buffer.size()>0){
		int32_t start=StringParser::Position(buffer.front(),"#define BLIB_VERSION");
		if(start>-1){
			std::string oldLine=StringParser::Sub(buffer.front(),start);
			oldLine=StringParser::Sub(oldLine,0,StringParser::First(oldLine,"\n"));

			std::string oldVersion=StringParser::After(oldLine,"\"");
			oldVersion=StringParser::Before(oldVersion,".");

			std::string newLine=StringParser::ToString("#define BLIB_VERSION \"%s.%s\"",oldVersion.c_str(),date.c_str());
			buffer.front()=StringParser::Replace(buffer.front(),oldLine,newLine);
		}
		f.Push(buffer.front());
		buffer.erase(buffer.begin());
	}
	f.Close();
}

int main(int argc, char* argv[]){
  ReplaceVersion("./inc/Blib.h");
	ReplaceVersion("./../../Blib.h");
	return 0;
}
