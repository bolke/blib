#ifndef BLIB_XML_H
#define BLIB_XML_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "pugixml.h"

#include "Core.h"

namespace blib{

class Xml:public Device,public Base{
  protected:
    std::string filename;
    pugi::xml_document doc;
    pugi::xml_node Root(void);    
    bool saveOnClose;
  public:
		Xml(std::string filename="");
	  ~Xml();    
		
		EnumResult_t Load(std::string filename=""); 
    EnumResult_t Save(std::string filename="");

    virtual EnumResult_t Open();
    virtual EnumResult_t Close();

    virtual bool IsOpen();
    
    virtual size_t Pop(char_t& c,size_t size=1);  
    virtual size_t Pop(std::string& data);
  
    virtual size_t Push(const char_t &c,size_t size=1);  
    virtual size_t Push(const std::string& data); 

    virtual size_t Size();

    virtual std::string GetName();
    
    virtual std::string GetFilename();
    virtual std::string SetFilename(std::string filename);

    virtual bool GetSaveOnClose();
    virtual EnumResult_t SetSaveOnClose(bool saveOnClose);
};

}

#endif
