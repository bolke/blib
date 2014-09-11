#ifndef BLIB_DEVICES_H
#define BLIB_DEVICES_H

#include "Basis.h"
#include "Threading.h"

#include "Device.h"												//consumer and producer and open close isopen
#include "DeviceCoupler.h"							  //a wrapper to couple devices to each other, d[0]->d[1]->d[2]->d[3]->d[4] etc
#include "DevicePusher.h"									//a wrapper to couple devices, to write data once and push to all
#include "DeviceWrapper.h"								//devicewrapper wraps around a device or an data object. make a device out of an data object
#include "DeviceOpener.h"									//opens the device connected every time something is done to it, push or pop, etc
#include "DeviceBuffer.h"									//creates a buffer for a device, with a threshold. saving data until a threshold is reached
#include "DeviceTimer.h"									//creates a device timer, timing input and output
#include "DataWrapper.h"									//wrap a data object into a device object
#include "DataStructure.h"

#endif
