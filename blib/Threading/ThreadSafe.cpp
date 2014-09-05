#include "ThreadSafe.h"

using namespace blib;

ThreadSafe::ThreadSafe(ThreadItem& item,bool destroyLockpad){
	lock=new ThreadLock(item,false);	
	lock->SetDestroyLockpad(destroyLockpad);
}

ThreadSafe::ThreadSafe(ThreadLock& lock){
	this->lock=&lock;
}

ThreadSafe::~ThreadSafe(){
	if(lock!=NULL)
	  delete lock;
	lock=NULL;
}

ThreadLock& ThreadSafe::GetLock(){
  return *lock;
}
