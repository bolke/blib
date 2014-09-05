#ifndef BLIB_DEVICE_H
#define BLIB_DEVICE_H

#include "Basis.h"
#include "ThreadSafe.h"               

namespace blib{

class Device:public Data,public ThreadSafe{ 											//a open and closeable data source
protected:
	bool isOpen;																										//if nothing else, this is used to indicate open/closed
public:
  Device(ThreadItem& item,bool destroyLockpad=false);							//get a lock from somewhere, and do we need to destroy it
	Device(ThreadLock& lock=*(new ThreadLock(false)));							//get your own lock, will be destroyed
  virtual ~Device(); 
  virtual size_t Size()=0;																				//return size of data that's poppable
  virtual size_t Pop(char_t& c,size_t size=1)=0;									
  virtual size_t Pop(std::string& data);
  virtual size_t Push(const char_t &c,size_t size=1)=0;  
  virtual size_t Push(const std::string& data); 
	virtual bool IsOpen();																					//returns isOpen variable
  virtual EnumResult_t Open();																		//sets isOpen to TRUE
  virtual EnumResult_t Close();																		//sets isOpen to FALSE
	virtual Device& operator>>(Device& device);											//stream to other device (this->pop other->push)
  virtual Device& operator<<(Device& device);											//stream from other device (other->pop other->push)
	virtual Device& operator>>(std::string& data);									//stream data to string (this->pop(string))
	virtual Device& operator<<(const std::string& data);						//stream data from string (this->push(string))

	friend std::istream& operator>>(std::istream &stream,Device &output){
		char_t* data=NULL;
		size_t pos;
		size_t size;
		if(stream.good()){
			pos=stream.tellg();      
			if(pos==-1){      
				char_t c=stream.get();
				if(c!=EOF)
					output.Push(c,1);				
			}else{              
				stream.seekg(0,stream.end);
				size=stream.tellg();
				if((size>0)&&(size!=-1)){
					stream.seekg(0,pos);                  
					size=size-pos;
					if(size>0){
						data=new char_t[size];
						stream.readsome(data,size);
						size=stream.gcount();
						output.Push(*data,size);
						delete[] data;
					}
				}
			}    
		}
		return stream;
	};

	friend std::ostream& operator<<(std::ostream& stream,Device& input){    
    size_t size=input.Size();
    if(size>0){    
      char_t* data=new char_t[size];
      size_t dataRead=input.Pop(*data,size);
      if(dataRead>0)
        stream.write(data,dataRead);
      delete[] data;
    }
    return stream;
  }; 

};

};

#endif
