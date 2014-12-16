/*
	file: Tokenizer.h
	date: 12-12-14
	author: bolke
	description: 
*/
#ifndef BLIB_TOKENIZER_H
#define BLIB_TOKENIZER_H

#include "CppToken.h"
#include "blib.h"

namespace blib{

class Tokenizer:public Device{
protected:
	StringParser sp;
	std::vector<CppToken*> tokens;
	std::string regex;
	std::vector<std::string> tokenDefs;
	std::vector<std::string> keywords;
	std::vector<std::string> unconditionals;
	std::vector<std::string> conditionals;
	std::vector<std::string> rights;
	std::vector<std::string> dataTypes;
	std::vector<std::string> defDataTypes;
	std::vector<std::string> modDataTypes;
	std::vector<std::string> toIgnore;
	std::vector<std::string> outbreakers;
	virtual EnumResult_t InitRegex();
	virtual size_t InitKeywords();
	virtual std::string GetRegex();
public:
	Tokenizer();
	~Tokenizer();	
	virtual size_t Parse(std::string data);
	virtual size_t Size();
	virtual size_t Pop(char_t& c,size_t size=1);
  virtual size_t Pop(std::string& data);
  virtual size_t Push(const char_t &c,size_t size=1);
  virtual size_t Push(const std::string& data); 
	virtual std::vector<CppToken*>& GetTokens();
	virtual std::vector<std::string>& GetToIgnore();
	static std::string TokenIdToString(const EnumToken_t tokenId);
};

};

#endif
