#ifndef BREWPROGRAM_H
#define BREWPROGRAM_H

#include "typedef.h"

#define MAX_NR_OF_SENSORS 8
#define MAX_NR_OF_OUTPUT	8
#define MAX_NR_OF_PROGRAM_STEPS 32

#define MAGIC_BREW_BYTE0	0xAA
#define MAGIC_BREW_BYTE1  (~MAGIC_BREW_BYTE0)

#define ACTION_INVALID		0
#define ACTION_COOLING		1
#define ACTION_HEATING		2
#define ACTION_SAFETY			4
#define ACTION_SAVE_COOLING (ACTION_COOLING|ACTION_SAFETY)
#define ACTION_SAVE_HEATING (ACTION_HEATING|ACTION_SAFETY)

#define SENSOR_UNKNOWN    0
#define SENSOR_SERIALIZE	10

#define PROGRAMSTEP_INVALID   0
#define PROGRAMSTEP_SERIALIZE 9

typedef union sensor_u{	
	struct{
		uint8_t sensorId;
		union{
			uint8_t serialArray[8];
			uint64_t serialNumber;
		};
	};
	uint8_t serialize[SENSOR_SERIALIZE];
}sensor_t;

typedef union programStep_u{
	struct{		
		uint8_t programId;
		uint8_t outputId;  
		uint8_t action;
		union{
			uint8_t thresholdArray[4];
			float threshold;
		};
		union{
			uint8_t durationArray[2];
			uint16_t duration;
		};
		sensor_t* sensorId;	
		union programStep_u* nextStep;
	};
	uint8_t serialize[PROGRAMSTEP_SERIALIZE];
}programStep_t;

#endif
