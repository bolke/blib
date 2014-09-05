#ifndef BLIB_THREADING_H
#define BLIB_THREADING_H

#include <stdlib.h>
#include <stdio.h>
#include <queue>

#include "Basis.h"										//all classes from basis library project

namespace blib{												//constants in blib namespace
  const int32_t NO_OWNER=0;           //no owner id, 0 is safe
  const int32_t KILL_TIMEOUT=100;     //default kill timeout in ms. if possible, try to kill after this timeout
  const int32_t RUN_DELAY=1;					//running delay of 1 millisecond by default
  DWORD GetThreadId();								//return the current thread id
};

#include "ThreadItem.h"               //base thread item, mutex grab and drop functions
#include "Thread.h"							      //a thread class, with virtual functions
#include "ThreadLock.h"               //a class that makes locking and unlocking easier 
#include "ThreadSafe.h"								//inherite this if a class should be thread safe
#include "ThreadWorker.h"							//task worker, executes tasks 
#include "ThreadTask.h"								//a callback with execcnt,execlimit
#include "ThreadTaskPool.h"						//a task container, multiple threadworkers can get tasks from here

#endif
