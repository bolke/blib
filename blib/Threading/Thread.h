#ifndef BLIB_THREAD_H
#define BLIB_THREAD_H

#include "Basis.h"
#include "ThreadSafe.h"

namespace blib{

class Thread:public Base,public ThreadSafe{																	
  protected:
		HANDLE threadHandle;																			//used for killing and tracking the thread
    DWORD threadId;																						//unique id of this thread, same value used in mutex functions
    static DWORD WINAPI Entrypoint(LPVOID args);							//static function used to start the threads

    CallbackTemp* setupCallback;															//alternative for setup
    CallbackTemp* runCallback;																//alternative for run
    CallbackTemp* cleanupCallback;														//alternative for cleanup
    
    bool killEnabled;																					//used at your own risk
    bool running;																							//thread in run function or not
    uint64_t killTimeout;																			//time before the killing is executed, if activated
    uint64_t runDelay;																				//delay between calls to run callback, in ms
    
    virtual void Setup(void);																	//thread setup function, runs within the new thread       
	  virtual void Run(void);																		//here goes the main function, runs within the new thread
	  virtual void Cleanup(void); 															//cleanup function, also runs within the new thread
    
    EnumResult_t Kill(void);																	//kill the thread hard
    
  public:
		Thread(ThreadItem& item,bool destroyLockpad=false);				//init internal a new lock with this threadItem
    Thread(ThreadLock& lock=*(new ThreadLock(false)));				//init a new lock
    ~Thread(void);																						//stops thread

    bool IsAlive(void);																				//is this thread alive, checks through threadHandle
    EnumResult_t Start(void);																	//starts this thread, calls Entrypoint within a new thread, this calls setup run and cleanup
    EnumResult_t Stop(void);																	//order the thread to stop. calls kill after timeout if enabled

    EnumResult_t SetKillEnabled(bool bKillEnabled);						//killing is disabled by default, not recommended
    bool GetKillEnabled(void);														

    uint64_t GetKillTimeout(void);														//time the thread waits until killing starts, if enabled
    EnumResult_t SetKillTimeout(uint64_t killTimeout);         
    EnumResult_t SetPriority(int32_t threadPriority);					//thread priority based upon OS
    int32_t GetPriority(void);                            

		bool GetRunning();																		    //return the running variable, not if the thread is alive, use IsAlive for that
		EnumResult_t SetRunning(bool running);										//set the running variable

    EnumResult_t SetSetupCallback(CallbackTemp* callback);    //set the setup callback, old one, if any, isn't destroyed
    EnumResult_t SetRunCallback(CallbackTemp* callback);      //set the run callback, old one, if any, isn't destroyed
    EnumResult_t SetCleanupCallback(CallbackTemp* callback);  //set the cleanup callback, odl one, if any, isn't destroy

    CallbackTemp* GetSetupCallback();                         //return the callback for setup
    CallbackTemp* GetRunCallback();                           //return the callback for run
    CallbackTemp* GetCleanupCallback();                       //return the callback for cleanup

		EnumResult_t ClearCallbacks();														//clear all the callbacks, delete them and set to NULL

    uint64_t GetRunDelay();                                   //return running delay in milliseconds, default 1ms
    EnumResult_t SetRunDelay(uint64_t runDelay);							//running delay in milliseconds  
};

};

#endif
