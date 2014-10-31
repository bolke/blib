#ifndef BLIB_THREADSAFE_H
#define BLIB_THREADSAFE_H

#include "Basis.h"
#include "ThreadLock.h"

namespace blib{

class ThreadSafe{
protected:
	ThreadLock* lock;
public:
	BLIB_LIB_API ThreadSafe(ThreadItem& item,bool destroyLockpad=false);
	BLIB_LIB_API ThreadSafe(ThreadLock& lock=*(new ThreadLock(false)));
	BLIB_LIB_API virtual ~ThreadSafe()=0;
	BLIB_LIB_API virtual ThreadLock& GetLock();
};

};

#endif
