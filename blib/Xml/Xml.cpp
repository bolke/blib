#include "Xml.h"

using namespace blib;

Xml::Xml(std::string filename){
	if(filename.size()>0)
	  Load(filename);
	else{
		isOpen=false;
    doc.reset();
    doc.root().set_name("");
	}
}

Xml::~Xml(){
  Close();
}

EnumResult_t Xml::Load(std::string filename){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    this->filename=filename;
    if(filename.size()>0){
      if (doc.load_file(filename.c_str(),pugi::parse_default)){              
        isOpen=true;
        result=SUCCESS;
      }
    }else{
      isOpen=true;
      result=SUCCESS;
      doc.reset();
      doc.root().set_name("");
    }
    lock->Unlock();
  }
  return result;
}

EnumResult_t Xml::Save(std::string filename){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(filename==""){
      filename=this->filename;
      if(doc.save_file(filename.c_str(),"  ",pugi::format_default)){
        result=SUCCESS;
        this->filename=filename;
      }
    }
    lock->Unlock();
  }
  return result;
}

pugi::xml_node Xml::Root(){
  pugi::xml_node result;
  if(lock->Lock()){
    result=doc.root().first_child();
    lock->Unlock();
  }
  return result;
}

EnumResult_t Xml::Open(){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(IsOpen())
      result=SUCCESS;
    else if(Load(filename)==SUCCESS){
      isOpen=true;
      result=SUCCESS;
    }
  }
  return result;
}

EnumResult_t Xml::Close(){
  if(lock->Lock()){
    if(this->saveOnClose)
      Save();
    doc.reset();
    doc.root().set_name("");
    isOpen=false;
  }
  return SUCCESS;
}

bool Xml::IsOpen(){  
  return isOpen;
}

size_t Xml::Pop(char_t& c,size_t size){
  return 0;
}

size_t Xml::Push(const char_t& c,size_t size){
  return 0;
}

size_t Xml::Pop(std::string& data){
  return Device::Pop(data);
}

size_t Xml::Push(const std::string& data){
  return Device::Push(data);
}

std::string Xml::GetName(){
  return "Xml";
}
