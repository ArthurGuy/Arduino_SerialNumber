/**
  	Serial Number Library - Fetch the ID from a DS2401 onewire id chip
	Returns a string - usefull for when device specific id's are needed
  
  	DS2401 - flat side forwards
  	left pin ground, middle pin data, right pin NC
	Power is provided through the data line - 2.2k pullup between data and v+
*/
#include "Arduino.h"
#include "OneWire.h"

#ifndef SerialNumber_h
#define SerialNumber_h

class SerialNumber
{
  public:
    SerialNumber(OneWire* _oneWire);
    void fetchNumber();
    String getNumber();
    byte getPart(int i);
    boolean numberReady();
    
  private:
    // A pointer to the one wire instance
    OneWire* _wire;
    
    //Loop position
    byte i;
    
    //Store the data comming off the device
    byte data[8];
    
    boolean _dataFetched;
    
    //CRC Check
    //The calculated value
    byte crc_calc;
	//The actual value
    byte crc_byte;

};

#endif
