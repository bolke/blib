#include "Threading.h"

using namespace blib;

Thread::Thread(ThreadItem& item,bool destroyLockpad):ThreadSafe(item,destroyLockpad){
	if(lock->Lock()){
    killEnabled=false;                                  //at default no killing, because it's not recommended
    killTimeout=KILL_TIMEOUT;                               
#ifdef LINUX
		threadHandle=0;                                      
#else
    threadHandle=NULL;                                      
#endif
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
#ifdef LINUX		
    threadHandle=0;                                      
#else
		threadHandle=NULL;                                      
#endif
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

#ifdef LINUX
void* Thread::ThreadEntry(void* args){  
  Thread *thread=(Thread *)args;                          //function called when a new thread is started, actual thread is given as argument          
  thread->Setup();                                        //setup the thread, inherited function
	thread->Run();                                          //run thread, also virtual
	thread->Cleanup();                                      //cleanup, also within the cleanup thread  
	return 0;                                               //thread return value, default 0
}
#else
DWORD WINAPI Thread::Entrypoint(LPVOID args){
	if(args!=NULL){
		Thread *thread=(Thread *)args;                          //function called when a new thread is started, actual thread is given as argument  
		thread->Setup();                                        
		thread->Run();
		thread->Cleanup();		
	}
	return 0;
}
#endif

int32_t Thread::GetPriority(void){
  int32_t result=0;
#ifdef LINUX
#else
  result=THREAD_PRIORITY_ERROR_RETURN;
  if(lock->Lock()){
    if(threadHandle!=NULL)
      result=GetThreadPriority(threadHandle);
    lock->Unlock();
  }
#endif
  return result;
}

EnumResult_t Thread::SetPriority(int32_t threadPriority){
  EnumResult_t result=FAIL;
#ifdef LINUX
#else
  if(lock->Lock()){
    if(threadHandle!=NULL){
      if(SetThreadPriority(threadHandle,threadPriority))
        result=SUCCESS;
    }
    lock->Unlock();
  }
#endif
  return result;
}

bool Thread::IsAlive(void){
  bool result=false;
  DWORD exitCode=0;
  #ifdef LINUX
  exitCode=~0;
  if(!(threadHandle==0))                                    //if we've got a thread
    exitCode=pthread_kill(threadHandle,0);                
  result=(exitCode==0);                                   //if active, alive, otherwise, not
  #else
  if(!threadHandle==NULL)
    GetExitCodeThread(threadHandle,&exitCode);            //grab the exitcode of the current thread
  result=(exitCode==STILL_ACTIVE);
  #endif
  return result;
}

EnumResult_t Thread::Start(void){
  EnumResult_t result=FAIL;
  if(!IsAlive()){      
#ifdef LINUX
    if(pthread_create(&threadHandle,NULL,ThreadEntry,(void*)this)==0)
      result=SUCCESS;                                     //result is a success
	  else
		  threadHandle=0;
#else
    threadHandle=CreateThread(NULL,0,Thread::Entrypoint,this,0,&threadId); 
    if(threadHandle!=NULL)
      result=SUCCESS; 
#endif
  }
  return result;
}

EnumResult_t Thread::Stop(void){
  int32_t timeout=0;
  EnumResult_t result=FAIL; 
#ifdef LINUX
  threadId_t currentThreadId=pthread_self();
  if(pthread_equal(currentThreadId,threadId)){                          //are we committing suicide?
    running=false;                                       //if so, stop and result eq success
    result=SUCCESS;
  }else{
    while(IsAlive()&&(timeout<GetKillTimeout())){              //while we are running and the timeout hasn't ran out
      running=false;                                     //stop the thread the nice way
      SleepMs(1);                                           //wait 1 millisecond
      if(GetKillEnabled())                                   //if we may kill
        timeout++;                                        //increment the kill counter
      if(GetKillTimeout()<timeout){                          //if we may kill
        if(GetKillEnabled()){                                //and kill flag is set
          result=Kill();                                  //try to kill
        }                                                   
      }
    }
  }
#else
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
#endif
  if(!IsAlive())
    result=SUCCESS;
  return result;
}

EnumResult_t Thread::Kill(void){
  EnumResult_t result=FAIL;  
	if(IsAlive()){
#ifdef LINUX    
    if(pthread_kill(threadHandle,SIGKILL)==0)    
      result=SUCCESS;   
#else    
    DWORD exitCode=0;
    if(TerminateThread(threadHandle,exitCode))
      result=SUCCESS;      
#endif
  }
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
