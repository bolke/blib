#ifndef BLIB_PIDDATA_H
#define BLIB_PIDDATA_H

#include "Blib.h"

using namespace blib;

#define PID_DEFAULT_PGAIN 0.2f
#define PID_DEFAULT_IGAIN 0.2f
#define PID_DEFAULT_DGAIN 0.2f

class PidData:public Data,public ThreadSafe{
protected:
	float32_t target;
	float32_t pGain;
	float32_t iGain;
	float32_t dGain;
	float32_t iTerm;
	float32_t lastInput;
	float32_t interval;
	float32_t minOutput;
	float32_t maxOutput;
	bool useMinMax;  
public:
  PidData(ThreadItem& item,bool destroyLockpad=false);       
  PidData(ThreadLock& lock=*(new ThreadLock(false)));        
  ~PidData();

	virtual size_t Size();
  virtual size_t Pop(char_t& c,size_t size=1);
  virtual size_t Pop(std::string& data);
  virtual size_t Push(const char_t &c,size_t size=1);
  virtual size_t Push(const std::string& data);
	
	EnumResult_t Init(float32_t target,float32_t pGain=PID_DEFAULT_PGAIN,float32_t iGain=PID_DEFAULT_IGAIN,float32_t dGain=PID_DEFAULT_DGAIN,float32_t interval=1.0f,float32_t minOutput=0.0f,float32_t maxOutput=0.1f,bool useMinMax=false);
	
	EnumResult_t SetTarget(const float32_t value);
	EnumResult_t SetPGain(const float32_t value);
	EnumResult_t SetIGain(const float32_t value);
	EnumResult_t SetDGain(const float32_t value);
	EnumResult_t SetITerm(const float32_t value);
	EnumResult_t SetInterval(const float32_t value);
	EnumResult_t SetMinOutput(const float32_t value);
	EnumResult_t SetMaxOutput(const float32_t value);
	EnumResult_t SetUseMinMax(const bool value);
	
	float32_t GetTarget();
	float32_t GetPGain();
	float32_t GetIGain();
	float32_t GetDGain();
	float32_t GetITerm();
	float32_t GetInterval();
	float32_t GetMinOutput();
	float32_t GetMaxOutput();
	bool GetUseMinMax();
	
	EnumResult_t Reset();
	EnumResult_t Clear();
	
	virtual float Compute(float32_t input);
};

#endif
