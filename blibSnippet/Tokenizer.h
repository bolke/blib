#ifndef BLIB_TOKENIZER_H
#define BLIB_TOKENIZER_H

#include "blib.h"

namespace blib{

typedef enum{
	TOK_UNKNOWN=0,

	TOK_PREPROCESSOR,			//1		#																				
  TOK_NEWLINE,					//2		\n\r																				
  TOK_STRING,						//3		""			
  TOK_NAME,							//4		anything				
  TOK_NUMBER,						//5		0123456789						
  TOK_SPACE,						//6		\s\t						

  TOK_COMMENTSTART,			//7		/*						
  TOK_COMMENTEND,				//8		*/		
  TOK_COMMENT,					//9		//			

  TOK_REFARROW,					//10	->					
  TOK_DOUBLECOLON,			//11	::						
  TOK_SEMICOLON,				//12	;				

  TOK_CREMENT,					//13	++ --
  TOK_ASSIGN,						//14  *= /= %= += -= &= ^= |= ~= <<= >>= =
  TOK_OPERATOR,					//15	* + - / % 					
  TOK_COMPARE,					//16	! || && == !=						
  													
  TOK_KOMMA,						//17	,							
  TOK_COLON,						//18	;						

	TOK_OPENBRACE,				//19	{	
  TOK_CLOSEBRACE,				//20	}					
  TOK_OPENPARENTHESE,		//21	(				
  TOK_CLOSEPARENTHESE,	//22	)		
  TOK_BINARY,						//23	& | ^ ~ << >>	

	TOK_OPENCHEVRON,			//24	<
	TOK_CLOSECHEVRON,			//25	>
	
	TOK_OPENBRACKET,			//26	[				
  TOK_CLOSEBRACKET,			//27	]				
  TOK_DOT,							//28	.				
  TOK_CATCHALL,					//29	
	TOK_KEYWORD,					//30	predefined name
}EnumToken_t;

class CppToken{
public:
	EnumToken_t id;
	size_t position;
	std::string content;
	std::vector<CppToken*> tokens;
	CppToken(const EnumToken_t id=TOK_UNKNOWN,const std::string content="",const size_t position=0);
};

class Tokenizer:public Device{
protected:
	StringParser sp;
	std::vector<CppToken*> tokens;
	std::string regex;
	std::vector<std::string> tokenDefs;
	std::vector<std::string> keywords;
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
	static std::string TokenIdToString(const EnumToken_t tokenId);
};

};

#endif
