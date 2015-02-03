#include "RawParser.h"
#include "BaseDefines.h"
#include "StringParser.h"

#include <cstring>

using namespace blib;

uint8_t RawParser::GetUInt8_t(const char_t& buffer,const size_t start){
	union8_t data;
	std::memcpy(data.c,&((&buffer)[start]),1);
	return data.u_value;
}

int8_t RawParser::GetInt8_t(const char_t& buffer,const size_t start){	
	return (&buffer)[start];
}

uint16_t RawParser::GetUInt16_t(const char_t& buffer,const size_t start){
	union16_t data;
	std::memcpy(data.c,&((&buffer)[start]),2);
	return data.u_value;
}

int16_t RawParser::GetInt16_t(const char_t& buffer,const size_t start){
	union16_t data;
	std::memcpy(data.c,&((&buffer)[start]),2);
	return data.value;
}

uint32_t RawParser::GetUInt32_t(const char_t& buffer,const size_t start){
	union32_t data;
	std::memcpy(data.c,&((&buffer)[start]),4);
	return data.u_value;
}

int32_t RawParser::GetInt32_t(const char_t& buffer,const size_t start){
	union32_t data;
	std::memcpy(data.c,&((&buffer)[start]),4);
	return data.value;
}

uint64_t RawParser::GetUInt64_t(const char_t& buffer,const size_t start){
	union64_t data;
	std::memcpy(data.c,&((&buffer)[start]),8);
	return data.u_value;
}
											
int64_t RawParser::GetInt64_t(const char_t& buffer,const size_t start){
	union64_t data;
	std::memcpy(data.c,&((&buffer)[start]),8);
	return data.value;
}
												
float32_t RawParser::GetFloat32_t(const char_t& buffer,const size_t start){
	union32_t data;
	std::memcpy(data.c,&((&buffer)[start]),4);
	return data.f_value;
}

float64_t RawParser::GetFloat64_t(const char_t& buffer,const size_t start){
	union64_t data;
	std::memcpy(data.c,&((&buffer)[start]),8);
	return data.f_value;
}
		
std::string RawParser::GetString(const char_t& buffer,const size_t start,const size_t size){
	std::string result;
	if(size>0)
		result=std::string((&buffer)[start],size);
	else
		result=((&buffer)[start]);
	return result;
}

EnumResult_t RawParser::GetVariable(const char_t& buffer,const size_t start,const std::type_info* info,void* variable,const size_t size){
	EnumResult_t result=FAIL;
	if(info!=&typeid(void)){
		result=SUCCESS;
		if(info==&typeid(uint8_t)){			
			uint8_t value=GetUInt8_t(buffer,start);
			std::memcpy(variable,&value,1);
		}else if(info==&typeid(int8_t)){
			int8_t value=GetInt8_t(buffer,start);
			std::memcpy(variable,&value,1);
		}else if(info==&typeid(char_t)){			
			((char_t*)variable)[0]=(&buffer)[start];
		}else if(info==&typeid(uint16_t)){
			uint16_t value=GetUInt16_t(buffer,start);
			std::memcpy(variable,&value,2);
		}else if(info==&typeid(int16_t)){
			int16_t value=GetInt16_t(buffer,start);
			std::memcpy(variable,&value,2);
		}else if(info==&typeid(uint32_t)){
			uint32_t value=GetUInt32_t(buffer,start);
			std::memcpy(variable,&value,4);
		}else if(info==&typeid(int32_t)){
			int32_t value=GetInt32_t(buffer,start);
			std::memcpy(variable,&value,4);
		}else if(info==&typeid(uint64_t)){
			uint64_t value=GetUInt64_t(buffer,start);
			std::memcpy(variable,&value,8);
		}else if(info==&typeid(int64_t)){
			int64_t value=GetInt64_t(buffer,start);
			std::memcpy(variable,&value,8);
		}else if(info==&typeid(float32_t)){
			float32_t value=GetFloat32_t(buffer,start);
			std::memcpy(variable,&value,4);
		}else if(info==&typeid(float64_t)){
			float64_t value=GetFloat64_t(buffer,start);
			std::memcpy(variable,&value,8);
		}else if(info==&typeid(std::string)){
			std::string value=GetString(buffer,start,size);
			((std::string*)variable)->assign(value);
		}else
			result=FAIL;
	}
	return result;
}

EnumResult_t RawParser::SetUInt8_t(const uint8_t value,char_t& target,const size_t start){  
	union8_t data;
	data.u_value=value;
	std::memcpy(&(&target)[start],data.c,1);
	return SUCCESS;
}
	
EnumResult_t RawParser::SetInt8_t(const int8_t value,char_t& target,const size_t start){
	union8_t data;
	data.value=value;
	std::memcpy(&(&target)[start],data.c,1);
	return SUCCESS;
}

EnumResult_t RawParser::SetUInt16_t(const uint16_t value,char_t& target,const size_t start){
	union16_t data;
	data.u_value=value;
	std::memcpy(&(&target)[start],data.c,2);
	return SUCCESS;
}

EnumResult_t RawParser::SetInt16_t(const int16_t value,char_t& target,const size_t start){
	union16_t data;
	data.value=value;
	std::memcpy(&(&target)[start],data.c,2);
	return SUCCESS;
}

EnumResult_t RawParser::SetUInt32_t(const uint32_t value,char_t& target,const size_t start){
	union32_t data;
	data.u_value=value;
	std::memcpy(&(&target)[start],data.c,4);
	return SUCCESS;
}

EnumResult_t RawParser::SetInt32_t(const int32_t value,char_t& target,const size_t start){
	union32_t data;
	data.value=value;
	std::memcpy(&(&target)[start],data.c,4);
	return SUCCESS;
}

EnumResult_t RawParser::SetUInt64_t(const uint64_t value,char_t& target,const size_t start){
	union64_t data;
	data.u_value=value;
	std::memcpy(&(&target)[start],data.c,8);
	return SUCCESS;
}

EnumResult_t RawParser::SetInt64_t(const int64_t value,char_t& target,const size_t start){
	union64_t data;
	data.value=value;
	std::memcpy(&(&target)[start],data.c,8);
	return SUCCESS;
}

EnumResult_t RawParser::SetFloat32_t(const float32_t value,char_t& target,const size_t start){
	union32_t data;
	data.value=value;
	std::memcpy(&(&target)[start],data.c,4);
	return SUCCESS;
}

EnumResult_t RawParser::SetFloat64_t(const float64_t value,char_t& target,const size_t start){
	union64_t data;
	data.value=value;
	std::memcpy(&(&target)[start],data.c,8);
	return SUCCESS;
}

EnumResult_t RawParser::SetString(const std::string& value,char_t& target,const size_t start){
	EnumResult_t result=FAIL;
	size_t size=value.size();
	if(size>0){
		std::memcpy(&(&target)[start],value.c_str(),size);
		result=SUCCESS;
	}
  return result;
}

EnumResult_t RawParser::SetVariable(const std::string& value,const EnumVar_t type,char_t& target,const size_t start){
	EnumResult_t result=FAIL;
	if(value.size()>0){
		switch(type){
			case CHAR_T:
				(&target)[start]=value[0];
				result=SUCCESS;
				break;
			case INT8_T:
				result=SetInt8_t(StringParser::ToInt8_t(value),target,start);
				break;
			case UINT8_T:
				result=SetUInt8_t(StringParser::ToInt8_t(value),target,start);
				break;
			case INT16_T:
				result=SetInt16_t(StringParser::ToInt16_t(value),target,start);
				break;
			case UINT16_T:
				result=SetUInt16_t(StringParser::ToUInt16_t(value),target,start);
				break;
			case INT32_T:
				result=SetInt32_t(StringParser::ToInt32_t(value),target,start);
				break;
			case UINT32_T:
				result=SetUInt32_t(StringParser::ToUInt32_t(value),target,start);
				break;
			case INT64_T:
				result=SetInt64_t(StringParser::ToInt64_t(value),target,start);
				break;
			case UINT64_T:
				result=SetUInt64_t(StringParser::ToUInt64_t(value),target,start);
				break;
			case LONG_T:
				result=SetInt64_t(StringParser::ToInt64_t(value),target,start);
				break;
			case ULONG_T:
				result=SetUInt64_t(StringParser::ToUInt64_t(value),target,start);
				break;
			case LLONG_T:
				result=SetInt64_t(StringParser::ToInt64_t(value),target,start);
				break;
			case ULLONG_T:
				result=SetUInt64_t(StringParser::ToUInt64_t(value),target,start);
				break;
			case FLOAT32_T:
				result=SetFloat32_t(StringParser::ToFloat32_t(value),target,start);
				break;
			case FLOAT64_T:
				result=SetFloat64_t(StringParser::ToFloat64_t(value),target,start);
				break;
			case LFLOAT64_T:
				result=SetFloat64_t(StringParser::ToFloat64_t(value),target,start);
				break;
			case STRING_T:
        ((std::string*)&target)->assign(value);
				result=SUCCESS;
				break;
		}
	}
	return result;
}

EnumResult_t RawParser::FromString(const std::string& source,const EnumVar_t type,void* target){
	EnumResult_t result=FAIL;
	if((target!=NULL)&&(source.size()>0)){
		result=SUCCESS;
		switch(type){
			case PCHAR_T:
				target=(void*)(*((char**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case CHAR_T:
				*((char_t*)target)=source[0];				
				break;
			case PINT8_T:
				target=(void*)(*((int8_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case INT8_T:
				*((int8_t*)target)=StringParser::ToInt8_t(source);				
				break;
			case PUINT8_T:
				target=(void*)(*((uint8_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case UINT8_T:
				*((uint8_t*)target)=StringParser::ToUInt8_t(source);								
				break;
			case PINT16_T:
				target=(void*)(*((int16_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case INT16_T:
				*((int16_t*)target)=StringParser::ToInt16_t(source);				
				break;
			case PUINT16_T:
				target=(void*)(*((uint16_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case UINT16_T:
				*((uint16_t*)target)=StringParser::ToUInt16_t(source);								
				break;
			case PINT32_T:
				target=(void*)(*((int32_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case INT32_T:
				*((int32_t*)target)=StringParser::ToInt32_t(source);				
				break;
			case PUINT32_T:
				target=(void*)(*((uint32_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case UINT32_T:
				*((uint32_t*)target)=StringParser::ToUInt32_t(source);								
				break;
			case PINT64_T:
				target=(void*)(*((int64_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case INT64_T:
				*((int64_t*)target)=StringParser::ToInt64_t(source);				
				break;
			case PUINT64_T:
				target=(void*)(*((uint64_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case UINT64_T:
				*((uint64_t*)target)=StringParser::ToUInt64_t(source);								
				break;
			case PLONG_T:
				target=(void*)(*((int64_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case LONG_T:
				*((long_t*)target)=StringParser::ToInt64_t(source);								
				break;
			case PULONG_T:
				target=(void*)(*((uint64_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case ULONG_T:
				*((ulong_t*)target)=StringParser::ToUInt64_t(source);				
				break;
			case PLLONG_T:
				target=(void*)(*((int64_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case LLONG_T:
				*((llong_t*)target)=StringParser::ToInt64_t(source);								
				break;
			case PULLONG_T:
				target=(void*)(*((uint64_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case ULLONG_T:
				*((ullong_t*)target)=StringParser::ToUInt64_t(source);				
				break;
			case PFLOAT32_T:
				target=(void*)(*((float32_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case FLOAT32_T:
				*((float32_t*)target)=StringParser::ToFloat32_t(source);				
				break;
			case PFLOAT64_T:
				target=(void*)(*((float64_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case FLOAT64_T:
				*((float64_t*)target)=StringParser::ToFloat64_t(source);				
				break;
			case PLFLOAT64_T:
				target=(void*)(*((float64_t**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case LFLOAT64_T:
				*((lfloat64_t*)target)=StringParser::ToFloat64_t(source);				
				break;
			case PSTRING_T:
				target=(void*)(*((std::string**)target));
				if(target==NULL){
					result=FAIL;
					break;
				}
			case STRING_T:				
				*((std::string*)target)=source;
				break;
			default:
				result=FAIL;
		}
	}
	return result;
}

EnumResult_t RawParser::FromString(const std::string& source,const std::type_info* type,void* target){
  return FromString(source,GetEnumVar(type),target);
}

EnumResult_t RawParser::ToString(const void* source,const EnumVar_t type,std::string& target){
	EnumResult_t result=SUCCESS;
	switch(type){
		case CHAR_T:
			target=StringParser::Assign(*((char_t*)source));								
			break;
		case INT8_T:
			target=StringParser::ToString("%i",(*((int8_t*)source)));
			break;
		case UINT8_T:
		  target=StringParser::ToString("%u",(*((uint8_t*)source)));
			break;
		case INT16_T:
			target=StringParser::ToString("%i",(*((int16_t*)source)));
			break;
		case UINT16_T:
			target=StringParser::ToString("%u",(*((uint16_t*)source)));
			break;
		case INT32_T:
			target=StringParser::ToString("%i",(*((int32_t*)source)));
			break;
		case UINT32_T:
			target=StringParser::ToString("%u",(*((uint32_t*)source)));
			break;
		case INT64_T:
			target=StringParser::ToString("%l",(*((int64_t*)source)));
			break;
		case UINT64_T:
			target=StringParser::ToString("%lu",(*((uint64_t*)source)));
			break;
		case LONG_T:
			target=StringParser::ToString("%i",(*((long_t*)source)));
			break;
		case ULONG_T:
			target=StringParser::ToString("%u",(*((ulong_t*)source)));
			break;
		case LLONG_T:
			target=StringParser::ToString("%l",(*((llong_t*)source)));
			break;
		case ULLONG_T:
			target=StringParser::ToString("%lu",(*((ullong_t*)source)));
			break;
		case FLOAT32_T:
			target=StringParser::ToString("%f",(*((float32_t*)source)));
			break;
		case FLOAT64_T:
			target=StringParser::ToString("%f",(*((float64_t*)source)));
			break;
		case LFLOAT64_T:
			target=StringParser::ToString("%f",(*((lfloat64_t*)source)));
			break;
		case STRING_T:				
			target=*((std::string*)source);
			break;
    case PCHAR_T:
      if(((char_t*)source)!=NULL)
        target=StringParser::ToString("%s",((char_t*)source));
      else
        result=FAIL;
      break;
    case PINT8_T:
      if(((int8_t*)source)!=NULL)
        target=StringParser::ToString("%i",((int8_t*)source));
      else
        result=FAIL;
      break;
    case PUINT8_T:
      if(((uint8_t*)source)!=NULL)
        target=StringParser::ToString("%u",((uint8_t*)source));
      else
        result=FAIL;
      break;
    case PINT16_T:
      if(((int16_t*)source)!=NULL)
        target=StringParser::ToString("%i",((int16_t*)source));
      else
        result=FAIL;
      break;
    case PUINT16_T:
      if(((uint16_t*)source)!=NULL)
        target=StringParser::ToString("%u",((uint16_t*)source));
      else
        result=FAIL;
      break;
    case PINT32_T:
      if(((int32_t*)source)!=NULL)
        target=StringParser::ToString("%i",((int32_t*)source));
      else
        result=FAIL;
      break;
    case PUINT32_T:
      if(((uint32_t*)source)!=NULL)
        target=StringParser::ToString("%u",((uint32_t*)source));
      else
        result=FAIL;
      break;
    case PINT64_T:
      if(((int64_t*)source)!=NULL)
        target=StringParser::ToString("%l",((int64_t*)source));
      else
        result=FAIL;
      break;
    case PUINT64_T:
      if(((uint64_t*)source)!=NULL)
        target=StringParser::ToString("%lu",((uint64_t*)source));
      else
        result=FAIL;
      break;
    case PLONG_T:
      if(((long_t*)source)!=NULL)
        target=StringParser::ToString("%i",((long_t*)source));
      else
        result=FAIL;
      break;
    case PULONG_T:
      if(((ulong_t*)source)!=NULL)
        target=StringParser::ToString("%u",((ulong_t*)source));
      else
        result=FAIL;
      break;
    case PLLONG_T:
      if(((llong_t*)source)!=NULL)
        target=StringParser::ToString("%l",((llong_t*)source));
      else
        result=FAIL;
      break;
    case PULLONG_T:
      if(((ullong_t*)source)!=NULL)
        target=StringParser::ToString("%lu",((ullong_t*)source));
      else
        result=FAIL;
      break;
    case PFLOAT32_T:
      if(((float32_t*)source)!=NULL)
        target=StringParser::ToString("%f",((float32_t*)source));
      else
        result=FAIL;
      break;
    case PFLOAT64_T:
      if(((float64_t*)source)!=NULL)
        target=StringParser::ToString("%f",((float64_t*)source));
      else
        result=FAIL;
      break;
    case PSTRING_T:
      if(((std::string*)source)!=NULL)
        target=*((std::string*)source);
      else
        result=FAIL;
      break;
		default:
			result=FAIL;
	}
	return result;
}

EnumResult_t RawParser::ToString(const void *source, const std::type_info *type, std::string &target){
  EnumResult_t result=FAIL;
  if(GetTypeInfoVarMap().find(type)!=GetTypeInfoVarMap().end())
    result=ToString(source,GetTypeInfoVarMap().find(type)->second,target);
  return result;
}
