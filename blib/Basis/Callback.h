#ifndef BLIB_CALLBACK_H
#define BLIB_CALLBACK_H

#include "Base.h"
#include "BaseDefines.h"
#include "RawParser.h"
#include <typeinfo>
#include <string>
#include <vector>

namespace blib{

class CallbackTemp{ 																								//universal class for callbacks, no worrying about class and parameter types
protected:
	void* returnRef;																									//pointer to return value
	const std::type_info* returnTypeInfo;															//return type typeinfo, default typeinfo(void)
	std::vector<void*> parameters;																		//pointer to parameter values
	std::vector<const std::type_info*> parametersTypeInfo;						//parameter types
public:
	BLIB_LIB_API CallbackTemp();																										//init returnValue pointer
  BLIB_LIB_API size_t GetNrOfParameters(void);																		//return size of parameters vector
  BLIB_LIB_API const std::type_info* GetParamTypeInfo(size_t nr);								//returns type of argument nr requested, or type info of void	
  BLIB_LIB_API EnumResult_t SetParameter(size_t nr,void* a);											//set the argument according to type, void type is converted if possible  
  BLIB_LIB_API EnumResult_t SetParamFromString(size_t nr,std::string value);     //set variable from string, if possible           
  BLIB_LIB_API EnumResult_t SetParamsFromString(std::string value);              //set all variables from string, if possible
  BLIB_LIB_API const std::type_info* GetReturnTypeInfo(void);										//return the return type info			
	BLIB_LIB_API void* GetReturnRef();																							//return a pointer to the return value of a call, which is a pointer to the return type info
	BLIB_LIB_API virtual EnumResult_t Callback()=0;														  	//per child class implemented callback function
};

template<class returnType,class classType=Base> class Callback0:public CallbackTemp,public Base{
protected:	
	returnType returnValue;																						
  classType* classPointer;
  returnType(classType::*functionPointer)(void);
  returnType(*onlyFunctionPointer)(void);
public:
	Callback0(classType* c,returnType(classType::*f)(void)){
	  returnTypeInfo=&typeid(returnType);
		classPointer=c;
    functionPointer=f;   
    onlyFunctionPointer=NULL;
  };

  Callback0(returnType(*f)(void)){
    classPointer=NULL;
    functionPointer=NULL;
    onlyFunctionPointer=f;
  };

	virtual EnumResult_t Callback(){
		EnumResult_t result=FAIL;
		if((this->classPointer!=NULL)&&(this->functionPointer!=NULL))	
      returnValue=(*this->classPointer.*this->functionPointer)();      
		else
			returnValue=(*this->onlyFunctionPointer)();
		returnRef=(void*)((returnType*)&returnValue);		
		return SUCCESS;
	};

};

template<class classType> class Callback0<void,classType>:public CallbackTemp,public Base{
protected:	
  classType* classPointer;
  void(classType::*functionPointer)(void);
  void(*onlyFunctionPointer)(void);

public:
	Callback0(classType* c,void(classType::*f)(void)){
	  returnTypeInfo=&typeid(void);
		classPointer=c;
    functionPointer=f;   
    onlyFunctionPointer=NULL;
  };

  Callback0(void(*f)(void)){
    classPointer=NULL;
    functionPointer=NULL;
    onlyFunctionPointer=f;
  };

	virtual EnumResult_t Callback(){
		EnumResult_t result=FAIL;
		if((this->classPointer!=NULL)&&(this->functionPointer!=NULL))	
      (*this->classPointer.*this->functionPointer)();      
		else
			(*this->onlyFunctionPointer)();				
    return SUCCESS;
	};

};

template<class returnType,class classType,class arg0> class Callback1:public Callback0<returnType,classType>{
protected:
  returnType (classType::*functionPointer)(arg0);
  returnType(*onlyFunctionPointer)(arg0);
  arg0 a0;
public:
	Callback1(classType* c,returnType(classType::*f)(arg0),arg0 a0):Callback0<returnType,classType>::Callback0(c,NULL){
    this->classPointer=c;
    functionPointer=f;
    this->a0=a0;	
		this->parametersTypeInfo.push_back(&typeid(arg0));
    this->parameters.push_back((void*)(arg0*)&this->a0);
  };

  Callback1(returnType(*f)(arg0),arg0 a0):Callback0<returnType,Base>::Callback0(NULL){
    this->classPointer=NULL;
    this->functionPointer=NULL;
    this->onlyFunctionPointer=f;
    this->a0=a0;
		this->parametersTypeInfo.push_back(&typeid(arg0));
    this->parameters.push_back((void*)(arg0*)&this->a0);
  };

	virtual EnumResult_t Callback(){
		EnumResult_t result=FAIL;
		if((this->classPointer!=NULL)&&(this->functionPointer!=NULL))	
      this->returnValue=(*this->classPointer.*this->functionPointer)(a0);      
		else
			this->returnValue=(*this->onlyFunctionPointer)(a0);
		this->returnRef=(void*)((returnType*)&(this->returnValue));		
		return SUCCESS;
	};
};

template<class classType,class arg0> class Callback1<void,classType,arg0>:public Callback0<void,classType>{
protected:
  void (classType::*functionPointer)(arg0);
  void(*onlyFunctionPointer)(arg0);
  arg0 a0;
public:
	  Callback1(classType* c,void(classType::*f)(arg0),arg0 a0):Callback0<void,classType>::Callback0(c,NULL){
    this->classPointer=c;
    functionPointer=f;
    this->a0=a0;	
		this->parametersTypeInfo.push_back(&typeid(arg0));
    this->parameters.push_back((void*)(arg0*)&this->a0);
  };

  Callback1(void(*f)(arg0),arg0 a0):Callback0<void,Base>::Callback0(NULL){
    this->classPointer=NULL;
    this->functionPointer=NULL;
    this->onlyFunctionPointer=f;
    this->a0=a0;
		this->parametersTypeInfo.push_back(&typeid(arg0));
    this->parameters.push_back((void*)(arg0*)&this->a0);
  };

	virtual EnumResult_t Callback(){
		EnumResult_t result=FAIL;
		if((this->classPointer!=NULL)&&(this->functionPointer!=NULL))	
      (*this->classPointer.*this->functionPointer)(a0);      
		else
			(*this->onlyFunctionPointer)(a0);		
		return SUCCESS;
	};
};

template<class returnType,class classType,class arg0,class arg1> class Callback2:public Callback1<returnType,classType,arg0>{
protected:
  returnType (classType::*functionPointer)(arg0,arg1);
  returnType(*onlyFunctionPointer)(arg0,arg1);
  arg1 a1;
public:
	  Callback2(classType* c,returnType(classType::*f)(arg0,arg1),arg0 a0,arg1 a1):Callback1<returnType,classType,arg0>::Callback1(c,NULL,a0){
    this->classPointer=c;
    functionPointer=f;
    this->a1=a1;	
		this->parametersTypeInfo.push_back(&typeid(arg1));
    this->parameters.push_back((void*)(arg1*)&this->a1);
  };

  Callback2(returnType(*f)(arg0,arg1),arg0 a0,arg1 a1):Callback1<returnType,Base,arg0>::Callback1(NULL,a0){
    this->classPointer=NULL;
    this->functionPointer=NULL;
    this->onlyFunctionPointer=f;
    this->a1=a1;
		this->parametersTypeInfo.push_back(&typeid(arg1));
    this->parameters.push_back((void*)(arg1*)&this->a1);
  };

	virtual EnumResult_t Callback(){
		EnumResult_t result=FAIL;
		if((this->classPointer!=NULL)&&(this->functionPointer!=NULL))	
      this->returnValue=(*this->classPointer.*this->functionPointer)(this->a0,this->a1);      
		else
			this->returnValue=(*this->onlyFunctionPointer)(this->a0,this->a1);
		this->returnRef=(void*)((returnType*)&(this->returnValue));
		return SUCCESS;
	};
};

template<class classType,class arg0,class arg1> class Callback2<void,classType,arg0,arg1>:public Callback1<void,classType,arg0>{
protected:
  void (classType::*functionPointer)(arg0,arg1);
  void(*onlyFunctionPointer)(arg0,arg1);
  arg1 a1;
public:
	  Callback2(classType* c,void(classType::*f)(arg0,arg1),arg0 a0,arg1 a1):Callback1<void,classType,arg0>::Callback1(c,NULL,a0){
    this->classPointer=c;
    functionPointer=f;
    this->a1=a1;	
		this->parametersTypeInfo.push_back(&typeid(arg1));
    this->parameters.push_back((void*)(arg1*)&this->a1);
  };

  Callback2(void(*f)(arg0,arg1),arg0 a0,arg1 a1):Callback1<void,Base,arg0>::Callback1(NULL,a0){
    this->classPointer=NULL;
    this->functionPointer=NULL;
    this->onlyFunctionPointer=f;
    this->a1=a1;
		this->parametersTypeInfo.push_back(&typeid(arg1));
    this->parameters.push_back((void*)(arg1*)&this->a1);
  };

	virtual EnumResult_t Callback(){
		EnumResult_t result=FAIL;
		if((this->classPointer!=NULL)&&(this->functionPointer!=NULL))	
      (*this->classPointer.*this->functionPointer)(a1);      
		else
			(*this->onlyFunctionPointer)(a1);		
		return SUCCESS;
	};
};

template<class returnType,class classType,class arg0,class arg1,class arg2> class Callback3:public Callback2<returnType,classType,arg0,arg1>{
protected:
  returnType (classType::*functionPointer)(arg0,arg1,arg2);
  returnType(*onlyFunctionPointer)(arg0,arg1,arg2);
  arg2 a2;
public:
	  Callback3(classType* c,returnType(classType::*f)(arg0,arg1,arg2),arg0 a0,arg1 a1):Callback2<returnType,classType,arg0,arg1>::Callback2(c,NULL,a0,a1){
    this->classPointer=c;
    functionPointer=f;
    this->a2=a2;	
		this->parametersTypeInfo.push_back(&typeid(arg2));
    this->parameters.push_back((void*)(arg2*)&this->a2);
  };

  Callback3(returnType(*f)(arg0,arg1,arg2),arg0 a0,arg1 a1,arg2 a2):Callback2<returnType,Base,arg0,arg1>::Callback2(NULL,a0,a1){
    this->classPointer=NULL;
    this->functionPointer=NULL;
    this->onlyFunctionPointer=f;
    this->a2=a2;
		this->parametersTypeInfo.push_back(&typeid(arg2));
    this->parameters.push_back((void*)(arg2*)&this->a2);
  };

	virtual EnumResult_t Callback(){
		EnumResult_t result=FAIL;
		if((this->classPointer!=NULL)&&(this->functionPointer!=NULL))	
      this->returnValue=(*this->classPointer.*this->functionPointer)(this->a0,this->a1,this->a2);
		else
			this->returnValue=(*this->onlyFunctionPointer)(this->a0,this->a1,this->a2);
		this->returnRef=(void*)((returnType*)&(this->returnValue));
		return SUCCESS;
	};
};

template<class classType,class arg0,class arg1,class arg2> class Callback3<void,classType,arg0,arg1,arg2>:public Callback2<void,classType,arg0,arg1>{
protected:
  void (classType::*functionPointer)(arg0,arg1,arg2);
  void(*onlyFunctionPointer)(arg0,arg1,arg2);
  arg2 a2;
public:
	  Callback3(classType* c,void(classType::*f)(arg0,arg1,arg2),arg0 a0,arg1 a1,arg2 a2):Callback2<void,classType,arg0,arg1>::Callback2(c,NULL,a0,a1){
    this->classPointer=c;
    functionPointer=f;
    this->a2=a2;	
		this->parametersTypeInfo.push_back(&typeid(arg2));
    this->parameters.push_back((void*)(arg2*)&this->a2);
  };

  Callback3(void(*f)(arg0,arg1,arg2),arg0 a0,arg1 a1,arg2 a2):Callback2<void,Base,arg0,arg1>::Callback2(NULL,a0,a1){
    this->classPointer=NULL;
    this->functionPointer=NULL;
    this->onlyFunctionPointer=f;
    this->a2=a2;
		this->parametersTypeInfo.push_back(&typeid(arg2));
    this->parameters.push_back((void*)(arg2*)&this->a2);
  };

	virtual EnumResult_t Callback(){
		EnumResult_t result=FAIL;
		if((this->classPointer!=NULL)&&(this->functionPointer!=NULL))	
      (*this->classPointer.*this->functionPointer)(a2);      
		else
			(*this->onlyFunctionPointer)(a2);		
		return SUCCESS;
	};
};

template<class returnType,class classType,class arg0,class arg1,class arg2,class arg3> class Callback4:public Callback3<returnType,classType,arg0,arg1,arg2>{
protected:
  returnType (classType::*functionPointer)(arg0,arg1,arg2,arg3);
  returnType(*onlyFunctionPointer)(arg0,arg1,arg2,arg3);
  arg3 a3;
public:
	Callback4(classType* c,returnType(classType::*f)(arg0,arg1,arg2,arg3),arg0 a0,arg1 a1,arg2 a2):Callback3<returnType,classType,arg0,arg1,arg2>::Callback2(c,NULL,a0,a1,a2){
    this->classPointer=c;
    functionPointer=f;
    this->a3=a3;	
		this->parametersTypeInfo.push_back(&typeid(arg2));
    this->parameters.push_back((void*)(arg3*)&this->a3);
  };

  Callback4(returnType(*f)(arg0,arg1,arg2,arg3),arg0 a0,arg1 a1,arg2 a2,arg3 a3):Callback3<returnType,Base,arg0,arg1,arg2>::Callback3(NULL,a0,a1,a2){
    this->classPointer=NULL;
    this->functionPointer=NULL;
    this->onlyFunctionPointer=f;
    this->a3=a3;
		this->parametersTypeInfo.push_back(&typeid(arg3));
    this->parameters.push_back((void*)(arg3*)&this->a3);
  };

	virtual EnumResult_t Callback(){
		EnumResult_t result=FAIL;
		if((this->classPointer!=NULL)&&(this->functionPointer!=NULL))	
      this->returnValue=(*this->classPointer.*this->functionPointer)(this->a0,this->a1,this->a2,this->a3);
		else
			this->returnValue=(*this->onlyFunctionPointer)(this->a0,this->a1,this->a2,this->a3);
		this->returnRef=(void*)((returnType*)&(this->returnValue));		
		return SUCCESS;
	};
};

template<class classType,class arg0,class arg1,class arg2,class arg3> class Callback4<void,classType,arg0,arg1,arg2,arg3>:public Callback3<void,classType,arg0,arg1,arg2>{
protected:
  void (classType::*functionPointer)(arg0,arg1,arg2,arg3);
  void(*onlyFunctionPointer)(arg0,arg1,arg2,arg3);
  arg3 a3;
public:
	  Callback4(classType* c,void(classType::*f)(arg0,arg1,arg2,arg3),arg0 a0,arg1 a1,arg2 a2,arg3 a3):Callback3<void,classType,arg0,arg1,arg2>::Callback3(c,NULL,a0,a1,a2){
    this->classPointer=c;
    functionPointer=f;
    this->a3=a3;	
		this->parametersTypeInfo.push_back(&typeid(arg3));
    this->parameters.push_back((void*)(arg3*)&this->a3);
  };

  Callback4(void(*f)(arg0,arg1,arg2,arg3),arg0 a0,arg1 a1,arg2 a2,arg3 a3):Callback3<void,Base,arg0,arg1,arg2>::Callback3(NULL,a0,a1,a2){
    this->classPointer=NULL;
    this->functionPointer=NULL;
    this->onlyFunctionPointer=f;
    this->a3=a3;
		this->parametersTypeInfo.push_back(&typeid(arg3));
    this->parameters.push_back((void*)(arg3*)&this->a3);
  };

	virtual EnumResult_t Callback(){
		EnumResult_t result=FAIL;
		if((this->classPointer!=NULL)&&(this->functionPointer!=NULL))	
      (*this->classPointer.*this->functionPointer)(a3);      
		else
			(*this->onlyFunctionPointer)(a3);		
		return SUCCESS;
	};
};

};

#endif
