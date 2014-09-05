#include "ThreadTaskPool.h"

using namespace blib;

ThreadTaskPool::ThreadTaskPool(){
}

ThreadTask* ThreadTaskPool::Pop(){
	ThreadTask* result=NULL;	
	if(lock->Lock()){
		if(tasks.size()>0){
			result=tasks.front();
			tasks.erase(tasks.begin());
		}
		lock->Unlock();
	}	
	return result;
}

ThreadTask* ThreadTaskPool::PopCompleted(){
	ThreadTask* result=NULL;
	if(lock->Lock()){
		if(completedTasks.size()>0){
			result=completedTasks.front();
			completedTasks.erase(completedTasks.begin());
		}
		lock->Unlock();
	}
	return result;
}

EnumResult_t ThreadTaskPool::Push(ThreadTask* task){
  EnumResult_t result=FAIL;
	if(task!=NULL){
		if(lock->Lock()){
			if(task->IsCompleted())
				completedTasks.push_back(task);
			else
				tasks.push_back(task);
			result=SUCCESS;
			lock->Unlock();
		}
	}
	return result;
}