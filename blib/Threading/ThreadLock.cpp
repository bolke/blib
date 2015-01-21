#include "Threading.h"

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
	if(lockpad)
    return lockpad->GrabMutex();
	return true;
}

bool ThreadLock::Unlock(){
	if(lockpad)
    return lockpad->DropMutex();
	return true;
}

threadId_t ThreadLock::GetOwner(void){
	if(lockpad)
    return lockpad->GetOwner();
	return NO_OWNER;
}

size_t ThreadLock::GetLockCnt(void){
	if(lockpad)
		return lockpad->GetGrabCnt();
	return 0;
}

ThreadItem* ThreadLock::GetLockpad(){
  return lockpad;
}

EnumResult_t ThreadLock::SetLockpad(ThreadItem* lockpad,bool locked,bool lockedExchange){
  EnumResult_t result=FAIL;  
  if(lockpad!=NULL){
    ThreadItem* oldLockpad=this->lockpad;
    if(locked)
      lockpad->GrabMutex();
    if(lockedExchange){
			if(oldLockpad){
				oldLockpad->GrabMutex();   
				this->lockpad=lockpad;
				oldLockpad->DropMutex();
			}
    }else
      this->lockpad=lockpad;    
		if(oldLockpad){
			if(destroyLockpad)
				delete oldLockpad;		
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
