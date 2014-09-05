#ifndef BLIB_STRINGPARSER_H
#define BLIB_STRINGPARSER_H

#include <string>
#include <vector>
#include "Base.h"

namespace blib{

class StringParser:public Base{
public: 
  static int32_t First(const std::string line,const std::string target);																						//return start pos of first instance of target, -1 on fail
  static int32_t Last(const std::string line,const std::string target);																							//return start pos of last instance of target, -1 on fail
	
  static int32_t Position(const std::string line,const std::string target,const size_t nr=1);												//return position of nr instance, -1 on fail
  static size_t Count(const std::string line,const std::string target);																							//return nr of instances of target
  static size_t Count(const std::string line,const char_t target);																									//return nr of instances of target

	static std::string Assign(const std::string line);
	static std::string Assign(const char_t& c,const size_t length=1);

  static std::string Append(const std::string line,const std::string append);																				//returns line with append string added to it

  static int32_t CntParameters(const std::string line);																															//return the number of space seperated string
  static std::string GetParameter(const std::string line,const size_t nr);																					//return the nr string after split with space

  static std::string ToLower(const std::string line);																																//returns line in lowercase
  static std::string ToUpper(const std::string line);																																//returns line in uppercase
  
  static bool Equals(const std::string line,const std::string target);																							//compare between line and target
  static bool Compare(const std::string line,const std::string target);																							//compare between line and target
  static bool CompareBool(const std::string line,const bool value,const bool toLower=false);												//value to string, then string compare
  static bool CompareInt(const std::string line,const int64_t value);																								//value to string, then string compare
  static bool CompareUInt(const std::string line,const uint64_t value);																							//value to string, then string compare
  static bool CompareFloat(const std::string line,const float value);																								//value to string, then string compare

  static bool Contains(const std::string line,const std::string target);																						//does the line contains the target
  static bool Contains(const std::string line,const std::string target,size_t cnt);																	//does the line contains the target cnt nr of times
  static bool ContainsAll(const std::string line,const std::vector<std::string> targets);														//does the line contain all the targets
  static bool ContainsAll(const std::string line,const std::string targets);																				//does the line contain all the targets
  static bool ContainsAny(const std::string line,const std::vector<std::string> targets);														//does the line contain any of the targets
  static bool ContainsAny(const std::string line,const std::string targets);																				//does the line contain any of the targets
  static bool ContainsOnly(const std::string line,const std::vector<std::string> targets);													//does the line only contain the given targets
  static bool ContainsOnly(const std::string line,const std::string targets);																				//does the line only contain the given targets

  static bool Contains(const std::string line,const std::string target,const size_t min,const size_t max);										//does the line contains the min or max of the target
  static bool ContainsAny(const std::string line,const std::vector<std::string> targets,const size_t min,const size_t max);	//does the line contains the min or max of the targets
  static bool ContainsAny(const std::string line,const std::string targets,const size_t min,const size_t max);								//does the line contains any of the targets
  static bool ContainsOnly(const std::string line,const std::vector<std::string> targets,const size_t min,const size_t max); //does the line contain only the targets
  static bool ContainsOnly(const std::string line,const std::string targets,const size_t min,const size_t max);							//does the line contain any of the targets

  static bool StartsWith(const std::string line,const std::string target);																					//does the line start with the target
  static bool EndsWith(const std::string line,const std::string target);																						//does the line end with the target
  
  static bool IsNumeric(const std::string line);																																		//is the string numerical legal?
  static bool IsInteger(const std::string line);																																		//is the string an integer? (no decimals)
  static bool IsFloat(const std::string line);																																			//is the string an integer or floating?
  static bool IsNegative(const std::string line);																																		//is the string a negative numeric?
	static bool IsBool(const std::string line);																																				//is the string a boolean value?
  
  static float ToFloat(const std::string line,const int32_t decimals=-1);																						//returns a floating point with decimals nr of decimals
  static int64_t ToInt(const std::string line);																																			//returns an integer from ToInt64(
  
  static int8_t ToInt8_t(const std::string line);																																		//returns a 8 bit signed integer
	static int16_t ToInt16_t(const std::string line);																																	//returns a 16 bit signed integer
  static int32_t ToInt32_t(const std::string line);																																	//returns a 32 bit signed integer
  static int64_t ToInt64_t(const std::string line);																																	//returns a 64 bit signed integer
  
  static uint8_t ToUInt8_t(const std::string line);																																	//returns a 8 bit unsigned integer
	static uint16_t ToUInt16_t(const std::string line);																																//returns a 16 bit unsigned integer
  static uint32_t ToUInt32_t(const std::string line);																																//returns a 32 bit unsigned integer
  static uint64_t ToUInt64_t(const std::string line);																																//returns a 64 bit unsigned integer
  
	static float32_t ToFloat32_t(const std::string line,const int32_t decimals=-1);                                   //string to normal float
	static float64_t ToFloat64_t(const std::string line,const int32_t decimals=-1);                                   //string to big float

  static bool ToBool(const std::string line);																																				//returns true or false

  static std::vector<std::string> Split(const std::string line,const char delimiter,bool keepDelimiter=false);				 //split the line into segments, snip on the delimiter (which is removed)
  static std::vector<std::string> Split(const std::string line,const std::string delimiter,bool keepDelimiter=false); //split the line into segments, snip on the delimiter (which is removed)

  static std::vector<std::string> SplitIntoArguments(const std::string line);																				//splits data into arguments

  static std::vector<std::string> SplitLines(const std::string line,const bool keepEmpty=false);										//split the line into segments, seperated by \r\n or \r or \n

  static std::string Compress(const std::string line);																															//compress multiple tabs and spaces to a single space, within and without
  static std::string CompressHard(const std::string line);																													//compress tabs and spaces, within and without
  static std::string Trim(const std::string line);																																	//remove spaces and tabs before and after the line
  static std::string TrimLeft(const std::string line);																															//remove spaces and tabs before the line
  static std::string TrimRight(const std::string line);																															//remove spaces and tabs after the line

	static std::string Sub(const std::string line,const size_t from);
  static std::string Sub(const std::string line,const size_t from,const size_t to);																	//get a substring starting at from, ending at to
  static std::string SubLeft(const std::string line,const size_t to);																								//get a substring from the start of the line until to
  static std::string SubRight(const std::string line,const size_t from);																						//get a substring starting at from, until the end of the string

  static std::string SubSized(const std::string line,const size_t from,const size_t size);													//get a substring starting at from with a length of size
  static std::string SubSizedLeft(const std::string line,const size_t size);																				//get a substring starting at the left, with a length of size
  static std::string SubSizedRight(const std::string line,const size_t size);																				//get a substring starting at the right, with a length counted back until size

  static std::string Inbetween(const std::string line,const std::string left,const std::string right);							//get the string in between the first instance of string left, and before first instance of right (after left)
  static std::string Before(const std::string line,const std::string right);																				//get the string before first instance of right
  static std::string After(const std::string line,const std::string left);																					//get the string after first instance of left
	static std::string BeforeLast(const std::string line,const std::string target);																		//get the string before the last instance of target
	static std::string AfterLast(const std::string line,const std::string target);																		//get the string after the last instance of target

  static std::string Remove(const std::string,const char_t c);																											//remove all target char from line
  static std::string Remove(const std::string line,const std::string target);																				//remove all target strings from line
  static std::string RemoveFirst(const std::string line,const std::string target);																	//remove first target string from line
  static std::string RemoveLast(const std::string line,const std::string target);																		//remove last target string from line
  static std::string RemoveTarget(const std::string line,const std::string target,const size_t pos);								//remove the pos target from line

  static std::string RemoveBetween(const std::string line,const std::string left,const std::string right);					//remove the string in between the first instance of string left, and before first instance of right (after left)
  static std::string RemoveBetween(const std::string line,const size_t from,const size_t to);												//remove the string in between from and to
  static std::string RemoveBefore(const std::string line,const std::string target);																	//remove the string before target string
  static std::string RemoveBefore(const std::string line,const size_t pos);																					//remove the string before pos
  static std::string RemoveAfter(const std::string line,const std::string target);																	//remove the string after first instance of target
  static std::string RemoveAfter(const std::string line,const size_t pos);																					//remove the string after pos
    
  static std::string Replace(const std::string line,const std::string target,const std::string replacement);				//replace all target strings in line with replacement
  static std::string ReplaceFirst(const std::string line,const std::string target,const std::string replacement);		//replace first target string in line with replacement
  static std::string ReplaceLast(const std::string line,const std::string target,const std::string replacement);		//replace last target string in line with replacement

  static std::string ToString(const char* format, ...);																															//sprintf function, except within this class    
	static std::string BoolToString(const bool value);
	static std::string UIntToString(const uint64_t value);																														//uint value to string
  static std::string IntToString(const int64_t value);																															//int value to string
  static std::string FloatToString(const float value);																															//float value to string																																									//cleanup
};

};

#endif
