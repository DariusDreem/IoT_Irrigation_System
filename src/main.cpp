#include <Arduino.h>
#include "Motor.h"
#include "HSensor.h"


void setup()
{
  Serial.begin(9600);
  Motor motor = New Motor(2);
  HSensor sensor = New HSensor(3);
  Serial.println(sensor.getHumidity()); 
}

void loop()
{
  
}
