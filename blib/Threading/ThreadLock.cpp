#include "ThreadLock.h"

using namespace blib;

ThreadLock::ThreadLock(bool locked){
  destroyLockpad=true;
  this->lockpad=new ThreadItem();  
  if(locked)
    Lock();
}

ThreadLock::ThreadLock(ThreadItem& lockpad,bool locked){
  destroyLockpad=false;
  this->lockpad=&lockpad;  
  if(locked)
    Lock();
}

ThreadLock::~ThreadLock(){  
  lockpad->DropMutex();
	if(destroyLockpad){
		if(lockpad!=NULL)
      delete lockpad;
		lockpad=NULL;
	}
}

bool ThreadLock::Lock(){
  return lockpad->GrabMutex();
}

bool ThreadLock::Unlock(){
  return lockpad->DropMutex();
}

threadId_t ThreadLock::GetOwner(void){
  return lockpad->GetOwner();
}

size_t ThreadLock::GetLockCnt(void){
  return lockpad->GetGrabCnt();
}

ThreadItem* ThreadLock::GetLockpad(){
  return lockpad;
}

EnumResult_t ThreadLock::SetLockpad(ThreadItem* lockpad,bool locked,bool lockedExchange){
  EnumResult_t result=FAIL;  
  if(lockpad!=NULL){
    destroyLockpad=false;
    ThreadItem* oldLockpad=this->lockpad;
    if(locked)
      lockpad->GrabMutex();
    if(lockedExchange){
      oldLockpad->GrabMutex();   
      this->lockpad=lockpad;
      oldLockpad->DropMutex();
    }else{
      this->lockpad=lockpad;
    }
    result=SUCCESS;
  }
  return result;
}

bool ThreadLock::GetDestroyLockpad(){
  return destroyLockpad;
}

EnumResult_t ThreadLock::SetDestroyLockpad(bool destroyLockpad){
  this->destroyLockpad=destroyLockpad;
  return SUCCESS;
}