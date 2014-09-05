#ifndef BLIB_THREADLOCK_H
#define BLIB_THREADLOCK_H

#include "Basis.h"
#include "ThreadItem.h"

namespace blib{

class ThreadLock:public Base{
protected:
  bool destroyLockpad;
  ThreadItem* lockpad;
public:  
  ThreadLock(bool locked=true);																												//create a lock, default locked
  ThreadLock(ThreadItem& lockpad,bool locked=true);																		//use a given lockpad, default locked
  virtual bool Lock();																																//grab lock, blocking
  virtual bool Unlock();																															//tries to unlock, fails if not the owner
  threadId_t GetOwner(void);																													//return threadId of owner
  size_t GetLockCnt(void);																														//get nr of locks
  ThreadItem* GetLockpad();																														//returns the mutex containing lock
  EnumResult_t SetLockpad(ThreadItem* lockpad,bool locked=true,bool lockedExchange=false);	//set a new lockpad
  bool GetDestroyLockpad();
  EnumResult_t SetDestroyLockpad(bool destroyLockpad);
  ~ThreadLock();
};

};

#endif
