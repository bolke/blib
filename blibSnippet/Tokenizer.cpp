#include "Tokenizer.h"
#include <regex>

using namespace blib;

CppToken::CppToken(const EnumToken_t id,const std::string content,const size_t position){
  this->id=id;
	this->content=content;
	this->position=position;
}

Tokenizer::Tokenizer(){
	regex="";
	InitRegex();
	InitKeywords();
}

Tokenizer::~Tokenizer(){
	while(tokens.size()>0){
	  delete tokens.back();
		tokens.pop_back();
	}
	while(tokenDefs.size()>0){
	  delete tokenDefs.back()
		tokenDefs.pop_back();
  }
}

EnumResult_t Tokenizer::InitRegex(){
	EnumResult_t result=SUCCESS;

  tokenDefs.push_back("(#[a-zA-Z_][a-zA-Z0-9_]*)");										//01 TOK_PREPROCESSOR
	tokenDefs.push_back("([\r\n]+)");																		//02 TOK_NEWLINE
	tokenDefs.push_back("(\"[^\"]*\")");																//03 TOK_STRING
	tokenDefs.push_back("([a-zA-Z_][a-zA-Z0-9_]*)");										//04 TOK_NAME
	tokenDefs.push_back("([0-9]*\\.?[0-9]+)");													//05 TOK_NUMBER
	tokenDefs.push_back("([ \t]+)");																		//06 TOK_SPACE

	tokenDefs.push_back("(/\\*)"); 																			//07 TOK_COMMENTSTART
	tokenDefs.push_back("(\\*/)");	  																	//08 TOK_COMMENTEND
	tokenDefs.push_back("(//.*)");																			//09 TOK_COMMENT

	tokenDefs.push_back("(->)");																				//10 TOK_REFARROW
	tokenDefs.push_back("(\\:\\:)");																		//11 TOK_DOUBLECOLON
	tokenDefs.push_back("(\\;)");																				//12 TOK_SEMICOLON
	
	tokenDefs.push_back("(\\+\\+|\\-\\-)");															//13 TOK_CREMENT
	tokenDefs.push_back("([\\*\\/\\%\\+\\-\\&\\^\\|\\~]=|<<=|>>=|=)");	//14 TOK_ASSIGN
	tokenDefs.push_back("([\\*\\+\\-\\/\\%])"); 												//15 TOK_OPERATOR
  tokenDefs.push_back("(\\!\\||\\&\\&|==|\\!=)");											//16 TOK_COMPARE
	
	tokenDefs.push_back("(,)");																					//17 TOK_KOMMA
	tokenDefs.push_back("([\\:])");																			//18 TOK_COLON
	tokenDefs.push_back("([{])");																				//19 TOK_OPENBRACE
	tokenDefs.push_back("([}])");																				//20 TOK_CLOSEBRACE
	tokenDefs.push_back("([(])");																				//21 TOK_OPENPARENTHESE
	tokenDefs.push_back("([)])");																				//22 TOK_CLOSEPARENTHESE
	tokenDefs.push_back("([\\&\\|\\^\\~]|\\<\\<|\\>\\>)");							//23 TOK_BINAIRY
	
	tokenDefs.push_back("([\\<])");																			//24 TOK_OPENCHEVRON
	tokenDefs.push_back("([\\>])");																			//25 TOK_CLOSECHEVRON
	tokenDefs.push_back("([\\[])");																			//26 TOK_OPENBRACKET
	tokenDefs.push_back("([\\]])");																			//27 TOK_CLOSEBRACKET
	tokenDefs.push_back("([\\.])");																			//28 TOK_DOT
	tokenDefs.push_back("(.+)");																				//29 TOK_CATCHALL

	return result;
}

size_t Tokenizer::Size(){
	return tokens.size();
}

size_t Tokenizer::Pop(char_t& c,size_t size){
	return 0;
}

size_t Tokenizer::Pop(std::string& data){
	return Device::Pop(data);
}

size_t Tokenizer::Push(const char_t &c,size_t size){
	return Parse(std::string(&c,size));
}

size_t Tokenizer::Push(const std::string& data){
	return Device::Push(data);
}

size_t Tokenizer::Parse(std::string data){
  size_t result=0;
	size_t position=0;

	std::vector<std::string*>::iterator it=tokenDefs.begin();
  std::string regStr=GetRegex();

  std::tr1::regex reg(regStr.c_str());    
  std::tr1::sregex_token_iterator rend;
        
  std::tr1::sregex_token_iterator rit(data.begin(),data.end(),reg);          
  while(rit!=rend){
    std::tr1::smatch match;
    std::string token=rit->str();            
    if(std::tr1::regex_match(token,match,reg)){
      EnumToken_t tokenId=TOK_UNKNOWN;              
      for(size_t f=1;f<match.size();f++){
        if(match[f].length()>0){
          tokenId=static_cast<EnumToken_t>(f);
          break;
        }
      }          
      tokens.push_back(new CppToken(tokenId,match[0]));

			tokens.back()->position =position;
			if(tokens.back()->id==TOK_NAME){
				if(std::find(keywords.begin(),keywords.end(),tokens.back()->content)!=keywords.end())
					tokens.back()->id=TOK_KEYWORD;
			}
			position=position+match[0].length();
    }
    rit++;
	}	

  return result;
}

size_t Tokenizer::InitKeywords(){  
	keywords.push_back("if");	
  keywords.push_back("while");	
	keywords.push_back("for");
	keywords.push_back("switch");
  keywords.push_back("catch");	

  keywords.push_back("try");															
	keywords.push_back("else");
	keywords.push_back("do");	

	keywords.push_back("enum");
	keywords.push_back("struct");	
	keywords.push_back("union");	
	keywords.push_back("class");
	keywords.push_back("typedef");	

	keywords.push_back("case");	
	keywords.push_back("default");

	keywords.push_back("private");
	keywords.push_back("public");
	keywords.push_back("protected");	

	keywords.push_back("register");
	keywords.push_back("virtual");
	keywords.push_back("extern");
	keywords.push_back("static");
	keywords.push_back("auto");
	keywords.push_back("char");
	keywords.push_back("const");
	keywords.push_back("double");
	keywords.push_back("float");
	keywords.push_back("int");
	keywords.push_back("long");
	keywords.push_back("wchar_t");
  keywords.push_back("short");
	keywords.push_back("signed");
	keywords.push_back("unsigned");
	keywords.push_back("void");
	keywords.push_back("volatile");
  keywords.push_back("bool");

	keywords.push_back("and");		      														
	keywords.push_back("and_eq");														
	keywords.push_back("bitand");														
	keywords.push_back("bitor");														
	keywords.push_back("compl");														
	keywords.push_back("not");																	
	keywords.push_back("not_eq");															
	keywords.push_back("or");																	
	keywords.push_back("or_eq");															
	keywords.push_back("xor");																
	keywords.push_back("xor_eq");															

	keywords.push_back("continue");
	keywords.push_back("break");

	keywords.push_back("throw");
	keywords.push_back("return");
	keywords.push_back("goto");

	keywords.push_back("const_cast");
	keywords.push_back("dynamic_cast");
	keywords.push_back("reinterpret_cast");
	keywords.push_back("static_cast");

	keywords.push_back("sizeof");
	keywords.push_back("asm");	
	keywords.push_back("delete");
	keywords.push_back("explicit");

	keywords.push_back("friend");
	keywords.push_back("inline");
	keywords.push_back("mutable");
	keywords.push_back("namespace");
	keywords.push_back("new");
	keywords.push_back("operator");	
	keywords.push_back("template");
	keywords.push_back("this");
	keywords.push_back("typeid");
	keywords.push_back("typename");
	keywords.push_back("using");	

	return keywords.size();
}

std::vector<CppToken*>& Tokenizer::GetTokens(){
	return tokens;
}

std::string Tokenizer::GetRegex(){
  std::string result="";  
  if(tokenDefs.size()>0){
	  std::vector<std::string>::iterator it=tokenDefs.begin();  
	  result=**it;
    it++;
    while(it!=tokenDefs.end()){    
		  result=sp.Append(result,sp.Append("|",*it));
      it++;
	  }
  }
  return result;
}

std::string Tokenizer::TokenIdToString(const EnumToken_t tokenId){
	std::string result="TOK_UNKNOWN";
	switch(tokenId){		
		case TOK_PREPROCESSOR:
			result="TOK_PREPROCESSOR";
			break;
		case TOK_NEWLINE:
			result="TOK_NEWLINE";
			break;
		case TOK_STRING:
			result="TOK_STRING";
			break;
		case TOK_NAME:
			result="TOK_NAME";
			break;
		case TOK_NUMBER:
			result="TOK_NUMBER";
			break;
		case TOK_SPACE:
			result="TOK_SPACE";
			break;
		case TOK_COMMENTSTART:
			result="TOK_COMMENTSTART";
			break;
		case TOK_COMMENTEND:
			result="TOK_COMMENTEND";
			break;
		case TOK_COMMENT:
			result="TOK_COMMENT";
			break;
		case TOK_REFARROW:
			result="TOK_REFARROW";
			break;
		case TOK_DOUBLECOLON:
			result="TOK_DOUBLECOLON";
			break;
		case TOK_SEMICOLON:
			result="TOK_SEMICOLON";
			break;
		case TOK_CREMENT:
			result="TOK_CREMENT";
			break;
		case TOK_ASSIGN:
			result="TOK_ASSIGN";
			break;
		case TOK_OPERATOR:
			result="TOK_OPERATOR";
			break;
		case TOK_COMPARE:
			result="TOK_COMPARE";
			break;
		case TOK_KOMMA:
			result="TOK_KOMMA";
			break;
		case TOK_COLON:
			result="TOK_COLON";
			break;
		case TOK_OPENBRACE:
			result="TOK_OPENBRACE";
			break;
		case TOK_CLOSEBRACE:
			result="TOK_CLOSEBRACE";
			break;
		case TOK_OPENPARENTHESE:
			result="TOK_OPENPARENTHESE";
			break;
		case TOK_CLOSEPARENTHESE:
			result="TOK_CLOSEPARENTHESE";
			break;
		case TOK_BINARY:
			result="TOK_BINARY";
			break;
		case TOK_OPENCHEVRON:
			result="TOK_OPENCHEVRON";
			break;
		case TOK_CLOSECHEVRON:
			result="TOK_CLOSECHEVRON";
			break;
		case TOK_OPENBRACKET:
			result="TOK_OPENBRACKET";
			break;
		case TOK_CLOSEBRACKET:
			result="TOK_CLOSEBRACKET";
			break;
		case TOK_DOT:
			result="TOK_DOT";
			break;		
		case TOK_CATCHALL:
			result="TOK_CATCHALL";
			break;
		case TOK_KEYWORD:
			result="TOK_KEYWORD";
			break;
	}
	return result;
}
