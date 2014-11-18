#include "Threading.h"

using namespace blib;

ThreadItem::ThreadItem(size_t grabTimeout){  
  this->grabTimeout=grabTimeout;
  this->owner=NO_OWNER;
  grabCnt=0;  
#ifdef LINUX
  mutex=PTHREAD_MUTEX_INITIALIZER;
  /* or PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP */
//  pthread_mutex_t       mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutexattr_t   mta;

  pthread_mutexattr_init(&mta);
  /* or PTHREAD_MUTEX_RECURSIVE_NP */
  pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE);

  pthread_mutex_init(&mutex, &mta);
#else
  mutex=CreateMutex(NULL,false,NULL);
#endif
}

ThreadItem::~ThreadItem(void){  
#ifdef LINUX
  pthread_mutex_destroy(&mutex);
#else
  CloseHandle(mutex);    
#endif
}

bool ThreadItem::DropMutex(void){
  bool result=false;
  if(owner!=NO_OWNER){                               //if there is an owner, try to release
#ifdef LINUX
  if(pthread_equal(owner,pthread_self())!=0){
      grabCnt--;
      if(grabCnt==0){
        owner=NO_OWNER;
        result=(pthread_mutex_unlock(&mutex)==0);
      }
    }
#else
    if(owner==GetThreadId()){
      grabCnt--;
      if(grabCnt==0){
        owner=NO_OWNER;
        result=(ReleaseMutex(mutex)==TRUE);             
      }
    }
#endif
  }else
    result=true;
  return result;
}

bool ThreadItem::GrabMutex(void){
  bool bResult=false;
  int32_t errorCode;  
#ifdef LINUX
  if(owner==NO_OWNER){
    bResult=true;
    pthread_mutex_lock(&mutex);//==0;
    owner=pthread_self();
    grabCnt++;
  }else if(pthread_equal(owner,pthread_self())==0){     //do we own it already?
    bResult=true;
    pthread_mutex_lock(&mutex);                      //lock the mutex.
    if(bResult){
      owner=pthread_self();                             //set owner id
      grabCnt++;                                    //increment grab cntr
    }
    
#else
  if(owner!=GetThreadId()){                      //do we own it already?
    errorCode=WaitForSingleObject(mutex,grabTimeout);   //grab it
    switch(errorCode){                              
      case WAIT_ABANDONED:    
        break;
      case WAIT_TIMEOUT:
        break;
      case WAIT_FAILED:
        break;
      case WAIT_OBJECT_0:
        bResult=true;                                   //we grabbed the mutex
        owner=GetThreadId();                     //set owner id
        grabCnt++;                                      //increment grab cntr
    }
#endif
  }else{
    bResult=true;                                   //we already own it
    grabCnt++;                                      //increment grab cntr
  }
  return bResult;
}

threadId_t ThreadItem::GetOwner(void){
  return owner;
}

size_t ThreadItem::GetGrabCnt(void){
  return grabCnt;
}

size_t ThreadItem::GetGrabTimeout(){
  return grabTimeout;
}