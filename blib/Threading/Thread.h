#ifndef BLIB_THREAD_H
#define BLIB_THREAD_H

#include "Basis.h"
#include "ThreadSafe.h"

namespace blib{

class Thread:public Base,public ThreadSafe{																	
  protected:
	#ifdef LINUX
    threadId_t threadHandle;                      						//used for killing and tracking the thread
    threadId_t threadId;                          						//unique id of this thread, same value used in mutex functions
    static void* ThreadEntry(void* args);         						//static function used to start the threads
	#else
		HANDLE threadHandle;																			//used for killing and tracking the thread
    DWORD threadId;																						//unique id of this thread, same value used in mutex functions
    static DWORD WINAPI Entrypoint(LPVOID args);							//static function used to start the threads
  #endif
    CallbackTemp* setupCallback;															//alternative for setup
    CallbackTemp* runCallback;																//alternative for run
    CallbackTemp* cleanupCallback;														//alternative for cleanup
    
    bool killEnabled;																					//used at your own risk
    bool running;																							//thread in run function or not
    uint64_t killTimeout;																			//time before the killing is executed, if activated
    uint64_t runDelay;																				//delay between calls to run callback, in ms
    
    BLIB_LIB_API virtual void Setup(void);										//thread setup function, runs within the new thread       
	  BLIB_LIB_API virtual void Run(void);											//here goes the main function, runs within the new thread
	  BLIB_LIB_API virtual void Cleanup(void); 									//cleanup function, also runs within the new thread
    
    EnumResult_t Kill(void);																	//kill the thread hard
    
  public:
		BLIB_LIB_API Thread(ThreadItem& item,bool destroyLockpad=false);				//init internal a new lock with this threadItem
    BLIB_LIB_API Thread(ThreadLock& lock=*(new ThreadLock(false)));				//init a new lock
    BLIB_LIB_API ~Thread(void);																						//stops thread

    BLIB_LIB_API bool IsAlive(void);																				//is this thread alive, checks through threadHandle
    BLIB_LIB_API EnumResult_t Start(void);																	//starts this thread, calls Entrypoint within a new thread, this calls setup run and cleanup
    BLIB_LIB_API EnumResult_t Stop(void);																	//order the thread to stop. calls kill after timeout if enabled

    BLIB_LIB_API EnumResult_t SetKillEnabled(bool bKillEnabled);						//killing is disabled by default, not recommended
    BLIB_LIB_API bool GetKillEnabled(void);														

    BLIB_LIB_API uint64_t GetKillTimeout(void);														//time the thread waits until killing starts, if enabled
    BLIB_LIB_API EnumResult_t SetKillTimeout(uint64_t killTimeout);         
    BLIB_LIB_API EnumResult_t SetPriority(int32_t threadPriority);					//thread priority based upon OS
    BLIB_LIB_API int32_t GetPriority(void);                            

		BLIB_LIB_API bool GetRunning();																		    //return the running variable, not if the thread is alive, use IsAlive for that
		BLIB_LIB_API EnumResult_t SetRunning(bool running);										//set the running variable

    BLIB_LIB_API EnumResult_t SetSetupCallback(CallbackTemp* callback);    //set the setup callback, old one, if any, isn't destroyed
    BLIB_LIB_API EnumResult_t SetRunCallback(CallbackTemp* callback);      //set the run callback, old one, if any, isn't destroyed
    BLIB_LIB_API EnumResult_t SetCleanupCallback(CallbackTemp* callback);  //set the cleanup callback, odl one, if any, isn't destroy

    BLIB_LIB_API CallbackTemp* GetSetupCallback();                         //return the callback for setup
    BLIB_LIB_API CallbackTemp* GetRunCallback();                           //return the callback for run
    BLIB_LIB_API CallbackTemp* GetCleanupCallback();                       //return the callback for cleanup

		BLIB_LIB_API EnumResult_t ClearCallbacks();														//clear all the callbacks, delete them and set to NULL

    BLIB_LIB_API uint64_t GetRunDelay();                                   //return running delay in milliseconds, default 1ms
    BLIB_LIB_API EnumResult_t SetRunDelay(uint64_t runDelay);							//running delay in milliseconds  
};

};

#endif
