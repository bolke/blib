#ifndef BLIB_CPPTOKEN_H
#define BLIB_CPPTOKEN_H

#include "Blib.h"

namespace blib{

typedef enum{
	TOK_UNKNOWN=0,					//unparsed

	TOK_PREPROCESSOR=1,			//#																				
  TOK_NEWLINE=2,					//\n\r																				
  TOK_STRING=3,						//""			
  TOK_NAME=4,							//anything				
  TOK_NUMBER=5,						//0123456789						
  TOK_SPACE=6,						//\s\t						

  TOK_COMMENTSTART=7,			///*						
  TOK_COMMENTEND=8,				//*/		
  TOK_COMMENT=9,					////		

  TOK_REFARROW=10,				//->					
  TOK_DOUBLECOLON=11,			//::						
  TOK_SEMICOLON=12,				//;				

  TOK_CREMENT=13,					//++ --
  TOK_ASSIGN=14,					//*= /= %= += -= &= ^= |= ~= <<= >>= =
  TOK_OPERATOR=15,				//* + - / % 					
  TOK_COMPARE=16,					//! || && == !=						
  													
  TOK_KOMMA=17,						//,							
  TOK_COLON=18,						//:						
	
	TOK_OPENBRACE=19,				//{	
  TOK_CLOSEBRACE=20,			//}					
  TOK_OPENPARENTHESE=21,	//(				
  TOK_CLOSEPARENTHESE=22,	//)		
  TOK_BINARY=23,					//& | ^ ~ << >>	

	TOK_OPENCHEVRON=24,			//<
	TOK_CLOSECHEVRON=25,		//>
	
	TOK_OPENBRACKET=26,			//[				
  TOK_CLOSEBRACKET=27,		//]				
  TOK_DOT=28,							//.				
  TOK_CATCHALL=29,				//
	TOK_KEYWORD=30,					//predefined name

	TOK_CONDITIONAL=31,			//if while for switch catch
	TOK_RIGHT=32,						//private protected public
	TOK_DEFDATATYPE=33,			//enum struct union class typedef
	TOK_DATATYPE=34,				//char double float int long wchar_t short void bool
	TOK_MODDATATYPE=35,			//register virtual extern static signed unsigned volatile
	
	TOK_BRACES=36,					//{}
	TOK_PARENTHESES=37,			//()
	TOK_CHEVRONS=38,				//<>
	TOK_BRACKETS=39,				//[]

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
