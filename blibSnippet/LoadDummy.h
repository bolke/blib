/*	
	file: LoadDummy.h
	date: 12-12-14
	author: bolke
	description: A linux only test load implemented into a function and thread, taking xx cpu load, on a single core.
*/

#ifndef BLIB_LOADDUMMY_H
#define BLIB_LOADDUMMY_H

#include "Blib.h"

#ifndef DUMMY_STARTER_LOAD
#define DUMMY_STARTER_LOAD 125
#endif

namespace blib{

class DummyLoadThread:public Thread{
  protected:
    uint32_t targetPercentage;
    uint32_t load;
    virtual void Run();
  public:
    DummyLoadThread(const uint32_t targetPercentage,const uint32_t load=DUMMY_STARTER_LOAD);
    uint32_t GetTargetPercentage();
    EnumResult_t SetTargetPercentage(const uint32_t value);
};

uint32_t DummyLoad(const uint32_t targetPercentage,uint32_t runtime=1,uint32_t load=DUMMY_STARTER_LOAD);

}

#endif
