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
    BLIB_LIB_API ThreadItem(size_t grabTimeout=INFINITE);											//create mutex with delay, or infinite delay
    BLIB_LIB_API ~ThreadItem(void);																						//release mutex, no check of release    
    BLIB_LIB_API bool GrabMutex(void);																					//returns true if owner of mutex, or blocks
    BLIB_LIB_API bool DropMutex(void);																					//returns true if mutex is loose or released, false if not the owner (and cannot release)		
    BLIB_LIB_API threadId_t GetOwner(void);																		//returns owner id      
    BLIB_LIB_API size_t GetGrabCnt(void);																			//return nr of grabs
    BLIB_LIB_API size_t GetGrabTimeout(void);																	//return grab timeout
};

};

#endif
