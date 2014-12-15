#include "LoadDummy.h"
#include <stdio.h>
#include <sys/times.h>
#include <sys/resource.h>

using namespace blib;

DummyLoadThread::DummyLoadThread(const uint32_t targetPercentage,const uint32_t load){
  this->targetPercentage=targetPercentage;
  this->load=load;
}

void DummyLoadThread::Run(){
  volatile uint32_t i,j,k;
  uint64_t tick=GetRunTimeMs();
  double first=0;
  double second=0;
  uint32_t sweetspot=load;
  uint32_t target=GetTargetPercentage();
  uint32_t percentage=target;  
  struct timespec ts;
  clockid_t cid;
  i=j=k=0;
  j=load;
  pthread_getcpuclockid(pthread_self(), &cid);
  clock_gettime(cid, &ts);    
  first=(ts.tv_sec+(((double)ts.tv_nsec)*0.000000001));
  while(running){  
    for(i=0;i<j;i++)
      k=i+j*i-j*k;
    if((GetRunTimeMs()-tick)>=1000){
      first=second;
      second=(ts.tv_sec+(((double)ts.tv_nsec)*0.000000001));
      percentage=(uint32_t)(((second-first)*100.0f)+0.5f);
      if(percentage==0)
        percentage=1;
      if(percentage<target){
        if((target*0.80)>percentage)
          j=(j/percentage)*target;
        else
          j=j+(j/5);
      }else if(percentage>target){
        j=(j/percentage)*target;
        if(j<j/5)
          j=j-(j/5);
      }else{
        if(sweetspot==0)
          sweetspot=j;
        else{
          sweetspot=(sweetspot+j)/2;
          j=sweetspot;
        }
      }
      if(j==0)
        j=target;
      tick=GetRunTimeMs();
      if(target!=GetTargetPercentage()){
        target=GetTargetPercentage();
        sweetspot=0;
      }
      pthread_getcpuclockid(pthread_self(), &cid);
      clock_gettime(cid, &ts);    
    }
    SleepMs(1);  
  }
    this->load=DummyLoad(this->GetTargetPercentage(),10,this->load);
}

uint32_t DummyLoadThread::GetTargetPercentage(){
  uint32_t result=0;
  if(lock->Lock()){
    result=this->targetPercentage;
    lock->Unlock();
  }
  return result;
}

EnumResult_t DummyLoadThread::SetTargetPercentage(const uint32_t value){
  EnumResult_t result=FAIL;
  if(lock->Lock()){
    this->targetPercentage=value;
    result=SUCCESS;
    lock->Unlock();
  }
  return result;
}
  
uint32_t blib::DummyLoad(const uint32_t targetPercentage,uint32_t runtime,uint32_t load){  
  volatile uint32_t i,j,k;
  uint64_t tick=GetRunTimeMs();
  double first=0;
  double second=0;
  uint32_t percentage=targetPercentage;
  struct timespec ts;
  clockid_t cid;
  i=j=k=0;
  j=load;
  pthread_getcpuclockid(pthread_self(), &cid);
  clock_gettime(cid, &ts);    
  first=(ts.tv_sec+(((double)ts.tv_nsec)*0.000000001));
  while(runtime>0){        
    for(i=0;i<j;i++)
      k=i+j*i-j*k;
    if((GetRunTimeMs()-tick)>=1000){
      first=second;
      second=(ts.tv_sec+(((double)ts.tv_nsec)*0.000000001));
      percentage=(uint32_t)(((second-first)*100.0f)+0.5f);
      if(percentage==0)
        percentage=1;
      if(percentage<targetPercentage){
        if((targetPercentage*0.80)>percentage)
          j=(j/percentage)*targetPercentage;
        else
          j=j+(j/5);
      }else if(percentage>targetPercentage){
        j=(j/percentage)*targetPercentage;
        if(j<j/5)
          j=j-(j/5);
      }
      if(j==0)
        j=targetPercentage;
      runtime--;
      tick=GetRunTimeMs();
      pthread_getcpuclockid(pthread_self(), &cid);
      clock_gettime(cid, &ts);    
    }
    SleepMs(1);
  }
  return j;
}
