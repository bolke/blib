#ifndef BLIB_THREADWORKERPOOL_H
#define BLIB_THREADWORKERPOOL_H

#include "Basis.h"
#include "Thread.h"
#include "ThreadSafe.h"
#include "ThreadTask.h"
#include "ThreadTaskPool.h"
#include "ThreadWorker.h"

namespace blib{

class ThreadWorkerPool:public Base,public Thread{
protected:
	size_t workforceSize;
	std::vector<ThreadWorker*> workers;
	std::vector<ThreadTaskPool*> workerPools;
	std::vector<Thread*> threads;
	ThreadTaskPool taskPool;
	BLIB_LIB_API EnumResult_t AddWorker();
	BLIB_LIB_API EnumResult_t PopWorker();
	BLIB_LIB_API void Run(void);
public:
  BLIB_LIB_API ThreadWorkerPool();
	BLIB_LIB_API ~ThreadWorkerPool();
	BLIB_LIB_API EnumResult_t AddTask(ThreadTask* task);		
	BLIB_LIB_API ThreadTask* PopCompletedTask();
	BLIB_LIB_API EnumResult_t SetWorkforceSize(size_t size);		
};

};

#endif
