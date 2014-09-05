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
	void Run(void);														//function cast into a callback, used when thread is set
public:
	ThreadWorker(ThreadTaskPool* taskPool=new ThreadTaskPool,bool destroyPool=true);
	~ThreadWorker();															//cleans the task
	EnumResult_t SetThread(Thread* thread=NULL);	//sets thread and sets run function into run callback, if thread==NULL, create new
	Thread* GetThread();													//returns internal thread, or NULL
	bool GetWorkParallel();												//return if workers works each task once then next or finish one.
	EnumResult_t SetWorkParallel(bool value);			//tasks will be executed one call at a time 
	ThreadTaskPool* GetTaskPool();								//taskpool sharing
	EnumResult_t SetTaskPool(ThreadTaskPool* taskPool);
	EnumResult_t AddTask(ThreadTask* task);				//add a task to the pool
};

};

#endif
