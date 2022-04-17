#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// Define the onboard sensor instance
Adafruit_BME280 bme; // I2C

//Define the BH1750 light sensor
BH1750 lightMeter;


void sensorsStart(void) {
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
    // Start light sensor
lightMeter.begin();


  
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
