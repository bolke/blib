#ifdef _DEBUG
#include "AvrSim.h"
#endif

#include "BrewProgram.h"

sensor_t sensors[MAX_NR_OF_SENSORS];
programStep_t programSteps[MAX_NR_OF_PROGRAM_STEPS];

uint8_t sensorCnt=0;
uint8_t outputCnt=0;
uint8_t programStepCnt=0;

bool inControlLoop=false;

programStep_t* NewProgram();
programStep_t* NewProgramStep(programStep_t* previous);
bool DeleteProgram(uint8_t id);
bool DeleteProgramStep(programStep_t* value);
void InitProgramStep(programStep_t* programStep);
uint8_t CountPrograms();
uint8_t CountSensors();

sensor_t* NewSensor();
bool DeleteSensor(sensor_t* value);
void InitSensor(sensor_t* sensor);
bool IsSensorUsed(sensor_t* value);

void LoadFromEeprom();
void SaveToEeprom();

void DoControlLoop();
void UpdateOutput();

programStep_t* NewProgram(){	
	uint8_t newProgramId=1;
	programStep_t* result=NULL;
	if(programStepCnt<MAX_NR_OF_PROGRAM_STEPS){
		for(uint8_t i=0;i<MAX_NR_OF_PROGRAM_STEPS;i++){
			if(programSteps[i].programId==newProgramId)
				newProgramId++;
			if(programSteps[i].programId==PROGRAMSTEP_INVALID){
				result=&(programSteps[i]);
				break;
			}
		}
	}	
	if(result!=NULL)
		result->programId=newProgramId;
	return result;
}

programStep_t* NewProgramStep(programStep_t* previous){
  programStep_t* result=NULL;	
	if(previous!=NULL){
	  result=NewProgram();
		if(result!=NULL){
			result->programId=previous->programId;
			previous->nextStep=result;
		}
	}
	return result;
}

bool DeleteProgram(uint8_t id){
	bool result=false;
	if(id!=PROGRAMSTEP_INVALID){
		for(uint8_t i=0;i<MAX_NR_OF_PROGRAM_STEPS;i++){
			if(programSteps[i].programId==id){
				result=true;
				InitProgramStep(&(programSteps[i]));
			}
		}
	}
	return result;
}

bool DeleteProgramStep(programStep_t* value){
	bool result=false;
	if(value!=NULL){
		if(value->nextStep!=NULL)
			DeleteProgramStep(value->nextStep);
		for(uint8_t i=0;i<MAX_NR_OF_PROGRAM_STEPS;i++){
			if(&(programSteps[i])==value){
				result=true;
				InitProgramStep(&(programSteps[i]));
				break;
			}
		}
	}
	return result;
}

sensor_t* NewSensor(){
	uint8_t sensorId=1;
  sensor_t* result=NULL;
	for(uint8_t i=0;i<MAX_NR_OF_SENSORS;i++){
		if(sensors[i].sensorId==sensorId)
			sensorId++;
		if(sensors[i].sensorId==SENSOR_UNKNOWN){
			result=&(sensors[i]);
			break;
		}
	}
	return result;
}

bool DeleteSensor(sensor_t* value){
  bool result=false;
	if(value!=NULL){
		for(uint8_t i=0;i<MAX_NR_OF_SENSORS;i++){
			if(&(sensors[i])==value){
				for(uint8_t j=0;j<MAX_NR_OF_PROGRAM_STEPS;j++){
					if(programSteps[i].sensorId==value)
						DeleteProgramStep(&programSteps[i]);
				}
			  InitSensor(value);
				result=SUCCESS;
				break;
			}
		}
	}
	return result;
}

bool IsSensorUsed(sensor_t* value){
  bool result=false;
	if(value!=NULL){
	  for(uint8_t i=0;i<MAX_NR_OF_PROGRAM_STEPS;i++){
			if(programSteps[i].sensorId==value)
				result=true;
		}
	}
	return result;
}

void InitSensor(sensor_t* sensor){
	if(sensor!=NULL){
		sensor->sensorId=0;
		sensor->serialNumber=SENSOR_UNKNOWN;
	}
};

uint8_t CountSensors(){
	uint8_t result=0;
	for(uint8_t i=0;i<MAX_NR_OF_SENSORS;i++){
		if(sensors[i].sensorId!=SENSOR_UNKNOWN)
			result++;
	}
	return result;
}

uint8_t CountPrograms(){
  uint8_t result=0;
	for(uint8_t i=1;i<=MAX_NR_OF_PROGRAM_STEPS;i++){							
		for(uint8_t j=0;j<MAX_NR_OF_PROGRAM_STEPS;j++){
			if(programSteps[j].programId==i){
				result++;
				break;
			}
		}
	}
	return result;
}

void InitProgramStep(programStep_t* programStep){
	if(programStep!=NULL){
		programStep->programId=PROGRAMSTEP_INVALID;
	  programStep->outputId=0;
		programStep->action=ACTION_INVALID;
		programStep->threshold=0.0f;
		programStep->duration=0;
		programStep->sensorId=NULL;
		programStep->nextStep=NULL;
	}
}

void LoadFromEeprom(){
	uint8_t i=0;
	uint16_t address=0;
	if(GetEepromByte(0)==MAGIC_BREW_BYTE0){
    if(GetEepromByte(1)==MAGIC_BREW_BYTE1){
			sensorCnt=GetEepromByte(2);
			outputCnt=GetEepromByte(3);
			programStepCnt=GetEepromByte(4);			
			address=5;
			for(i=0;i<sensorCnt;i++){
				ReadEepromBytes(address,sensors[i].serialize,SENSOR_SERIALIZE);			
				address=address+SENSOR_SERIALIZE;
			}
			for(i=0;i<outputCnt;i++){
			}
			for(i=0;i<programStepCnt;i++){
				ReadEepromBytes(address,programSteps[i].serialize,PROGRAMSTEP_SERIALIZE);
				address=address+PROGRAMSTEP_SERIALIZE;
			}
		}
	}
}

void SaveToEeprom(){
	uint8_t i=0;
	uint8_t emptySensor[SENSOR_SERIALIZE]={0};
	uint8_t emptyProgramStep[PROGRAMSTEP_SERIALIZE]={0};
	uint16_t address=0;
	WriteEepromByte(0,MAGIC_BREW_BYTE0);
	WriteEepromByte(1,MAGIC_BREW_BYTE1);
	WriteEepromByte(2,sensorCnt);
	WriteEepromByte(3,outputCnt);
	WriteEepromByte(4,programStepCnt);
  address=5;
	for(i=0;i<MAX_NR_OF_SENSORS;i++){
		if(i<sensorCnt)
		  WriteEepromBytes(address,sensors[i].serialize,SENSOR_SERIALIZE);			
		else
			WriteEepromBytes(address,emptySensor,SENSOR_SERIALIZE);
		address=address+SENSOR_SERIALIZE;
	}			
	for(i=0;i<programStepCnt;i++){
		if(i<programStepCnt)
		  WriteEepromBytes(address,programSteps[i].serialize,PROGRAMSTEP_SERIALIZE);
		else
			WriteEepromBytes(address,emptyProgramStep,PROGRAMSTEP_SERIALIZE);
		address=address+PROGRAMSTEP_SERIALIZE;
	}	
}

void Setup(){
	uint8_t i=0;
	for(i=0;i<MAX_NR_OF_SENSORS;i++)
		InitSensor(&sensors[i]);
	for(i=0;i<MAX_NR_OF_PROGRAM_STEPS;i++)
		InitProgramStep(&programSteps[i]);
	LoadFromEeprom();	
	inControlLoop=false;
}

void DoControlLoop(){

}

void UpdateOutput(){	
	printf("programs: %i\r\n",CountPrograms());
	printf("sensors: %i\r\n",CountSensors());	
}

void Loop(){
	if(inControlLoop)		
		DoControlLoop();	
	UpdateOutput();
}
