/***************************************************************************
This is a library for the BMP280 humidity, temperature &amp;amp; pressure sensor
 
Written by Limor Fried &amp;amp; Kevin Townsend for Adafruit Industries.
BSD license, all text above must be included in any redistribution
 
sketch adopted &amp;amp; modified by Jayprakash Shet , www.iknowvations.in
***************************************************************************/
 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
 
// only used if we are using SPI to communicate with sensor
 
//#define BMP_SCK 13
//#define BMP_MISO 12
//#define BMP_MOSI 11
//#define BMP_CS 10
 
// Here we are using IIC
 
Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);
 
void setup() {
Serial.begin(9600);
Serial.println(F("BMP280 teste"));
 
if (!bmp.begin()) {
Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
while (1);
}
}
 
void loop() {
Serial.print(F("Temperatura = "));
Serial.print(bmp.readTemperature());
Serial.println(" *C");
 
Serial.print(F("Pressure = "));
Serial.print(bmp.readPressure());
Serial.println(" Pa");
 
Serial.print(F("Approx altitude = "));
Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
Serial.println(" m");
 
Serial.println();
delay(2000);
}
