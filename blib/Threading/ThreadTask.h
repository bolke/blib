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
	ThreadTask(CallbackTemp* task=NULL,uint32_t execLimit=0);
	bool IsCompleted();
	~ThreadTask();
};

};

#endif
