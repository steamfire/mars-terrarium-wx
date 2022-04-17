/**********
 * Mars Terrarium Sensor + disp testing
 * 
 * Dan Bowen
 * MIT license 2020
 * 
 * 
***********/



#include <SPI.h>
#include <Wire.h>


#define PIN_I2C_POWER 7

unsigned long delayTimeReadSensors;

void setup() {
// turn on the I2C power by setting pin to opposite of 'rest state'
// This is a hack, and may need to be removed later if the BOARDS definitions of 
//   the S2 are fixed by adafruit
  pinMode(PIN_I2C_POWER, INPUT);
  delay(1);
  bool polarity = digitalRead(PIN_I2C_POWER);
  pinMode(PIN_I2C_POWER, OUTPUT);
  digitalWrite(PIN_I2C_POWER, !polarity);
//End Hack

  
  Serial.begin(115200);
  delay(1500); // wait for serial port to start up
  
  Serial.println("Mars OLED + Sensors Test");

  netStart(); // Start up the webserver and connect to Wifi
  sensorsStart();  // Start up the sensors
  OLEDStart();  // Start the display


    delayTimeReadSensors = 1000;



}

void loop() {
    delay(delayTimeReadSensors);
    printSensorsValues();
}
