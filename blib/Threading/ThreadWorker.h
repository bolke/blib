#ifndef BLIB_THREADWORKER_H
#define BLIB_THREADWORKER_H

#include "Basis.h"
#include "Thread.h"
#include "ThreadSafe.h"
#include "ThreadTask.h"
#include "ThreadTaskPool.h"

namespace blib{

class ThreadWorker:public Base,public ThreadSafe{
protected:
	bool destroyPool;
	bool workParallel;												//execute one task after another, in a loop
	ThreadTask* task;													//current task to execute
	Thread* thread;														//thread used to execute tasks with
	ThreadTaskPool* taskPool;									//our task pool, might be shared with others
	BLIB_LIB_API void Run(void);														//function cast into a callback, used when thread is set
public:
	BLIB_LIB_API ThreadWorker(ThreadTaskPool* taskPool=new ThreadTaskPool,bool destroyPool=true);
	BLIB_LIB_API ~ThreadWorker();															//cleans the task
	BLIB_LIB_API EnumResult_t SetThread(Thread* thread=NULL);	//sets thread and sets run function into run callback, if thread==NULL, create new
	BLIB_LIB_API Thread* GetThread();													//returns internal thread, or NULL
	BLIB_LIB_API bool GetWorkParallel();												//return if workers works each task once then next or finish one.
	BLIB_LIB_API EnumResult_t SetWorkParallel(bool value);			//tasks will be executed one call at a time 
	BLIB_LIB_API ThreadTaskPool* GetTaskPool();								//taskpool sharing
	BLIB_LIB_API EnumResult_t SetTaskPool(ThreadTaskPool* taskPool);
	BLIB_LIB_API EnumResult_t AddTask(ThreadTask* task);				//add a task to the pool
};

};

#endif
