#include "PidData.h"

using namespace blib;

PidData::PidData(ThreadItem& item,bool destroyLockpad):ThreadSafe(item,destroyLockpad){
	Init(0);
	Clear();
};

PidData::PidData(ThreadLock& lock):ThreadSafe(lock){
	Init(0);
	Clear();
};

PidData::~PidData(){
};

size_t PidData::Size(){
	return sizeof(float32_t);
};

size_t PidData::Pop(char_t& c,size_t size){
	size_t result=0;
	if(size>=Size()){
	  result=Size();
	}
	return result;
};

size_t PidData::Pop(std::string& data);{
	return Data::Pop(data);
};

size_t PidData::Push(const char_t &c,size_t size){
	size_t result=0;
	if(size>=sizeof(float32_t)){
	}
	return result;
};

size_t PidData::Push(const std::string& data){
  return Data::Push(data);
};

EnumResult_t PidData::Init(float32_t target,float32_t pGain,float32_t iGain,float32_t dGain,float32_t interval,float32_t minOutput,float32_t maxOutput,bool useMinMax){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(SetTarget(target)==SUCCESS)
			if(SetPGain(pGain)==SUCCESS)
				if(SetIGain(iGain)==SUCCESS)
					if(SetDGain(dGain)==SUCCESS)
						if(SetInterval(interval)==SUCCESS)
							if(SetMinOutput(minOutput)==SUCCESS)
								if(SetMaxOutput(maxOutput)==SUCCESS)
									if(SetUseMinMax(useMinMax)==SUCCESS)
										result=SUCCESS;
		lock->Unlock();
	}
	return result;
};

EnumResult_t PidData::SetTarget(const float32_t value){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->target=value;		
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
};

EnumResult_t PidData::SetPGain(const float32_t value){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->target=value;		
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
};

EnumResult_t PidData::SetIGain(const float32_t value){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->target=value;		
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
};

EnumResult_t PidData::SetDGain(const float32_t value){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->target=value;		
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
};

EnumResult_t PidData::SetITerm(const float32_t value){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->target=value;		
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
};

EnumResult_t PidData::SetInterval(const float32_t value){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->target=value;		
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
};

EnumResult_t PidData::SetMinOutput(const float32_t value){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->target=value;		
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
};

EnumResult_t PidData::SetMaxOutput(const float32_t value){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->target=value;		
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
};

EnumResult_t PidData::SetUseMinMax(const bool value){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->target=value;		
		result=SUCCESS;
		lock->Unlock();
	}
	return result;
};

float32_t PidData::GetTarget(){
};

float32_t PidData::GetPGain(){
};

float32_t PidData::GetIGain(){
};

float32_t PidData::GetDGain(){
};

float32_t PidData::GetITerm(){
};

float32_t PidData::GetInterval(){
};

float32_t PidData::GetMinOutput(){
};

float32_t PidData::GetMaxOutput(){
};

bool PidData::GetUseMinMax(){
};

EnumResult_t PidData::Reset(){
};

EnumResult_t PidData::Clear(){
};

float PidData::Compute(float32_t input){
};
