#include "ThreadWorkerPool.h"

using namespace blib;

ThreadWorkerPool::ThreadWorkerPool(){
	workforceSize=1;	
};

ThreadWorkerPool::~ThreadWorkerPool(){
};

void ThreadWorkerPool::Run(void){
};

EnumResult_t ThreadWorkerPool::AddTask(ThreadTask* task){
  EnumResult_t result=FAIL;
	return result;
};

ThreadTask* ThreadWorkerPool::PopCompletedTask(){
  ThreadTask* result=NULL;
	return result;
};

EnumResult_t ThreadWorkerPool::SetWorkforceSize(size_t size){
  EnumResult_t result=FAIL;
	return result;
};
