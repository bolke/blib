#ifndef BLIB_THREADTASK_H
#define BLIB_THREADTASK_H

#include "Basis.h"
#include "ThreadItem.h"
#include "ThreadLock.h"

namespace blib{

class ThreadTask:public Base{
public:
	uint32_t execCnt;
	uint32_t execLimit;
	CallbackTemp* task;
	BLIB_LIB_API ThreadTask(CallbackTemp* task=NULL,uint32_t execLimit=0);
	BLIB_LIB_API bool IsCompleted();
	BLIB_LIB_API ~ThreadTask();
};

};

#endif
