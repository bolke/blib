#include "PidObject.h"

using namespace blib;

void PidInitF(PidObject_t &pidObject,float32_t target,float32_t pGain,float32_t iGain,float32_t dGain,float32_t interval,float32_t minOutput,float32_t maxOutput){
	pidObject.targetF=target;
	pidObject.pGainF=pGain;
	pidObject.iGainF=iGain;
	pidObject.dGainF=dGain;
	pidObject.intervalF=interval;
	pidObject.minOutputF=minOutput;
	pidObject.maxOutputF=maxOutput;
	pidObject.iTermF=0.0f;
	pidObject.lastInputF=0.0f;
};

void PidInitI(PidObject_t &pidObject,int32_t target,int32_t pGain,int32_t iGain,int32_t dGain,int32_t interval,int32_t minOutput,int32_t maxOutput){
	pidObject.targetI=target*1000;
	pidObject.pGainI=pGain;
	pidObject.iGainI=iGain;
	pidObject.dGainI=dGain;
	pidObject.intervalI=interval;
	pidObject.minOutputI=minOutput;
	pidObject.maxOutputI=maxOutput;
	pidObject.iTermI=0;
	pidObject.lastInputI=0;
};

void PidReset(PidObject_t &pidObject){
	if(pidObject.useFloat){
		pidObject.lastInputF=0.0f;
		pidObject.iTermF=0.0f;
	}else{
		pidObject.lastInputI=0;
		pidObject.iTermI=0;
	}
}

void PidClear(PidObject_t &pidObject,const bool useFloat){
	pidObject.useFloat=useFloat;
	pidObject.useMinMax=false;
	if(useFloat)
		PidInitF(pidObject,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
	else	
		PidInitI(pidObject,0,0,0,0,0,0,0);
};

float32_t PidSetPGainF(PidObject_t &pidObject,float32_t pGain){
	pidObject.pGainF=pGain;
	return pidObject.pGainF;
}

float32_t PidSetIGainF(PidObject_t &pidObject,float32_t iGain){
	if(pidObject.intervalF>0.0f)
	  pidObject.iGainF=iGain*(1.0f/pidObject.intervalF);
	else
	  pidObject.iGainF=iGain;
  return pidObject.iGainF;
}

float32_t PidSetDGainF(PidObject_t &pidObject,float32_t dGain){
	if(pidObject.intervalF>0.0f)
	  pidObject.dGainF=dGain/(1.0f/pidObject.intervalF);
	else
	  pidObject.dGainF=dGain;
  return pidObject.dGainF;
}

float32_t PidSetIntervalF(PidObject_t &pidObject,float32_t interval){
	float oldInterval=pidObject.intervalF;
  pidObject.intervalF=interval;
	if(oldInterval==0.0f){
		PidSetIGainF(pidObject,pidObject.iGainF);
		PidSetDGainF(pidObject,pidObject.dGainF);
	}else{
    PidSetIGainF(pidObject,pidObject.iGainF/(1.0f/pidObject.intervalF));
		PidSetDGainF(pidObject,pidObject.dGainF*(1.0f/pidObject.intervalF));
	}
	return pidObject.intervalF;
}

float32_t PidSetTargetF(PidObject_t &pidObject,float32_t target){
  pidObject.targetF=target;
	return pidObject.targetF;
}

bool PidSetMinMaxF(PidObject_t &pidObject,float32_t minOutput,float32_t maxOutput){
	pidObject.minOutputF=minOutput;
	pidObject.maxOutputF=maxOutput;
	pidObject.useMinMax=(pidObject.minOutputF<pidObject.maxOutputF);
	return pidObject.useMinMax;
}

float32_t PidComputeF(PidObject_t &pidObject,float32_t input){
	float error=pidObject.targetF-input;
	pidObject.iTermF=pidObject.iTermF+(pidObject.iGainF*error);
	if(pidObject.useMinMax){
	  if(pidObject.iTermF<pidObject.minOutputF)
		  pidObject.iTermF=pidObject.minOutputF;
		else if(pidObject.iTermF>pidObject.maxOutputF)
		 pidObject.iTermF=pidObject.maxOutputF;
	}
	float output=(pidObject.pGainF*error)+pidObject.iTermF-(pidObject.dGainF*(input-pidObject.lastInputF));
	if(pidObject.useMinMax){
		if(output<pidObject.minOutputF)
			output=pidObject.minOutputF;
		else if(output>pidObject.maxOutputF)
			output=pidObject.maxOutputF;
	}
	pidObject.lastInputF=input;
	return output; 
}

int32_t PidSetPGainI(PidObject_t &pidObject,int32_t pGain){
	pidObject.pGainI=pGain;
	return pidObject.pGainI;
}

int32_t PidSetIGainI(PidObject_t &pidObject,int32_t iGain){
	if(pidObject.intervalI>0)
	  pidObject.iGainI=iGain*(1000/pidObject.intervalI); //!todo goto integer
	else
	  pidObject.iGainI=iGain;
  return pidObject.iGainI;
};

int32_t PidSetDGainI(PidObject_t &pidObject,int32_t dGain){
	if(pidObject.intervalI>0)
	  pidObject.dGainI=dGain/(1000/pidObject.intervalI); //!todo goto integer
	else
	  pidObject.dGainI=dGain;
  return pidObject.dGainI;
};

int32_t PidSetIntervalI(PidObject_t &pidObject,int32_t interval){
	int32_t oldInterval=pidObject.intervalI;
  pidObject.intervalI=interval;
	if(oldInterval==0){
		PidSetIGainI(pidObject,pidObject.iGainI);
		PidSetDGainI(pidObject,pidObject.dGainI);
	}else{
    PidSetIGainI(pidObject,pidObject.iGainI/(1.0f/pidObject.intervalI)); //!todo make it integer
		PidSetDGainI(pidObject,pidObject.dGainI*(1.0f/pidObject.intervalI)); //!todo make it integer
	}
	return pidObject.intervalI;
};

int32_t PidSetTargetI(PidObject_t &pidObject,int32_t target){
	pidObject.targetI=target*1000;
	return target;
};

bool PidSetMinMaxI(PidObject_t &pidObject,int32_t minOutput,int32_t maxOutput){
	pidObject.minOutputI=minOutput;
	pidObject.maxOutputI=maxOutput;
	pidObject.useMinMax=(pidObject.minOutputI<pidObject.maxOutputI);
	return pidObject.useMinMax;
};

int32_t PidComputeI(PidObject_t &pidObject,int32_t input){
	input=input*1000;
	int32_t error=pidObject.targetI-input;
	pidObject.iTermI=pidObject.iTermI+(pidObject.iGainI*error);
	if(pidObject.useMinMax){
	  if(pidObject.iTermI<pidObject.minOutputI)
		  pidObject.iTermI=pidObject.minOutputI;
		else if(pidObject.iTermI>pidObject.maxOutputI)
		 pidObject.iTermI=pidObject.maxOutputI;
	}
	int32_t output=((pidObject.pGainI*error)+pidObject.iTermI-(pidObject.dGainI*(input-pidObject.lastInputI)))/100;
	if(pidObject.useMinMax){
		if(output<pidObject.minOutputI)
			output=pidObject.minOutputI;
		else if(output>pidObject.maxOutputI)
			output=pidObject.maxOutputI;
	}
	pidObject.lastInputI=input;
	return output/1000; 
};
