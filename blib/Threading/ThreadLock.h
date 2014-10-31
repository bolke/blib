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
  BLIB_LIB_API ThreadLock(bool locked=true);																												//create a lock, default locked
  BLIB_LIB_API ThreadLock(ThreadItem& lockpad,bool locked=true);																		//use a given lockpad, default locked
  BLIB_LIB_API virtual bool Lock();																																//grab lock, blocking
  BLIB_LIB_API virtual bool Unlock();																															//tries to unlock, fails if not the owner
  BLIB_LIB_API threadId_t GetOwner(void);																													//return threadId of owner
  BLIB_LIB_API size_t GetLockCnt(void);																														//get nr of locks
  BLIB_LIB_API ThreadItem* GetLockpad();																														//returns the mutex containing lock
  BLIB_LIB_API EnumResult_t SetLockpad(ThreadItem* lockpad,bool locked=true,bool lockedExchange=false);	//set a new lockpad
  BLIB_LIB_API bool GetDestroyLockpad();
  BLIB_LIB_API EnumResult_t SetDestroyLockpad(bool destroyLockpad);
  BLIB_LIB_API ~ThreadLock();
};

};

#endif
