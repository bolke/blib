#include "BaseProject.h"

using namespace blib;

BaseProject::~BaseProject(){
  Cleanup();
}

BaseProject::BaseProject(size_t argc,char_t** argv){
	reopenInput=true;
	reopenOutput=true;

	inputThread=NULL;
	outputThread=NULL;

	outBuf=NULL;
	inBuf=NULL;
	tempOutStream=NULL;
	tempInStream=NULL;

	outputDevice=NULL;
	inputDevice=NULL;

	name="Default";
	version="0.1";

  outputFlag=false;
  outputFileFlag=false;
  outputEthFlag=false;
  outputSerialFlag=false;
  inputFlag=false;
  inputFileFlag=false;
  inputEthFlag=false;
  inputSerialFlag=false;

	if(argc>1)   
    Init(argc,argv);
}

void BaseProject::PrintHelp(){
	std::cout<<BLIB_HELP_TEXT;
  if(inputFlag){
  	std::cout<<"    -i: cin(default) \n";
    if(inputFileFlag)
      std::cout<<"    file \"filename\"\n";
    if(inputEthFlag)
	    std::cout<<"    ethernet <tcp/udp/multi> <server/client> [address] port\n\    address is optional if tcp server.\n";
    if(inputSerialFlag)
	    std::cout<<"    serial \"port\" [baud=9600]\n";
	  std::cout<<"    Select input source.\n";
  }

  if(outputFlag){
  	std::cout<<"\    -o: cout(default) \n";
    if(outputFileFlag)
      std::cout<<"    file \"filename\"\n";
    if(outputEthFlag)
      std::cout<<"    ethernet <tcp/udp/multi> <server/client> [address] port \n    address is optional if tcp server.\n";
    if(outputSerialFlag)
	    std::cout<<"    serial \"port\" [baud=9600]\n";
	  std::cout<<"    Select output source.\n";
  }
	
  std::cout<<"\n";
}

void BaseProject::PrintVersion(){	
	std::cout<<"Project:"<<name<<" Version:"<<version<<"\n";
	std::cout<<"Library Version:"<<BLIB_VERSION<<" Core:"<<BLIB_CORE<<" OS:"<<BLIB_OS<<" License:"<<BLIB_LICENSE_TYPE<<"\n\n";
}

void BaseProject::PrintLicense(){
	std::cout<<BLIB_LICENSE<<"\n\n";
}

void BaseProject::InputThreadSetup(){
	if(inputDevice!=NULL)
		inputDevice->Open();
}

void BaseProject::OutputThreadSetup(){
	if(outputDevice!=NULL)
		outputDevice->Open();
}

void BaseProject::InputThreadRun(){
	if(inputDevice!=NULL){
		if(inputDevice->IsOpen()){		
			if(inputDevice->Size()==0){
				if(inputThread->GetRunDelay()<1000)
				  inputThread->SetRunDelay(inputThread->GetRunDelay()+1);
				else if(inputThread->GetRunDelay()>1)
					inputThread->SetRunDelay(inputThread->GetRunDelay()-1);
			}else if(tempInStream!=NULL)
				*tempInStream<<*inputDevice;
		}else{			
			inputDevice->Close();
			if(reopenInput)
			  inputDevice->Open();
		}
	}
}

void BaseProject::OutputThreadRun(){
	if(outputDevice!=NULL){
		if(outputDevice->IsOpen()){
			if(outBuf!=NULL){
				if(outBuf->Size()==0){
					if(outputThread->GetRunDelay()<1000)
						outputThread->SetRunDelay(outputThread->GetRunDelay()+1);
					else if(outputThread->GetRunDelay()>1)
						outputThread->SetRunDelay(outputThread->GetRunDelay()-1);
				}else
					*outBuf>>*outputDevice;
			}else if(tempOutStream!=NULL){
				*tempOutStream>>*outputDevice;
			}
		}else{
			outputDevice->Close();
			if(reopenOutput)
			  outputDevice->Open();
		}
	}
}

EnumResult_t BaseProject::StartInputThread(){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(inputDevice!=NULL){
			inputThread=new Thread();
			inputThread->SetSetupCallback(new Callback0<void,BaseProject>(this,&BaseProject::InputThreadSetup));
			inputThread->SetRunCallback(new Callback0<void,BaseProject>(this,&BaseProject::InputThreadRun));
			result=inputThread->Start();
		}
		lock->Unlock();
	}
	return result;
}

EnumResult_t BaseProject::StartOutputThread(){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(outputDevice!=NULL){
			outputThread=new Thread();
			outputThread->SetSetupCallback(new Callback0<void,BaseProject>(this,&BaseProject::OutputThreadSetup));
			outputThread->SetRunCallback(new Callback0<void,BaseProject>(this,&BaseProject::OutputThreadRun));
			result=outputThread->Start();
		}
		lock->Unlock();
	}
	return result;
}

FileInterface* BaseProject::GetFileFromArguments(std::vector<std::string>& args){
	FileInterface* result=NULL;
	if(lock->Lock()){
		if(args.size()==3){
			if(StringParser::Compare(args[0],"file")){			
				result=new FileInterface(args[1],std::fstream::binary|std::fstream::in);				
				if(StringParser::Compare(args[2],"out")){
					result->SetFilemode(std::fstream::binary|std::fstream::out|std::fstream::trunc);
					if(result->Open()==SUCCESS){
					  result->Close();
						result->SetFilemode(std::fstream::binary|std::fstream::out|std::fstream::app);
					}else{
						delete result;
						result=NULL;
					}
				}
			}
		}
		lock->Unlock();
	}
	return result;
}

Socket* BaseProject::GetSocketFromArguments(std::vector<std::string>& args){
	Socket* result=NULL;
	if(lock->Lock()){
		if(args.size()>=4){
			InitNetwork();																					//!todo remove and integrate into lib or network open functions
			if(StringParser::Compare(args[0],"ethernet")){
				std::string address=args[3];		
				uint16_t port=StringParser::ToUInt16_t(args[3]);
				if(args.size()==5)
					port=StringParser::ToUInt16_t(args[4]);
				if(StringParser::Compare(args[1],"tcp")){
					if(StringParser::Compare(args[2],"server"))
						address="";
					result=new TcpSocket();					
				}else if(StringParser::Compare(args[1],"udp"))
					result=new UdpSocket();
				else if(StringParser::Compare(args[1],"multi"))
					result=new MultiSocket(address,port);			
				if(result!=NULL){
					result->SetBlocking(false);
					result->SetTarget(address,port);
				}
			}
		}
		lock->Unlock();
	}
	return result;
}

SerialPort* BaseProject::GetSerialFromArguments(std::vector<std::string>& args){
	SerialPort* result=NULL;
	return result;
}

void BaseProject::OutputToFile(std::vector<std::string>& args){
	outputDevice=GetFileFromArguments(args);
}

void BaseProject::OutputToEthernet(std::vector<std::string>& args){
	outputDevice=GetSocketFromArguments(args);
}

void BaseProject::OutputToSerial(std::vector<std::string>& args){
	outputDevice=GetSerialFromArguments(args);
}

void BaseProject::OutputFromArgument(std::string arguments){
	std::vector<std::string> args=StringParser::SplitIntoArguments(arguments);
	if(args.size()>0){
    if(outputFlag){
      if(outputFileFlag){
	    	if(StringParser::Compare(args[0],"file")){
			    args.push_back("out");
		      OutputToFile(args);
		    }
      }
      if(outputEthFlag){
    		if(StringParser::Compare(args[0],"ethernet"))
		      OutputToEthernet(args);
      }
      if(outputSerialFlag){
		    if(StringParser::Compare(args[0],"serial"))
		      OutputToSerial(args);
      }
		  if(outputDevice!=NULL){
			  outBuf=new ThreadStringBuf();
			  tempOutStream=new std::iostream(outBuf);
			  std::cout.rdbuf(tempOutStream->rdbuf());
			  if(StartOutputThread()!=SUCCESS){
				  delete outputDevice;
				  outputDevice=NULL;
				  //!todo set error code and message
			  }
		  }
    }
	}
}

void BaseProject::InputFromFile(std::vector<std::string>& args){
	inputDevice=GetFileFromArguments(args);
}

void BaseProject::InputFromEthernet(std::vector<std::string>& args){
	inputDevice=GetSocketFromArguments(args);
}

void BaseProject::InputFromSerial(std::vector<std::string>& args){
	inputDevice=GetSerialFromArguments(args);
}

void BaseProject::InputFromArgument(std::string arguments){
	std::vector<std::string> args=StringParser::SplitIntoArguments(arguments);
	if(args.size()>0){
    if(inputFlag){
      if(inputFileFlag){
	    	if(StringParser::Compare(args[0],"file")){
			    args.push_back("in");
		      InputFromFile(args);
		    }
      }
      if(inputEthFlag){
        if(StringParser::Compare(args[0],"ethernet"))
		      InputFromEthernet(args);
      }
      if(inputSerialFlag){
    		if(StringParser::Compare(args[0],"serial"))
  		    InputFromSerial(args);
      }
		  if(inputDevice!=NULL){
			  inBuf=new ThreadStringBuf();
			  tempInStream=new std::iostream(inBuf);
			  std::cin.rdbuf(tempInStream->rdbuf());
			  if(StartInputThread()!=SUCCESS){
				  delete inputDevice;
				  inputDevice=NULL;
				  //!todo set error code and message
			  }
		  }
    }
	}
}

void BaseProject::InitArguments(){
	argumentFunctions["h"]=new Callback0<void,BaseProject>(this,&BaseProject::PrintHelp);
	argumentFunctions["l"]=new Callback0<void,BaseProject>(this,&BaseProject::PrintLicense);
#ifdef BLIB_INPUT_ENABLED
	argumentFunctions["i"]=new Callback1<void,BaseProject,std::string>(this,&BaseProject::InputFromArgument,"");
#endif
#ifdef BLIB_OUTPUT_ENABLED
	argumentFunctions["o"]=new Callback1<void,BaseProject,std::string>(this,&BaseProject::OutputFromArgument,"");	
#endif
	argumentFunctions["v"]=new Callback0<void,BaseProject>(this,&BaseProject::PrintVersion);	
}

EnumResult_t BaseProject::ParseArguments(size_t length,char_t* arg[]){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		result=SUCCESS;	
		std::vector<std::string> arguments;
		size_t i=0;

		for(i=1;i<length;i++){		
			if(StringParser::StartsWith(arg[i],"-"))
				arguments.push_back(StringParser::AfterLast(arg[i],"-"));					
			else if(arguments.size()>0)
				arguments.back()=StringParser::Append(arguments.back(),StringParser::Append(" ",arg[i]));
			else{			
				std::cout<<StringParser::ToString("Invalid argument. Error in argument %i : %s\n\n",i,arg[i]);
				result=FAIL;			
				break;
			}			
		}		
		
		if(result==SUCCESS){
			result=FAIL;
			for(i=0;i<arguments.size();i++){
				CallbackTemp* call=NULL;
				if(StringParser::Contains(arguments[i]," ")){
					if(argumentFunctions.find(StringParser::Before(arguments[i]," "))!=argumentFunctions.end())
						call=argumentFunctions[StringParser::Before(arguments[i]," ")];			
				}else if(argumentFunctions.find(arguments[i])!=argumentFunctions.end())
					call=argumentFunctions[arguments[i]];				
				if(call!=NULL){					
					if(arguments[i].size()>0){
						std::string options=StringParser::After(arguments[i]," ");
            if(options.size()>0){
              call->SetParamsFromString(options);
              result=call->Callback();
              //result=call->Call(StringParser::Append(StringParser::Append("\"",options),"\""));
            }else if(call->GetNrOfParameters()==0)
              result=call->Callback();
					}else if(call->GetNrOfParameters()==0)
            result=call->Callback();
				}
				if(result==FAIL){
					if(call==NULL)
						std::cout<<StringParser::ToString("Invalid argument. Command %s not found.\n\n",arguments[i].c_str());
					else
						std::cout<<StringParser::ToString("Error executing argument. Command: %s Parameters: %s\n\n",StringParser::Before(arguments[i]," ").c_str(),StringParser::After(arguments[i]," ").c_str());
					break;
				}
			}
		}else
			i=i-1;

		if(result==FAIL)
			PrintHelp();
		lock->Unlock();
  }

	return result;
}

EnumResult_t BaseProject::CleanupArgumentFunctions(){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		std::map<std::string,CallbackTemp*>::iterator aIt=argumentFunctions.begin();
		while(aIt!=argumentFunctions.end()){
			delete aIt->second;
			aIt++;
		}
		argumentFunctions.clear();
		result=SUCCESS;
		lock->Unlock();
  }
	return result;
}


EnumResult_t BaseProject::Init(size_t argc, char_t* argv[]){
	EnumResult_t result=FAIL;
	if(argc<=1)
		result=SUCCESS;
	else{
		if(lock->Lock()){		
			InitArguments();
			result=ParseArguments(argc,argv);
			if(CleanupArgumentFunctions()!=SUCCESS)
				result=FAIL;
			lock->Unlock();
		}
	}
	return result;
}

EnumResult_t BaseProject::Cleanup(){
	EnumResult_t result=FAIL;
	if(lock->Lock()){		
		if(outputThread!=NULL)
			delete outputThread;
		if(inputThread!=NULL)
			delete inputThread;
		if(inputDevice!=NULL)
			delete inputDevice;
		if(outputDevice!=NULL)
			delete outputDevice;
		if(tempOutStream!=NULL)
			delete tempOutStream;
		if(tempInStream!=NULL)
			delete tempInStream;
		if(coutBuf!=NULL)
			std::cout.rdbuf(coutBuf);
		if(cinBuf!=NULL)
			std::cin.rdbuf(cinBuf);
		if(outBuf!=NULL)
			delete outBuf;
		if(inBuf!=NULL)
			delete inBuf;
		result=SUCCESS;
	  lock->Unlock();
	}
	return result;
}

size_t BaseProject::Size(){
	size_t result=0;
	if(lock->Lock()){		
		if(std::cin.get()!=EOF)
			result=1;		
	  lock->Unlock();
	}
	return result;
}

size_t BaseProject::Pop(char_t& c,size_t size){
  size_t result=0;
	if(size>0){
		if(lock->Lock()){
			std::cin.read(&c,size);
			result=std::cin.gcount();
			lock->Unlock();
		}
	}
	return result;
}

size_t BaseProject::Pop(std::string &data){
  size_t result=0;
	if(lock->Lock()){
		result=Data::Pop(data);
		lock->Unlock();
	}
	return result;
}

size_t BaseProject::Push(const char_t& c,size_t size){
  size_t result=0;
	if(size>0){
		if(lock->Lock()){						           
			std::cout.write(&c,size);
			result=size;
			lock->Unlock();
		}
	}
	return result;
}

size_t BaseProject::Push(const std::string& data){
  size_t result=0;
	if(lock->Lock()){
		result=Data::Push(data);
		lock->Unlock();
	}
	return result;
}

EnumResult_t BaseProject::Run(){	
	std::string line;
	while(!StringParser::Compare(line,"exit")){
		if(lock->Lock()){
			if(std::cin.get()==EOF)
				std::cin.clear();
			else{
 				std::cin>>line;			
				if(line.size()>0)
					std::cout<<line<<"\n\r";
			}
			lock->Unlock();
		}
		Sleep(1);
	}
	return SUCCESS;
}
