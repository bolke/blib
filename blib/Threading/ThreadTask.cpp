#include "ThreadTask.h"

using namespace blib;

ThreadTask::ThreadTask(CallbackTemp* task,uint32_t execLimit){
	this->task=task;
	this->execLimit=execLimit;
	this->execCnt=0;
}

bool ThreadTask::IsCompleted(){
  return ((execLimit>0)&&(execCnt>=execLimit))||(task==NULL);
}

ThreadTask::~ThreadTask(){
  if(task!=NULL)
		delete task;
}
