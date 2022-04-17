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
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>


//For Featherwing OLED 128x64

#define PIN_I2C_POWER 7

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define TEXTROWHEIGHT 8
#define TEXTLEFTCOORDINATE 64




Adafruit_SH1107 display = Adafruit_SH1107(SCREEN_HEIGHT, SCREEN_WIDTH, &Wire);



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

  // Sensor setup code
     unsigned status;
    // BME sensor default settings
    status = bme.begin();  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
    delayTimeReadSensors = 1000;

// Start light sensor
lightMeter.begin();


  /////////////////////////  OLED display startup ////////////////////////

  delay(250); // wait for the OLED to power up
  display.begin(0x3C, true); // Address 0x3C default
  Serial.println("OLED begun");
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  //display.display();
  //delay(1000);


  // Clear the buffer.
  display.clearDisplay();
  display.display();


  display.setRotation(1); // Orient the display to landscape
  display.setTextWrap(false);


//  // Display the mars rover bitmap coded in this file
//  display.drawBitmap(0, 0,  marsrover, 64, 64, 1);
//  display.display();
//  delay(2000);

  // Display the mars rover bitmap coded in this file
  display.drawBitmap(0, 0,  marsrover, 64, 64, 1);

  // text display tests
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE, SH110X_BLACK);
  display.setCursor(64,TEXTROWHEIGHT);
  display.println("Terrarium:");
  display.display(); // actually display all of the above
}

void loop() {
    delay(delayTimeReadSensors);
    printSensorsValues();
}


void printSensorsValues() {
  
    display.setTextWrap(false);
    display.setCursor(TEXTLEFTCOORDINATE,TEXTROWHEIGHT*2);
    float BMEtempRaw = bme.readTemperature();
    display.print("T: ");
    display.print(BMEtempRaw, 0);
    display.println(" C");
    Serial.print("Temp ");
    Serial.print(BMEtempRaw, 0);
    Serial.println(" °C");

    display.setTextWrap(false);
    display.setCursor(TEXTLEFTCOORDINATE,TEXTROWHEIGHT*3);
    float BMEhumidityRaw = (bme.readHumidity());
    int BMEhumidity = roundf(BMEhumidityRaw);
    display.print("H: ");
    display.print(BMEhumidity);
    display.println(" %   ");
    Serial.print("Humidity = ");
    Serial.print(BMEhumidity);
    Serial.println(" %   ");

    display.setTextWrap(false);
    display.setCursor(TEXTLEFTCOORDINATE,TEXTROWHEIGHT*4);
    float BMEpressureRaw = bme.readPressure() ;
    float BMEpressureKPa = (roundf(BMEpressureRaw / 100.0F))/10.0; 
    display.print("P:");
    display.print(BMEpressureKPa, 1);
    display.println("kPa   ");
 
    Serial.print("Pressure = ");
    Serial.print(BMEpressureKPa, 1); 
    Serial.println("kPa   ");

/*  // This works, but not really interested in this right now.
    display.setTextWrap(false);
    display.setCursor(TEXTLEFTCOORDINATE,TEXTROWHEIGHT*5);
    float BMEaltitudeEarthRaw = bme.readAltitude(SEALEVELPRESSURE_HPA);
    int BMEaltitudeEarth = roundf(BMEaltitudeEarthRaw / 10.0F) * 10;
    if (BMEaltitudeEarth < 0){  // Clamp altitude on earth to 0 m
      BMEaltitudeEarth = 0;
    }
    
    display.print("A: ");
    display.print(BMEaltitudeEarth);
    display.print(" m   ");

    Serial.print("Approx. Altitude = ");
    Serial.print(BMEaltitudeEarth);
    Serial.println(" m    ");
    */

    display.setTextWrap(false);
    display.setCursor(TEXTLEFTCOORDINATE,TEXTROWHEIGHT*6);
    float lux = lightMeter.readLightLevel();
    int luxTens = roundf(lux / 10.0F) * 10;
    display.print("L: ");
    display.print(luxTens);
    display.println(" lux   ");
    
    Serial.print("Light: ");
    Serial.print(luxTens);
    Serial.println(" lux   ");




    Serial.println();
    display.display();
}
