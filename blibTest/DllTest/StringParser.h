#ifndef BLIB_STRINGPARSER_H
#define BLIB_STRINGPARSER_H

#include <string>
#include <vector>
#include "DllTest.h"
#include "Base.h"

namespace blib{

class StringParser:public Base{
public: 
  BLIBDLL_API static int32_t First(const std::string line,const std::string target);																						//return start pos of first instance of target, -1 on fail
  BLIBDLL_API static int32_t Last(const std::string line,const std::string target);																							//return start pos of last instance of target, -1 on fail
	
  BLIBDLL_API static int32_t Position(const std::string line,const std::string target,const size_t nr=1);												//return position of nr instance, -1 on fail
  BLIBDLL_API static size_t Count(const std::string line,const std::string target);																							//return nr of instances of target
  BLIBDLL_API static size_t Count(const std::string line,const char_t target);																									//return nr of instances of target

	BLIBDLL_API static std::string Assign(const std::string line);
	BLIBDLL_API static std::string Assign(const char_t& c,const size_t length=1);

  BLIBDLL_API static std::string Append(const std::string line,const std::string append);																				//returns line with append string added to it

  BLIBDLL_API static int32_t CntParameters(const std::string line);																															//return the number of space seperated string
  BLIBDLL_API static std::string GetParameter(const std::string line,const size_t nr);																					//return the nr string after split with space

  BLIBDLL_API static std::string ToLower(const std::string line);																																//returns line in lowercase
  BLIBDLL_API static std::string ToUpper(const std::string line);																																//returns line in uppercase
  
  BLIBDLL_API static bool Equals(const std::string line,const std::string target);																							//compare between line and target
  BLIBDLL_API static bool Compare(const std::string line,const std::string target);																							//compare between line and target
  BLIBDLL_API static bool CompareBool(const std::string line,const bool value,const bool toLower=false);												//value to string, then string compare
  BLIBDLL_API static bool CompareInt(const std::string line,const int64_t value);																								//value to string, then string compare
  BLIBDLL_API static bool CompareUInt(const std::string line,const uint64_t value);																							//value to string, then string compare
  BLIBDLL_API static bool CompareFloat(const std::string line,const float value);																								//value to string, then string compare

  BLIBDLL_API static bool Contains(const std::string line,const std::string target);																						//does the line contains the target
  BLIBDLL_API static bool Contains(const std::string line,const std::string target,size_t cnt);																	//does the line contains the target cnt nr of times
  BLIBDLL_API static bool ContainsAll(const std::string line,const std::vector<std::string> targets);														//does the line contain all the targets
  BLIBDLL_API static bool ContainsAll(const std::string line,const std::string targets);																				//does the line contain all the targets
  BLIBDLL_API static bool ContainsAny(const std::string line,const std::vector<std::string> targets);														//does the line contain any of the targets
  BLIBDLL_API static bool ContainsAny(const std::string line,const std::string targets);																				//does the line contain any of the targets
  BLIBDLL_API static bool ContainsOnly(const std::string line,const std::vector<std::string> targets);													//does the line only contain the given targets
  BLIBDLL_API static bool ContainsOnly(const std::string line,const std::string targets);																				//does the line only contain the given targets

  BLIBDLL_API static bool Contains(const std::string line,const std::string target,const size_t min,const size_t max);										//does the line contains the min or max of the target
  BLIBDLL_API static bool ContainsAny(const std::string line,const std::vector<std::string> targets,const size_t min,const size_t max);	//does the line contains the min or max of the targets
  BLIBDLL_API static bool ContainsAny(const std::string line,const std::string targets,const size_t min,const size_t max);								//does the line contains any of the targets
  BLIBDLL_API static bool ContainsOnly(const std::string line,const std::vector<std::string> targets,const size_t min,const size_t max); //does the line contain only the targets
  BLIBDLL_API static bool ContainsOnly(const std::string line,const std::string targets,const size_t min,const size_t max);							//does the line contain any of the targets

  BLIBDLL_API static bool StartsWith(const std::string line,const std::string target);																					//does the line start with the target
  BLIBDLL_API static bool EndsWith(const std::string line,const std::string target);																						//does the line end with the target
  
  BLIBDLL_API static bool IsNumeric(const std::string line);																																		//is the string numerical legal?
  BLIBDLL_API static bool IsInteger(const std::string line);																																		//is the string an integer? (no decimals)
  BLIBDLL_API static bool IsFloat(const std::string line);																																			//is the string an integer or floating?
  BLIBDLL_API static bool IsNegative(const std::string line);																																		//is the string a negative numeric?
	BLIBDLL_API static bool IsBool(const std::string line);																																				//is the string a boolean value?
  
  BLIBDLL_API static float ToFloat(const std::string line,const int32_t decimals=-1);																						//returns a floating point with decimals nr of decimals
  BLIBDLL_API static int64_t ToInt(const std::string line);																																			//returns an integer from ToInt64(
  
  BLIBDLL_API static int8_t ToInt8_t(const std::string line);																																		//returns a 8 bit signed integer
	BLIBDLL_API static int16_t ToInt16_t(const std::string line);																																	//returns a 16 bit signed integer
  BLIBDLL_API static int32_t ToInt32_t(const std::string line);																																	//returns a 32 bit signed integer
  BLIBDLL_API static int64_t ToInt64_t(const std::string line);																																	//returns a 64 bit signed integer
  
  BLIBDLL_API static uint8_t ToUInt8_t(const std::string line);																																	//returns a 8 bit unsigned integer
	BLIBDLL_API static uint16_t ToUInt16_t(const std::string line);																																//returns a 16 bit unsigned integer
  BLIBDLL_API static uint32_t ToUInt32_t(const std::string line);																																//returns a 32 bit unsigned integer
  BLIBDLL_API static uint64_t ToUInt64_t(const std::string line);																																//returns a 64 bit unsigned integer
  
	BLIBDLL_API static float32_t ToFloat32_t(const std::string line,const int32_t decimals=-1);                                   //string to normal float
	BLIBDLL_API static float64_t ToFloat64_t(const std::string line,const int32_t decimals=-1);                                   //string to big float

  BLIBDLL_API static bool ToBool(const std::string line);																																				//returns true or false

  BLIBDLL_API static std::vector<std::string> Split(const std::string line,const char delimiter,bool keepDelimiter=false);				 //split the line into segments, snip on the delimiter (which is removed)
  BLIBDLL_API static std::vector<std::string> Split(const std::string line,const std::string delimiter,bool keepDelimiter=false); //split the line into segments, snip on the delimiter (which is removed)

  BLIBDLL_API static std::vector<std::string> SplitIntoArguments(const std::string line);																				//splits data into arguments

  BLIBDLL_API static std::vector<std::string> SplitLines(const std::string line,const bool keepEmpty=false);										//split the line into segments, seperated by \r\n or \r or \n

  BLIBDLL_API static std::string Compress(const std::string line);																															//compress multiple tabs and spaces to a single space, within and without
  BLIBDLL_API static std::string CompressHard(const std::string line);																													//compress tabs and spaces, within and without
  BLIBDLL_API static std::string Trim(const std::string line);																																	//remove spaces and tabs before and after the line
  BLIBDLL_API static std::string TrimLeft(const std::string line);																															//remove spaces and tabs before the line
  BLIBDLL_API static std::string TrimRight(const std::string line);																															//remove spaces and tabs after the line

	BLIBDLL_API static std::string Sub(const std::string line,const size_t from);
  BLIBDLL_API static std::string Sub(const std::string line,const size_t from,const size_t to);																	//get a substring starting at from, ending at to
  BLIBDLL_API static std::string SubLeft(const std::string line,const size_t to);																								//get a substring from the start of the line until to
  BLIBDLL_API static std::string SubRight(const std::string line,const size_t from);																						//get a substring starting at from, until the end of the string

  BLIBDLL_API static std::string SubSized(const std::string line,const size_t from,const size_t size);													//get a substring starting at from with a length of size
  BLIBDLL_API static std::string SubSizedLeft(const std::string line,const size_t size);																				//get a substring starting at the left, with a length of size
  BLIBDLL_API static std::string SubSizedRight(const std::string line,const size_t size);																				//get a substring starting at the right, with a length counted back until size

  BLIBDLL_API static std::string Inbetween(const std::string line,const std::string left,const std::string right);							//get the string in between the first instance of string left, and before first instance of right (after left)
  BLIBDLL_API static std::string Before(const std::string line,const std::string right);																				//get the string before first instance of right
  BLIBDLL_API static std::string After(const std::string line,const std::string left);																					//get the string after first instance of left
	BLIBDLL_API static std::string BeforeLast(const std::string line,const std::string target);																		//get the string before the last instance of target
	BLIBDLL_API static std::string AfterLast(const std::string line,const std::string target);																		//get the string after the last instance of target

  BLIBDLL_API static std::string Remove(const std::string,const char_t c);																											//remove all target char from line
  BLIBDLL_API static std::string Remove(const std::string line,const std::string target);																				//remove all target strings from line
  BLIBDLL_API static std::string RemoveFirst(const std::string line,const std::string target);																	//remove first target string from line
  BLIBDLL_API static std::string RemoveLast(const std::string line,const std::string target);																		//remove last target string from line
  BLIBDLL_API static std::string RemoveTarget(const std::string line,const std::string target,const size_t pos);								//remove the pos target from line

  BLIBDLL_API static std::string RemoveBetween(const std::string line,const std::string left,const std::string right);					//remove the string in between the first instance of string left, and before first instance of right (after left)
  BLIBDLL_API static std::string RemoveBetween(const std::string line,const size_t from,const size_t to);												//remove the string in between from and to
  BLIBDLL_API static std::string RemoveBefore(const std::string line,const std::string target);																	//remove the string before target string
  BLIBDLL_API static std::string RemoveBefore(const std::string line,const size_t pos);																					//remove the string before pos
  BLIBDLL_API static std::string RemoveAfter(const std::string line,const std::string target);																	//remove the string after first instance of target
  BLIBDLL_API static std::string RemoveAfter(const std::string line,const size_t pos);																					//remove the string after pos
    
  BLIBDLL_API static std::string Replace(const std::string line,const std::string target,const std::string replacement);				//replace all target strings in line with replacement
  BLIBDLL_API static std::string ReplaceFirst(const std::string line,const std::string target,const std::string replacement);		//replace first target string in line with replacement
  BLIBDLL_API static std::string ReplaceLast(const std::string line,const std::string target,const std::string replacement);		//replace last target string in line with replacement

  BLIBDLL_API static std::string ToString(const char* format, ...);																															//sprintf function, except within this class    
	BLIBDLL_API static std::string BoolToString(const bool value);
	BLIBDLL_API static std::string UIntToString(const uint64_t value);																														//uint value to string
  BLIBDLL_API static std::string IntToString(const int64_t value);																															//int value to string
  BLIBDLL_API static std::string FloatToString(const float value);																															//float value to string																																									//cleanup
  
  BLIBDLL_API static std::string TypeEnumToString(const EnumVar_t value);
};

};

#endif
