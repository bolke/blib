#ifndef BLIB_CPPTOKEN_H
#define BLIB_CPPTOKEN_H

#include "Blib.h"

namespace blib{

typedef enum{
	TOK_UNKNOWN=0,					//unparsed

	TOK_PREPROCESSOR=1,			//#																				
	TOK_IGNORENEWLINE=2,		//\\n \\r
  TOK_NEWLINE=3,					//\n\r																				
  TOK_STRING=4,						//""			
  TOK_NAME=5,							//anything				
  TOK_NUMBER=6,						//0123456789						
  TOK_SPACE=7,						//\s\t						

  TOK_COMMENTSTART=8,			///*						
  TOK_COMMENTEND=9,				//*/		
  TOK_COMMENT=10,					////		

  TOK_REFARROW=11,				//->					
  TOK_DOUBLECOLON=12,			//::						
  TOK_SEMICOLON=13,				//;				

  TOK_CREMENT=14,					//++ --
  TOK_ASSIGN=15,					//*= /= %= += -= &= ^= |= ~= <<= >>= =
  TOK_OPERATOR=16,				//* + - / % 					
  TOK_COMPARE=17,					//! || && == !=						
  													
  TOK_KOMMA=18,						//,							
  TOK_COLON=19,						//:						
	
	TOK_OPENBRACE=20,				//{	
  TOK_CLOSEBRACE=21,			//}					
  TOK_OPENPARENTHESE=22,	//(				
  TOK_CLOSEPARENTHESE=23,	//)		
  TOK_BINARY=24,					//& | ^ ~ << >>	

	TOK_OPENCHEVRON=25,			//<
	TOK_CLOSECHEVRON=26,		//>
	
	TOK_OPENBRACKET=27,			//[				
  TOK_CLOSEBRACKET=28,		//]				
  TOK_DOT=29,							//.				
  TOK_CATCHALL=30,				//
	TOK_KEYWORD=31,					//predefined name

	TOK_UNCONDITIONAL=32,		//try else do
	TOK_CONDITIONAL=33,			//if while for switch catch	
	TOK_RIGHT=34,						//private protected public
	TOK_DEFDATATYPE=35,			//enum struct union class typedef
	TOK_DATATYPE=36,				//char double float int long wchar_t short void bool
	TOK_MODDATATYPE=37,			//register virtual extern static signed unsigned volatile
	
	TOK_BRACES=38,					//{}
	TOK_PARENTHESES=39,			//()
	TOK_CHEVRONS=40,				//<>
	TOK_BRACKETS=41,				//[]

	TOK_OUTBREAK=42,				//continue break throw return goto
	
	TOK_IGNORE=255,					//this token is ignored, as determined by user
}EnumToken_t;

class CppToken{
public:
	EnumToken_t id;
	size_t position;
	std::string content;
	std::vector<CppToken*> tokens;
	CppToken(const EnumToken_t id=TOK_UNKNOWN,const std::string content="",const size_t position=0);
};

};

#endif
