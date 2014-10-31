#ifndef BLIB_THREADTASKPOOL_H
#define BLIB_THREADTASKPOOL_H

#include "Basis.h"
#include "ThreadTask.h"
#include "ThreadSafe.h"

namespace blib{

class ThreadTaskPool:public ThreadSafe,public Base{
protected:
	std::vector<ThreadTask*> tasks;
	std::vector<ThreadTask*> completedTasks;
public:
	BLIB_LIB_API ThreadTaskPool();
	BLIB_LIB_API ThreadTask* Pop();
	BLIB_LIB_API ThreadTask* PopCompleted();
	BLIB_LIB_API EnumResult_t Push(ThreadTask* task);
};

};

#endif
