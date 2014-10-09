#ifndef BLIB_SERIAL_H
#define BLIB_SERIAL_H

#include "Core.h"
#include "SerialPort.h"
#include "AutoSerialPort.h"

namespace blib{
  std::vector<std::string> GetAvailableSerialPorts();
};

#endif
