#ifndef BLIB_THREADITEM_H
#define BLIB_THREADITEM_H

#include "Basis.h"

namespace blib{

class ThreadItem:public Base{
  protected:
    size_t grabTimeout;																						//time the grab tries to grab the mutex before giving up
    size_t grabCnt;																								//counter of the amount of grabs performed on the mutex
    threadId_t owner;																							//current owner of the mutex and thus of the class, is threadid
    HANDLE mutex;																									//mutex that gets grabbed, or released      
  public:		
    ThreadItem(size_t grabTimeout=INFINITE);											//create mutex with delay, or infinite delay
    ~ThreadItem(void);																						//release mutex, no check of release    
    bool GrabMutex(void);																					//returns true if owner of mutex, or blocks
    bool DropMutex(void);																					//returns true if mutex is loose or released, false if not the owner (and cannot release)		
    threadId_t GetOwner(void);																		//returns owner id      
    size_t GetGrabCnt(void);																			//return nr of grabs
    size_t GetGrabTimeout(void);																	//return grab timeout
};

};

#endif
