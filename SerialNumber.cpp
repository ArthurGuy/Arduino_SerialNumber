/**
	SerialNumber.cpp
*/
#include "Arduino.h"
#include "SerialNumber.h"

//Setup the serial number instance, a onewire object needs to be passed in
SerialNumber::SerialNumber(OneWire* _oneWire)
{
	_wire = _oneWire;
}


//Fetch the return the formatted serial number
String SerialNumber::getNumber()
{
  	//1-Wire bus reset, needed to start operation on the bus,
  	//returns true if presence pulse detected - i.e. the device is there
  	if (_wire->reset())
  	{
	    _wire->write(0x33);  //Send Read data command
	    
	    //Read of the first byte - this is the device family code
	    //This byte is needed for the crc check below
	    data[0] = _wire->read();
	    
	    for (i = 1; i <= 6; i++)
	    {
	      data[i] = _wire->read();
	    }
	 
	 	//Read the CRC byte and the calculate our own
	    crc_byte = _wire->read();
	    crc_calc = _wire->crc8(data, 7);
	
		//Compare the two CRC bytes
	    if (crc_calc != crc_byte) {
			//The data is invalid - the crc check failed
	    	return false;
	    }
	}
	else //Nothing is connected in the bus
	{
	    return false;
	}

	//Concatinate the serial number string and return
  	return String(data[1]/16, HEX)+String(data[1]%16, HEX)+
        String(data[2]/16, HEX)+String(data[2]%16, HEX)+
        String(data[3]/16, HEX)+String(data[3]%16, HEX)+
        String(data[4]/16, HEX)+String(data[4]%16, HEX)+
        String(data[5]/16, HEX)+String(data[5]%16, HEX)+
        String(data[6]/16, HEX)+String(data[6]%16, HEX);
}

