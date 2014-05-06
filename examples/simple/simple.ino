
#include "OneWire.h"
#include "SerialNumber.h"

//DS2401 - flat side facing forward
//left pin ground, middle pin data, right pin NC
//Power is provieded over the data line - 2.2k pullup between data and v+
OneWire oneWire(6);

SerialNumber SerialNumber(&oneWire);

String serialNumber;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  serialNumber = SerialNumber.getNumber();
  Serial.println(serialNumber);
  delay(5000);
}
