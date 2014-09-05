#include "ThreadWorker.h"

using namespace blib;

ThreadWorker::ThreadWorker(ThreadTaskPool* taskPool){
	this->taskPool=taskPool;
  workParallel=false;
	thread=NULL;
	task=NULL;
}

ThreadWorker::~ThreadWorker(){
	CallbackTemp* callback=NULL;
	if(thread!=NULL){				
		callback=thread->GetRunCallback();
		thread->SetRunCallback(NULL);
		if(callback!=NULL)
			delete callback;
	}
	if(taskPool!=NULL)
		delete taskPool;
}

EnumResult_t ThreadWorker::SetThread(Thread* thread){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(thread!=NULL){
			this->thread=thread;
			thread->SetRunCallback(new Callback0<void,ThreadWorker>(this,&ThreadWorker::Run));
			result=SUCCESS;
		}else if(this->thread!=NULL){
			CallbackTemp* callback=this->thread->GetRunCallback();
			this->thread->SetRunCallback(NULL);
			if(callback!=NULL)
				delete callback;
		}
		lock->Unlock();
	}
	return result;
}

Thread* ThreadWorker::GetThread(){
	return thread;
}

void ThreadWorker::Run(){
	if(lock->Lock()){
		if(taskPool!=NULL){
			if(task!=NULL){
				if((task->IsCompleted())||(workParallel)){
					taskPool->Push(task);
					task=NULL;
				}
			}
			if(task==NULL)
				task=taskPool->Pop();				
		}			  
		lock->Unlock();
	}	
	if(task!=NULL){
		task->task->Callback();
		task->execCnt++;
	}
}

bool ThreadWorker::GetWorkParallel(){
	return workParallel;
}

EnumResult_t ThreadWorker::SetWorkParallel(bool value){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
	  this->workParallel=value;
	  result=SUCCESS;
		lock->Unlock();
	}
	return result;
}

EnumResult_t ThreadWorker::SetTaskPool(ThreadTaskPool* taskPool){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->taskPool=taskPool;
		result=SUCCESS;
	}
	return result;
}

ThreadTaskPool* ThreadWorker::GetTaskPool(){
  ThreadTaskPool* result=NULL;
	if(lock->Lock()){
		result=taskPool;
		lock->Unlock();
	}
	return result;
}

EnumResult_t ThreadWorker::AddTask(ThreadTask* task){
  EnumResult_t result=FAIL;
	if(task!=NULL){		
	  if(lock->Lock()){				
			if(taskPool!=NULL){
				result=taskPool->Push(task);
			}
			lock->Unlock();
		}		
	}
	return result;
}
