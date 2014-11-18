#include "StringParser.h"

#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <stdarg.h>

using namespace blib;

int32_t StringParser::First(const std::string line,const std::string target){
  int32_t result=-1;
  size_t pos=line.find(target);
  if(pos!=std::string::npos)
    result=pos;
  return result;
}

int32_t StringParser::Last(const std::string line,const std::string target){
  int32_t result=-1;
  size_t pos=line.rfind(target);
  if(pos!=std::string::npos)
    result=pos;
  return result;
}

size_t StringParser::Count(const std::string line,char target){
  size_t result=0;
  std::size_t found=line.find(target);
  while(found!=std::string::npos){
    result++;
    found=line.find(target,found+1);
  }
  return result;
}

size_t StringParser::Count(const std::string line,const std::string target){
  size_t result=0;
  std::size_t found=line.find(target);
  while(found!=std::string::npos){
    result++;
    found=line.find(target,found+target.size());
  }
  return result;
}

bool StringParser::Compare(const std::string line,const std::string target){
  return Equals(line,target);
}

bool StringParser::CompareBool(std::string line,bool value,bool toLower){
  if(toLower)
    line=ToLower(line);

  if(value)
    return Equals(line,"true");
  else
    return Equals(line,"false");
}

bool StringParser::CompareInt(std::string line,int64_t value){
  return (ToInt64_t(line)==value);
}

bool StringParser::CompareUInt(std::string line,uint64_t value){
  return (ToUInt64_t(line)==value);
}

bool StringParser::CompareFloat(std::string line,float value){
  return (ToFloat(line)==value);
}

std::string StringParser::Append(std::string line,std::string append){
  line.append(append);
  return line;
}

std::string StringParser::ToLower(std::string line){
  std::transform(line.begin(), line.end(), line.begin(), ::tolower);
  return line;
}

std::string StringParser::ToUpper(std::string line){
  std::transform(line.begin(), line.end(), line.begin(), ::toupper);
  return line;
}

bool StringParser::Equals(const std::string line,const std::string target){
  return line==target;
}

bool StringParser::Contains(const std::string line,const std::string target){
  return (line.find(target)!=std::string::npos);
}

bool StringParser::ContainsAll(const std::string line,const std::vector<std::string> targets){
  bool result=true;
  for(size_t i=0;i<targets.size();i++){
    if(line.find(targets[i])!=std::string::npos)
      continue;
    else{
      result=false;
      break;
    }
  }
  return result;
}

bool StringParser::ContainsAll(const std::string line,const std::string targets){
  bool result=true;
  for(size_t i=0;i<targets.length();i++){
    if(line.find(targets[i])!=std::string::npos)
      continue;
    else{
      result=false;
      break;
    }
  }
  return result;
}

bool StringParser::ContainsAny(const std::string line,const std::vector<std::string> targets){
  bool result=false;
  for(size_t i=0;i<targets.size();i++){
    if(line.find(targets[i])!=std::string::npos){
      result=true;
      break;
    }
  }
  return result;
}

bool StringParser::ContainsAny(const std::string line,const std::string targets){
  bool result=false;
  for(size_t i=0;i<targets.size();i++){
    if(line.find(targets[i])!=std::string::npos){
      result=true;
      break;
    }
  }
  return result;
}

bool StringParser::ContainsOnly(const std::string line,const std::vector<std::string> targets){
  std::string test=line;
  for(size_t i=0;i<targets.size();i++){
    test=Remove(test,targets[i]);
  }
  return test.size()==0;
}

bool StringParser::ContainsOnly(const std::string line,const std::string targets){
  std::string test=line;
  for(size_t i=0;i<targets.length();i++){
    test=Remove(test,targets[i]);
  }
  return test.size()==0;
}

bool StringParser::Contains(const std::string line,const std::string target,const size_t cnt){
  return Contains(line,target,cnt,cnt);
}

bool StringParser::Contains(const std::string line,const std::string target,const size_t min,const size_t max){
  bool result=false;
  if((min>=0)||(max>=0)&&(max>=min)){
    size_t buf=Count(line,target);
		if(buf!=-1){
      result=(buf>=min)&&(buf<=max);
		}
  }
  return result;
}

bool StringParser::ContainsAny(const std::string line,const std::vector<std::string> targets,const size_t min,const size_t max){
  bool result=false;
  if((min>=0)||(max>=0)){
    if(max>=min){
      size_t buf=0;
      for(size_t i=0;i<targets.size();i++)
        buf=buf+Count(line,targets[i]);
      result=(buf>=min)&&(buf<=max);
    }
  }
  return result;
}

bool StringParser::ContainsAny(const std::string line,const std::string targets,const size_t min,const size_t max){
  bool result=false;
  if((min>=0)||(max>=0)&&(max>=min)){
    size_t buf=0;
		for(size_t i=0;i<targets.length();i++){
      buf=buf+Count(line,targets[i]);
		}
    result=(buf>=min)&&(buf<=max);
  }else
    result=ContainsAny(line,targets);
  return result;
}

bool StringParser::ContainsOnly(const std::string line,const std::vector<std::string> targets,const size_t min,const size_t max){
  bool result=ContainsOnly(line,targets);
  if(result){
    if((min>=0)||(max>=0)&&(max>=min)){
      size_t buf=0;
      for(size_t i=0;i<targets.size();i++)
        buf=buf+Count(line,targets[i]);
      result=(buf>=min)&&(buf<=max);
    }
  }
  return result;
}

bool StringParser::ContainsOnly(const std::string line,const std::string targets,const size_t min,const size_t max){
  bool result=ContainsOnly(line,targets);
  if(result){
    if((min>=0)||(max>=0)&&(max>=min)){
      size_t buf=0;
      for(size_t i=0;i<targets.length();i++)
        buf=buf+Count(line,targets[i]);
      result=(buf>=min)&&(buf<=max);
    }
  }
  return result;
}

std::vector<std::string> StringParser::SplitIntoArguments(const std::string line){
  std::vector<std::string> result;

  int32_t from=0;
  int32_t to=0;
  std::string args=line;
  std::string left;
  std::string right;
  std::vector<std::string> part;

  if(Contains(args,"\"",1))
    result.push_back(args);
  else{
    while(Count(args,"\"")>1){
      from=Position(args,"\"",0);
      to=Position(args,"\"",1);
      left=SubLeft(args,from);
      right=Sub(args,from+1,to);
      args=SubRight(args,to+1);
      part=Split(left,' ');
      for(size_t i=0;i<part.size();i++)
        result.push_back(part[i]);
      result.push_back(right);
    }

    part=Split(args,' ');
    for(size_t i=0;i<part.size();i++)
      result.push_back(part[i]);
  }

  return result;
}

std::string StringParser::GetParameter(const std::string line,const size_t nr){
  std::string result;

  std::vector<std::string> list=SplitIntoArguments(line);
  if((list.size()>nr)&&(nr>0))
    result=list[nr];

  return result;
}

int32_t StringParser::CntParameters(const std::string line){
  return SplitIntoArguments(line).size();
}

bool StringParser::StartsWith(const std::string line,const std::string target){
  return Compare(target,(line.substr(0,target.length())));
}

bool StringParser::EndsWith(const std::string line,const std::string target){
  bool result=false;
  int32_t pos=Last(line,target);
  if(pos>-1)
    result=Compare(target,SubRight(line,pos));
  return result;
}

bool StringParser::IsNumeric(const std::string line){
  return ContainsOnly(line,"0123456789");
}

bool StringParser::IsInteger(const std::string line){
  std::string value=line;
  if(value.size()>0){
    if(value[0]=='-')
      value.erase(value.begin());
  }
  return IsNumeric(value);
}

bool StringParser::IsFloat(const std::string line){
  std::string value=line;
  int32_t pos=First(value,".");
  if(pos>-1)
    value.erase(value.begin()+pos);
  return IsInteger(value);
}

bool StringParser::IsNegative(const std::string line){
  bool result=false;
  if(IsFloat(line)||(IsInteger(line)))
    result=(line[0]=='-');
  return result;
}

float32_t StringParser::ToFloat32_t(const std::string line,const int32_t decimals){
	float32_t result=0.0f;
	if(IsFloat(line)){
    std::string newLine=line;
    if((decimals>0)&&(StringParser::Contains(line,".")))
      newLine=StringParser::SubLeft(line,StringParser::Position(line,".")+decimals+2);
    result=atof(newLine.c_str());
  }
	return result;
}

float64_t StringParser::ToFloat64_t(const std::string line,const int32_t decimals){
	float32_t result=0.0f;
	if(IsFloat(line)){
    std::string newLine=line;
    if((decimals>0)&&(StringParser::Contains(line,".")))
      newLine=StringParser::SubLeft(line,StringParser::Position(line,".")+decimals+2);
    result=atof(newLine.c_str());
  }
	return result;
}

float StringParser::ToFloat(const std::string line,const int32_t decimals){
  return ToFloat32_t(line,decimals);
}

int64_t StringParser::ToInt(const std::string line){
  return ToInt64_t(line);
}

int8_t StringParser::ToInt8_t(const std::string line){
  int8_t result=0;
  if(IsInteger(line)){
    result=(int8_t)atol(line.c_str());
  }
  return result;
}

int16_t StringParser::ToInt16_t(const std::string line){
  int16_t result=0;
  if(IsInteger(line)){
    result=(int16_t)atol(line.c_str());
  }
  return result;
}

int32_t StringParser::ToInt32_t(const std::string line){
  int32_t result=0;
  if(IsInteger(line)){
    result=atol(line.c_str());
  }
  return result;
}

int64_t StringParser::ToInt64_t(const std::string line){
  int64_t result=0;
  if(IsInteger(line)){
    result=atol(line.c_str());
  }
  return result;
}

uint8_t StringParser::ToUInt8_t(const std::string line){
  uint8_t result=0;
  if(IsInteger(line)||(!IsNegative(line))){
    result=(uint8_t)strtoul(line.c_str(),NULL,0);
  }
  return result;
}

uint16_t StringParser::ToUInt16_t(const std::string line){
  uint16_t result=0;
  if(IsInteger(line)||(!IsNegative(line))){
    result=(uint16_t)strtoul(line.c_str(),NULL,0);
  }
  return result;
}

uint32_t StringParser::ToUInt32_t(const std::string line){
  uint32_t result=0;
  if(IsInteger(line)||(!IsNegative(line))){
    result=(uint32_t)strtoul(line.c_str(),NULL,0);
  }
  return result;
}

uint64_t StringParser::ToUInt64_t(const std::string line){
  uint64_t result=0;
  if(IsInteger(line)||(!IsNegative(line))){
    result=(uint64_t)strtoul(line.c_str(),NULL,0);
  }
  return result;
}

std::vector<std::string> StringParser::Split(const std::string line,const char_t delimiter,bool keepDelimiter){
  return Split(line,std::string(1,delimiter),keepDelimiter);
}

std::vector<std::string> StringParser::Split(const std::string line,const std::string delimiter,bool keepDelimiter){
  std::vector<std::string> result;
  std::string segment;
  std::string args=line;
  int32_t start=First(args,delimiter);

  while(start!=-1){
    segment=SubLeft(args,start);
    args=SubRight(args,start+delimiter.length());
    if(segment.length()>0)
      result.push_back(segment);
		if(keepDelimiter)
			result.back()=Append(result.back(),delimiter);
    start=First(args,delimiter);
  }

  if(args.length()>0)
    result.push_back(args);
  return result;
}

std::vector<std::string> StringParser::SplitLines(const std::string line,const bool keepEmpty){
  return Split(Replace(Replace(line,"\r\n","\n"),"\r",""),"\n");
}

std::string StringParser::Compress(const std::string line){
  bool bSpace=false;
  std::string result=line;
  result=Trim(result);
  size_t i=0;
  while(i<result.length()){
    if((result[i]==' ')||(result[i]=='\t')){
      if(bSpace){
        result.erase(result.begin()+i);
      }else{
        bSpace=true;
        i++;
      }
    }
    else{
      bSpace=false;
      i++;
    }
  }

  return result;
}

std::string StringParser::CompressHard(const std::string line){
  size_t i=0;
  std::string result=line;
  while(i<result.length()){
    if((result[i]==' ')||(result[i]=='\t')){
      result.erase(result.begin()+i);
    } else{
      i++;
    }
  }
  return result;
}

std::string StringParser::Trim(const std::string line){
  return TrimLeft(TrimRight(line));
}

std::string StringParser::TrimLeft(const std::string line){
  size_t i=0;
  std::string result=line;
  while(i<result.length()){
    if((result[i]==' ')||(result[i]=='\t')){
      result.erase(result.begin()+i);
    }else
      break;
  }
  return result;
}

std::string StringParser::TrimRight(const std::string line){
  std::string result=line;
  int32_t i=result.length()-1;
  while(i>=0){
    if((result[i]==' ')||(result[i]=='\t')){
      result.erase(result.begin()+i);
      i=i-1;
    }else
      break;
  }
  return line;
}

std::string StringParser::Sub(const std::string line,const size_t from){
	std::string result;
	if(from<line.size()){
	  result=line.substr(from);
	}
	return result;
}

std::string StringParser::Sub(const std::string line,const size_t from,const size_t to){
  std::string result;
  if(from<line.size()){
    if(to<0)
      result=line.substr(from);
    else if(from<to){
      int32_t cnt=to-from;
      if(from<line.length())
        result=line.substr(from,cnt);
    }
  }
  return result;
}

std::string StringParser::SubLeft(const std::string line,const size_t to){
  return Sub(line,0,to);
}

std::string StringParser::SubRight(const std::string line,const size_t from){
  return Sub(line,from);
}

std::string StringParser::SubSized(const std::string line,const size_t from,const size_t size){
  std::string result;
  if(from<line.length())
    result=line.substr(from,size);
  return result;
}

std::string StringParser::SubSizedLeft(const std::string line,const size_t size){
  return SubSized(line,0,size);
}

std::string StringParser::SubSizedRight(const std::string line,const size_t size){
  return SubSized(line,line.length()-size,size);
}

std::string StringParser::Inbetween(const std::string line,const std::string left,const std::string right){
  std::string result="";
  int32_t start=First(line,left);
  int32_t stop=First(line,right);

  if((start>-1)&&(stop>-1)){
    start=start+left.size();
    if(start<stop){
      result=Sub(line,start,stop);
    }
  }

  return result;
}

std::string StringParser::Before(const std::string line,const std::string right){
  std::string result=line;
  int32_t stop=First(line,right);

  if(stop>0)
    result=SubLeft(line,stop);
  else if(stop==0)
    result="";
  return result;
}

std::string StringParser::After(const std::string line,const std::string left){
  std::string result="";
  int32_t start=First(line,left);

  if(start>-1){
		size_t resultStart=left.size()+start;
    if(resultStart<line.size())
      result=line.substr(resultStart);
  }

  return result;
}

std::string StringParser::Remove(const std::string line,const std::string target){
  return Replace(line,target,"");
}
std::string StringParser::Remove(const std::string line,const char_t c){
  return Remove(line,std::string(1,c));
}

std::string StringParser::RemoveFirst(const std::string line,const std::string target){
  return ReplaceFirst(line,target,"");
}

std::string StringParser::RemoveLast(const std::string line,const std::string target){
  int32_t pos=Last(line,target);
  if(pos>=0)
    line==Sub(line,pos,pos+target.size());
  return line;
}

std::string StringParser::RemoveTarget(const std::string line,const std::string target,const size_t pos){
  std::string result=line;
  int32_t start=Position(line,target,pos);
  if(start>=0)
    result=Sub(result,start,start+target.size());
  return result;
}

std::string StringParser::RemoveBetween(const std::string line,const std::string left,const std::string right){
  std::string result;
  int32_t start=Position(line,left);
  int32_t stop=Position(line,right);
  if(start>=0){
    if(start>stop){
      result=Sub(line,start,stop);
    }
  }
  return result;
}

std::string StringParser::RemoveBetween(const std::string line,const size_t from,const size_t to){
  return (SubLeft(line,from)).append(SubRight(line,to));
}

std::string StringParser::RemoveBefore(const std::string line,const std::string target){
  return RemoveBefore(line,First(line,target));
}

std::string StringParser::RemoveBefore(const std::string line,const size_t pos){
  return SubRight(line,pos);
}

std::string StringParser::RemoveAfter(const std::string line,const std::string target){
  std::string result=line;
  size_t pos=line.find(target);
  if(pos!=std::string::npos)
    result=RemoveAfter(result,pos+target.length());
  return result;
}

std::string StringParser::RemoveAfter(const std::string line,const size_t pos){
  std::string result=line;
  if(pos>0)
    result=SubLeft(line,pos);
  return result;
}

std::string StringParser::Replace(const std::string line,const std::string target,const std::string replacement){
  std::string right=line;
  std::string result;
  while(Count(right,target)>0){
    std::string left=Before(right,target);
    right=After(right,target);
    result.append(left);
    result.append(replacement);
  }
  result.append(right);
  return result;
}

std::string StringParser::ReplaceFirst(const std::string line,const std::string target,const std::string replacement){
  std::string result;
  if(First(line,target)>-1)
    result=Append(Append(Before(line,target),replacement),After(line,target));
  else
    result=line;
  return result;
}

std::string StringParser::ReplaceLast(const std::string line,const std::string target,const std::string replacement){
  std::string result;
  int32_t last=Last(line,target);
  if(last>-1)
    result=Append(Append(SubLeft(line,last),replacement),SubRight(line,last+target.size()));
  else
    result=line;
  return line;
}

std::string StringParser::ToString(const char* format, ...){
  char message[5121];
  message[sizeof(message) - 1] = 0;

  va_list arg;
  va_start(arg, format);
  vsnprintf(message, sizeof(message) - 1, format, arg);

  va_end(arg);

  return std::string(message);
}

std::string StringParser::BoolToString(const bool value){
  if(value)
    return "true";
  else
    return "false";
}

std::string StringParser::UIntToString(const uint64_t value){
  return ToString("%lu",value);
}

std::string StringParser::IntToString(const int64_t value){
  return ToString("%li",value);
}

std::string StringParser::FloatToString(const float value){
  return ToString("%f",value);
}

int32_t StringParser::Position(const std::string line,const std::string target,const size_t nr){
  int32_t result=nr;
  std::size_t found=0;
  while((found!=std::string::npos)&&(result>0)){
    result--;
		found=line.find(target,found+target.size());
  }
  if(found!=std::string::npos)
    result=found;
  else
    result=-1;
  return result;
}

bool StringParser::ToBool(const std::string line){
  return Compare(line,"true");
}

std::string StringParser::BeforeLast(const std::string line,const std::string target){
	int32_t pos=Last(line,target);
	std::string result=line;
	if(pos>0)
		result=RemoveAfter(line,Last(line,target));
	else if(pos==0)
		result="";
	return result;
}

bool StringParser::IsBool(const std::string line){
	return Compare(line,"true")||Compare(line,"false");
}

std::string StringParser::AfterLast(const std::string line,const std::string target){
	int32_t pos=Last(line,target);
	std::string result=line;
	if(pos>=0)
		result=RemoveFirst(RemoveBefore(line,pos),target);
  return result;
}

std::string StringParser::Assign(const std::string line){
  return line;
}

std::string StringParser::Assign(const char_t& c,const size_t length){
	return std::string(&c,length);
}

static std::string TypeEnumToString(const EnumVar_t value){
  std::string result;
  switch(value){
    case BOOL_T:
      result="bool";
      break;
    case CHAR_T:
      result="char_t";
      break;
    case INT8_T:
      result="int8_t";
      break;
    case UINT8_T:
      result="uint8_t";
      break;
    case INT16_T:
      result="int16_t";
      break;
    case UINT16_T:
      result="uint16_t";
      break;
    case INT32_T:
      result="int32_t";
      break;
    case UINT32_T:
      result="uint32_t";
      break;
    case INT64_T:
      result="int64_t";
      break;
    case UINT64_T:
      result="uint64_t";
      break;
    case LONG_T:
      result="long_t";
      break;
    case ULONG_T:
      result="ulong_t";
      break;
    case LLONG_T:
      result="llong_t";
      break;
    case ULLONG_T:
      result="ullong_t";
      break;
    case FLOAT32_T:
      result="float32_t";
      break;
    case FLOAT64_T:
      result="float64_t";
      break;
    case LFLOAT64_T:
      result="lfloat64_t";
      break;
    case STRING_T:
      result="std::string";
      break;
    case VOID_T:
      result="void";
      break;
    case PBOOL_T:
      result="bool*";
      break;
    case PCHAR_T:
      result="char_t*";
      break;
    case PINT8_T:
      result="int8_t*";
      break;
    case PUINT8_T:
      result="uint8_t*";
      break;
    case PINT16_T:
      result="int16_t*";
      break;
    case PUINT16_T:
      result="uint16_t*";
      break;
    case PINT32_T:
      result="int32_t*";
      break;
    case PUINT32_T:
      result="uint32_t*";
      break;
    case PINT64_T:
      result="int64_t*";
      break;
    case PUINT64_T:
      result="uint64_t*";
      break;
    case PLONG_T:
      result="long_t*";
      break;
    case PULONG_T:
      result="ulong_t*";
      break;
    case PLLONG_T:
      result="llong_t*";
      break;
    case PULLONG_T:
      result="ullong*";
      break;
    case PFLOAT32_T:
      result="float32_t*";
      break;
    case PFLOAT64_T:
      result="float64_t*";
      break;
    case PLFLOAT64_T:
      result="lfloat64_t*";
      break;
    case PSTRING_T:
      result="std::string*";
      break;
    case PVOID_T:
      result="void*";
      break;
  }
  return result;
}
