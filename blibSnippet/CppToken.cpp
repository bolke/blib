#include "CppToken.h"

using namespace blib;

CppToken::CppToken(const EnumToken_t id,const std::string content,const size_t position){
  this->id=id;
	this->content=content;
	this->position=position;
};
