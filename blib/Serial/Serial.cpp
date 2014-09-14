#include "Serial.h"

using namespace blib;

std::vector<std::string> blib::GetAvailableSerialPorts(){
	std::vector<std::string> result;
	StringParser sp;
	SerialPort serial;
	for(int32_t i=1;i<999;i++){
		serial.SetPort(sp.ToString("COM%i",i));
		serial.Open();
		if(serial.IsOpen())
			result.push_back(serial.GetPort());
		serial.Close();
	}
	return result;
}
