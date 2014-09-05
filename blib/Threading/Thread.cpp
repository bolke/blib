#include "Threading.h"

using namespace blib;

Thread::Thread(ThreadItem& item,bool destroyLockpad):ThreadSafe(item,destroyLockpad){
	if(lock->Lock()){
    killEnabled=false;                                  //at default no killing, because it's not recommended
    killTimeout=KILL_TIMEOUT;                               
    threadHandle=NULL;                                      
    threadId=0;
    threadId=0;
    running=false;    
    runDelay=RUN_DELAY;
    setupCallback=NULL;
    runCallback=NULL;
    cleanupCallback=NULL;
		lock->Unlock();
  }
}

Thread::Thread(ThreadLock& lock):ThreadSafe(lock){
	if(lock.Lock()){
    killEnabled=false;                                  //at default no killing, because it's not recommended
    killTimeout=KILL_TIMEOUT;                               
    threadHandle=NULL;                                      
    threadId=0;
    threadId=0;
    running=false;    
    runDelay=RUN_DELAY;
    setupCallback=NULL;
    runCallback=NULL;
    cleanupCallback=NULL;
		lock.Unlock();
  }
}

Thread::~Thread(void){
  Stop();                                                 //stop the thread
  if(setupCallback!=NULL)
    delete setupCallback;
  if(runCallback!=NULL)
    delete runCallback;
  if(cleanupCallback!=NULL)
    delete cleanupCallback;
}

void Thread::Setup(void){
  running=true;    
  if(setupCallback!=NULL)
    setupCallback->Callback();				                           
}

void Thread::Run(void){
  while(running){        
    if(runCallback!=NULL)
      runCallback->Callback();
    else
      running=false;
    SleepMs(runDelay);
  }
}

void Thread::Cleanup(void){
  if(cleanupCallback!=NULL)
		cleanupCallback->Callback();
}

EnumResult_t Thread::SetKillEnabled(bool value){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    killEnabled=value;
    result=SUCCESS;    
    lock->Unlock();
  }  
  return result;
}

bool Thread::GetKillEnabled(void){
  bool bResult=false;  
  if(lock->Lock()){
    bResult=killEnabled;    
    lock->Unlock();
  }
  return bResult;
}

uint64_t Thread::GetKillTimeout(void){  
  uint64_t result=0;
  if(lock->Lock()){
    result=killTimeout;
    lock->Unlock();
  }
  return result;  
}

EnumResult_t Thread::SetKillTimeout(uint64_t killTimeout){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){
    this->killTimeout=killTimeout;
    result=SUCCESS;
    lock->Unlock();
  }
  return result;
}

bool Thread::GetRunning(){
	return running;
}

EnumResult_t Thread::SetRunning(bool running){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		this->running=running;
		result=SUCCESS;
	  lock->Unlock();
	}
	return result;
}

EnumResult_t Thread::SetSetupCallback(CallbackTemp* callback){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){
    if(!IsAlive()){
      setupCallback=callback;
    }
    lock->Unlock();    
  }
  return result;
}

EnumResult_t Thread::SetRunCallback(CallbackTemp* callback){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){
    if(!IsAlive()){
      runCallback=callback;
    }
    lock->Unlock();    
  }
  return result;
}

EnumResult_t Thread::SetCleanupCallback(CallbackTemp* callback){
  EnumResult_t result=FAIL;  
  if(lock->Lock()){
    if(!IsAlive()){
      cleanupCallback=callback;
    }
    lock->Unlock();    
  }
  return result;
}

CallbackTemp* Thread::GetSetupCallback(){
  return setupCallback;
}

CallbackTemp* Thread::GetRunCallback(){
  return runCallback;
}

CallbackTemp* Thread::GetCleanupCallback(){
  return cleanupCallback;
}

EnumResult_t Thread::SetRunDelay(uint64_t runDelay){   
  this->runDelay=runDelay;
  return SUCCESS;
}

uint64_t Thread::GetRunDelay(){
  return runDelay;
}

DWORD WINAPI Thread::Entrypoint(LPVOID args){
	if(args!=NULL){
		Thread *thread=(Thread *)args;                          //function called when a new thread is started, actual thread is given as argument  
		thread->Setup();                                        
		thread->Run();
		thread->Cleanup();		
	}
	return 0;
}

int32_t Thread::GetPriority(void){
  int32_t result=THREAD_PRIORITY_ERROR_RETURN;
  if(lock->Lock()){
    if(threadHandle!=NULL)
      result=GetThreadPriority(threadHandle);
    lock->Unlock();
  }
  return result;
}

EnumResult_t Thread::SetPriority(int32_t threadPriority){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    if(threadHandle!=NULL){
      if(SetThreadPriority(threadHandle,threadPriority))
        result=SUCCESS;
    }
    lock->Unlock();
  }
  return result;
}

bool Thread::IsAlive(void){
  DWORD exitCode=0;
  if(!threadHandle==NULL)
    GetExitCodeThread(threadHandle,&exitCode);            //grab the exitcode of the current thread
  return (exitCode==STILL_ACTIVE);                        //if active, alive, otherwise, not
}

EnumResult_t Thread::Start(void){
  EnumResult_t result=FAIL;
  if(!IsAlive()){      
    threadHandle=CreateThread(NULL,0,Thread::Entrypoint,this,0,&threadId); 
    if(threadHandle!=NULL)
      result=SUCCESS; 
  }
  return result;
}

EnumResult_t Thread::Stop(void){
  int32_t timeout=0;
  EnumResult_t result=FAIL;   
  while(IsAlive()&&(timeout<GetKillTimeout())){
    running=false;
    SleepMs(1);
    if(GetKillEnabled())
      timeout++;    
    if(GetKillTimeout()<timeout){
      if(GetKillEnabled()){
        result=Kill();
      }
    }  
  }
  if(!IsAlive())
    result=SUCCESS;
  return result;
}

EnumResult_t Thread::Kill(void){
  EnumResult_t result=FAIL;
  DWORD exitCode=0;  
  if(TerminateThread(threadHandle,exitCode))
    result=SUCCESS;      
  return result;
}

EnumResult_t Thread::ClearCallbacks(){
  EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(!IsAlive()){
			if(setupCallback!=NULL)
				delete setupCallback;
			if(runCallback!=NULL)
				delete runCallback;
			if(cleanupCallback!=NULL)
				delete cleanupCallback;
			setupCallback=NULL;
			runCallback=NULL;
			cleanupCallback=NULL;
			result=SUCCESS;
		}
		lock->Unlock();
	}
	return result;
}
