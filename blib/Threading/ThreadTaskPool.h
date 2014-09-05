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
	ThreadTaskPool();
	ThreadTask* Pop();
	ThreadTask* PopCompleted();
	EnumResult_t Push(ThreadTask* task);
};

};

#endif
