#ifndef BLIB_AUTOSERIALPROT_H
#define BLIB_AUTOSERIALPORT_H

#include "SerialPort.h"

namespace blib{

class AutoSerialPort:public SerialPort{
protected:
  CallbackTemp* identifyCallback;
public:
  AutoSerialPort();
  virtual EnumResult_t Open(void);
  virtual EnumResult_t SetIdentifyCallback(CallbackTemp* value);
};

};

#endif
