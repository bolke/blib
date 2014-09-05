#include "Threading.h"

using namespace blib;

ThreadItem::ThreadItem(size_t grabTimeout){  
  this->grabTimeout=grabTimeout;
  owner=NO_OWNER;
  grabCnt=0;  
  mutex=CreateMutex(NULL,false,NULL);
}

ThreadItem::~ThreadItem(void){  
  CloseHandle(mutex);    
}

bool ThreadItem::DropMutex(void){
  bool result=false;
  if(owner!=NO_OWNER)                               //if there is an owner, try to release
    if(owner==GetThreadId()){
      grabCnt--;
      if(grabCnt==0){
        owner=NO_OWNER;
        result=(ReleaseMutex(mutex)==TRUE);             
      }
    }
  else
    result=true;
  return result;
}

bool ThreadItem::GrabMutex(void){
  bool bResult=false;
  int32_t errorCode;  

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