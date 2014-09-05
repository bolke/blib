#ifndef BLIB_THREADSAFE_H
#define BLIB_THREADSAFE_H

#include "Basis.h"
#include "ThreadLock.h"

namespace blib{

class ThreadSafe{
protected:
	ThreadLock* lock;
public:
	ThreadSafe(ThreadItem& item,bool destroyLockpad=false);
	ThreadSafe(ThreadLock& lock=*(new ThreadLock(false)));
	virtual ~ThreadSafe()=0;
	virtual ThreadLock& GetLock();
};

};

#endif
