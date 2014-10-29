#ifndef BLIB_PROJECT_H
#define BLIB_PROJECT_H

#include "blib.h"
#include "ThreadStringBuf.h"

#define BLIB_HELP_TEXT "\
Program help.\n\
  -h: Shows this page.\n\
  -l: Shows license.\n\
  -v: Shows version device type and OS.\n"	

namespace blib{

static std::streambuf* cinBuf=std::cin.rdbuf();
static std::streambuf* coutBuf=std::cout.rdbuf();

class BaseProject:public Data,public ThreadSafe,public Base{
protected:
  bool outputFlag;                //enable output options, any of them
  bool outputFileFlag;            //enable file output options
  bool outputEthFlag;             //enable eth output options
  bool outputSerialFlag;          //enable serial output options
  bool inputFlag;                 //enable input options, any of them
  bool inputFileFlag;             //enable input file flag
  bool inputEthFlag;              //enable input eth
  bool inputSerialFlag;           //enable input serial

  std::string name;               //application name
	std::string version;            //application version
	
	bool reopenInput;               //if input is closed, retry opening it?
	bool reopenOutput;              //if output is closed, retry opening it?

	Thread* inputThread;            //thread handling the input reading
	Thread* outputThread;           //thread handling the output writing

	ThreadStringBuf* outBuf;        //buffer used as pipe for output
	ThreadStringBuf* inBuf;         //buffer used as pipe for input
	std::iostream* tempOutStream;   //stream for output buffer
	std::iostream* tempInStream;    //stream for input buffer

	Device* outputDevice;           //output device used if enabled
	Device* inputDevice;            //input device used if enabled

	std::map<std::string,CallbackTemp*> argumentFunctions;

  virtual void PrintHelp();																//default -h function, prints help
	virtual void PrintVersion();														//default -v function, prints version
	virtual void PrintLicense();														//default -l function, prints license

	virtual void InputThreadSetup();												//setup callback within thread input
	virtual void OutputThreadSetup();												//setup callback within thread output
	virtual void InputThreadRun();													//run callback for thread input
	virtual void OutputThreadRun();													//run callback for thread output

	virtual EnumResult_t StartInputThread();											//sets callbacks for input thread and starts it
	virtual EnumResult_t StartOutputThread();										//sets callbacks for output thread and starts it

	virtual FileInterface* GetFileFromArguments(std::vector<std::string>& args);	//returns a fileinterface based upon arguments, device is not openend
	virtual Socket* GetSocketFromArguments(std::vector<std::string>& args);				//returns a socketinterface based upon arguments, device is not opened
	virtual SerialPort* GetSerialFromArguments(std::vector<std::string>& args);		//returns a serialports based upon arguments, device is not opened

	virtual void OutputToFile(std::vector<std::string>& args);			//set outputDevice to fileinterface according to arguments
	virtual void OutputToEthernet(std::vector<std::string>& args);	//set outputDevice to socket according to arguments
	virtual void OutputToSerial(std::vector<std::string>& args);		//set outputDevice to serial according to arguments
	virtual void OutputFromArgument(std::string arguments);					//set outputDevice to device according to arguments
  virtual void InputFromFile(std::vector<std::string>& args);			//set inputDevice to fileinterface according to arguments
	virtual void InputFromEthernet(std::vector<std::string>& args);	//set inputDevice to socket according to arguments
	virtual void InputFromSerial(std::vector<std::string>& args);		//set inputDevice to serial according to arguments
	virtual void InputFromArgument(std::string arguments);					//set inputDevice to device according to arguments

	virtual void InitArguments();																		    //initialize arguments handling
	virtual EnumResult_t ParseArguments(std::vector<std::string> lines);	//handle arguments in listed string form
	virtual EnumResult_t ParseArguments(size_t length,char_t* arg[]);		//handle arguments
	virtual EnumResult_t CleanupArgumentFunctions();									  //cleanup function callbacks 
public:		
	BaseProject(size_t argc=0,char_t** argv=NULL);							        //project that also calls init
	~BaseProject();

  virtual EnumResult_t Init(size_t argc, char_t* argv[]);			        //init according to arguments, if any
	virtual EnumResult_t Init(std::string configFile);									//init with settings loaded from given configFile, if any
	virtual EnumResult_t Cleanup();															        //reset cin/cout and stop threads

  virtual size_t Size();																	            //size of cin buffer, if applicable
  virtual size_t Pop(char_t& c,size_t size=1);						            //pop data from cin
  virtual size_t Pop(std::string& data);									
  virtual size_t Push(const char_t &c,size_t size=1);			            //push data into cout
  virtual size_t Push(const std::string& data);                   

	virtual EnumResult_t Run();																	        //main of project	
};

};

#endif
