#ifndef PIDOBJECT_H
#define PIDOBJECT_H

#include "blib.h"

using namespace blib;

typedef union{
	struct{
		union{
			struct{
				float32_t targetF;
				float32_t pGainF;
				float32_t iGainF;
				float32_t dGainF;
				float32_t iTermF;
				float32_t lastInputF;
				float32_t intervalF;
				float32_t minOutputF;
				float32_t maxOutputF;
			};
			struct{
				int32_t targetI;
				int32_t pGainI;
				int32_t iGainI;
				int32_t dGainI;
				int32_t iTermI;
				int32_t lastInputI;
				int32_t intervalI;
				int32_t minOutputI;
				int32_t maxOutputI;			
			};
		};
		bool useMinMax;  
		bool useFloat;
	};
	char_t serialized[38];
} PidObject_t;

void PidReset(PidObject_t& pidObject);
void PidClear(PidObject_t& pidObject,const bool useFloat=false);

void PidInitF(PidObject_t& pidObject,float32_t target,float32_t pGain=0.2f,float32_t iGain=0.2f,float32_t dGain=0.2f,float32_t interval=1.0f,float32_t minOutput=0.0f,float32_t maxOutput=0.0f);
float32_t PidSetPGainF(PidObject_t &pidObject,float32_t pGain);
float32_t PidSetIGainF(PidObject_t &pidObject,float32_t iGain);
float32_t PidSetDGainF(PidObject_t &pidObject,float32_t dGain);
float32_t PidSetIntervalF(PidObject_t &pidObject,float32_t interval);
float32_t PidSetTargetF(PidObject_t &pidObject,float32_t target);
bool PidSetMinMaxF(PidObject_t &pidObject,float32_t minOutput,float32_t maxOutput);
float32_t PidComputeF(PidObject_t &pidObject,float32_t input);

void PidInitI(PidObject_t& pidObject,int32_t target,int32_t pGain=20,int32_t iGain=20,int32_t dGain=20,int32_t interval=1,int32_t minOutput=0,int32_t maxOutput=0);
int32_t PidSetPGainI(PidObject_t &pidObject,int32_t pGain);
int32_t PidSetIGainI(PidObject_t &pidObject,int32_t iGain);
int32_t PidSetDGainI(PidObject_t &pidObject,int32_t dGain);
int32_t PidSetIntervalI(PidObject_t &pidObject,int32_t interval);
int32_t PidSetTargetI(PidObject_t &pidObject,int32_t target);
bool PidSetMinMaxI(PidObject_t &pidObject,int32_t minOutput,int32_t maxOutput);
int32_t PidComputeI(PidObject_t &pidObject,int32_t input);

#endif
