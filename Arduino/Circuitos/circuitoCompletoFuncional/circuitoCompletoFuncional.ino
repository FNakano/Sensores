//BMP280
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//DS3231
#include "RTClib.h"

//DHT22
#include <DHT.h>

//DS18B20
#include  <OneWire.h>
#include <DallasTemperature.h>

//MPU
#include "MPU9250.h"

//BMP280
Adafruit_BMP280 bmp; // I2C

//DS3231
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//DHT22
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
int chk;
float umidade;
float temp;

//DS18B20
#define Pin 2
OneWire ourWire(Pin);
DallasTemperature sensors(&ourWire);

//LDR
int sensorValue = 0;
int sensorPin = A0; 

//MPU - an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x69);
int status;

char entrada;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(3000);

  //BMP280
  Serial.println(F("BMP280 teste"));
 
  if (!bmp.begin()) {
  Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
  while (1);
  }

  //DS3231
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    rtc.adjust(DateTime(2018, 10, 06, 22, 33, 0));
  }

  //DHT22
  dht.begin();

  //DS18B20
  sensors.begin();

  //MPU
  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }

  delay(500);
}


void loop() {
  DateTime now;
  if (Serial.available() > 0) {
      entrada = Serial.read();
      
      switch(entrada){
      case 'a':
        //BMP280
          Serial.println("BMP280------------------");
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
          delay(200);
        break;
      case 'b':
          now = rtc.now();
          Serial.println("DS3231------------------");
          Serial.print(now.year(), DEC);
          Serial.print('/');
          Serial.print(now.month(), DEC);
          Serial.print('/');
          Serial.print(now.day(), DEC);
          Serial.print(" (");
          Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
          Serial.print(") ");
          Serial.print(now.hour(), DEC);
          Serial.print(':');
          Serial.print(now.minute(), DEC);
          Serial.print(':');
          Serial.print(now.second(), DEC);
          Serial.println();
          
          Serial.print(" since midnight 1/1/1970 = ");
          Serial.print(now.unixtime());
          Serial.print("s = ");
          Serial.print(now.unixtime() / 86400L);
          Serial.println("d");
         
          delay(200);
          Serial.println();
        break;
      case 'c':
          //DHT22
          umidade = dht.readHumidity();
          temp = dht.readTemperature();
          Serial.println("DHT22------------------");
          Serial.print("Umidade: ");
          Serial.print(umidade);
          Serial.print(" %, Temperatura: ");
          Serial.print(temp);
          Serial.println(" Celsius");
          Serial.println();
          delay(200); //Delay 2 sec.
        break;
      case 'd':
          //DS18B20
          sensors.requestTemperatures();
          Serial.println("DS18B20------------------");
          Serial.print(sensors.getTempCByIndex(0));
          Serial.println(" graus Centigrados");
          Serial.print(sensors.getTempFByIndex(0)); //Lê-se e imprime a temperatura en graus Fahrenheit
          Serial.println(" graus Fahrenheit");
          Serial.println();
          delay(200);
        break;
      case 'e':
          //LDR
          Serial.println("LDR------------------");
          sensorValue = analogRead(sensorPin);
          Serial.println(sensorValue);
          Serial.println();
          delay(200);
        break;
      case 'f':
          //MPU
          Serial.println("MPU------------------");
          IMU.readSensor();
          // display the data
          Serial.print("AccelX: ");
          Serial.print(IMU.getAccelX_mss(),6);
          Serial.print("  ");
          Serial.print("AccelY: ");  
          Serial.print(IMU.getAccelY_mss(),6);
          Serial.print("  ");
          Serial.print("AccelZ: ");  
          Serial.println(IMU.getAccelZ_mss(),6);
          
          Serial.print("GyroX: ");
          Serial.print(IMU.getGyroX_rads(),6);
          Serial.print("  ");
          Serial.print("GyroY: ");  
          Serial.print(IMU.getGyroY_rads(),6);
          Serial.print("  ");
          Serial.print("GyroZ: ");  
          Serial.println(IMU.getGyroZ_rads(),6);
        
          Serial.print("MagX: ");  
          Serial.print(IMU.getMagX_uT(),6);
          Serial.print("  ");  
          Serial.print("MagY: ");
          Serial.print(IMU.getMagY_uT(),6);
          Serial.print("  ");
          Serial.print("MagZ: ");  
          Serial.println(IMU.getMagZ_uT(),6);
          
          Serial.print("Temperature in C: ");
          Serial.println(IMU.getTemperature_C(),6);
          Serial.println();
          delay(200);
        break;
    }
  }
}
