#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "FirebaseESP32.h"
#include "RTClib.h"
#include "Adafruit_CCS811.h"

/*------------------ EDUROAM*/
#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks
#define EAP_IDENTITY "10723795@usp.br" //if connecting from another corporation, use identity@organisation.domain in Eduroam 
#define EAP_PASSWORD "ZXASQ!W@8c35aebc" //your Eduroam password
const char* ssid = "eduroam"; // Eduroam SSID
int counter=0;
/*******/

//Firebase Configs
#define FIREBASE_HOST "redesensoresgit.firebaseio.com" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "Big6OmN1pQLrHByhrVI99Ne5Mfaq3PvyLC0wnz7G"
//Define Firebase Data object
FirebaseData firebaseData;

/*------------------ BME280*/
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C

/*------------------ LDR*/
int valorLDR;

/*------------------ DS3231*/
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

/*------------------ CCS811*/
Adafruit_CCS811 ccs;

void setup() {
  Serial.begin(115200);

  /*------------------ EDUROAM*/
  Serial.println();
  Serial.print("Connecting to network: ");
  Serial.println(ssid);
  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA); //init wifi mode
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide identity
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide username --> identity and username is same
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD)); //provide password
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); //set config settings to default
  esp_wifi_sta_wpa2_ent_enable(&config); //set config settings to enable function
  WiFi.begin(ssid); //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //after 30 seconds timeout - reset board
      ESP.restart();
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address set: "); 
  Serial.println(WiFi.localIP()); //print LAN IP
  /****************/

  /*------------------ BME280*/
  bool status;
    
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
  }

  /*------------------ Firebase*/
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  /*------------------ DS3231*/
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date &amp; time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date &amp; time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  /*------------------ CCS811*/
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
  }
  //Calibra o sensor de temperatura
  if(ccs.available()){
    float temp = ccs.calculateTemperature();
    ccs.setTempOffset(temp - 25.0);
  }
}

void loop() {
  
  /*------------------ BME280*/
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");

  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();

  /*------------------ DS3231*/
    DateTime now = rtc.now();
     
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
     
    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now + TimeSpan(7,12,30,6));
     
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();  

  /*------------------ LDR*/
  valorLDR = analogRead(A0); // read analog input pin 0 isso é no VP
  Serial.print("LDR: ");
  Serial.println(valorLDR, DEC); // prints the value read
  Serial.print(" \n"); // prints a space between the numbers

  /*------------------ CCS811*/
  if(ccs.available()){
    float temp = ccs.calculateTemperature();
     if(!ccs.readData()){
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.print(ccs.getTVOC());
      Serial.print("ppb Temp:");
      Serial.println(temp);
     }else{
      Serial.println("ERRO NO CCS811!");
     }
  }
  

  /*------------------ Firebase*/
  String pathMac = "/" + WiFi.macAddress();

  //String jsonStr = "{\"TempBME\" : " + String(bme.readTemperature()) + ", \"UmidadeBME\" : " + String(bme.readHumidity()) + ", \"PressaoBME\" : " + String(bme.readPressure() / 100.0F) + ", \"LDR\" : " + String(valorLDR) + ;
  String jsonStr = "{";
  jsonStr += "\"TempBME\" : " + String(bme.readTemperature()) + ",";
  jsonStr += "\"UmidadeBME\" : " + String(bme.readHumidity()) + ", ";
  jsonStr += "\"PressaoBME\" : " + String(bme.readPressure() / 100.0F) + ",";
  jsonStr += "\"LDR\" : " + String(valorLDR) + ",";
  jsonStr += "\"Ano\" : " + String(now.year()) + ", ";
  jsonStr += "\"Mes\" : " + String(now.month()) + ", ";
  jsonStr += "\"Dia\" : " + String(now.day()) + ", ";
  jsonStr += "\"Hora\" : " + String(now.hour()) + ", ";
  jsonStr += "\"Minuto\" : " + String(now.minute()) + ", ";
  jsonStr += "\"Segundo\" : " + String(now.second()) + ", ";
  jsonStr += "\"CO2\" : " + String(ccs.geteCO2()) + ", ";
  jsonStr += "\"TVOC\" : " + String(ccs.getTVOC());
  jsonStr += "}";
  Serial.println(jsonStr);

  if (Firebase.pushJSON(firebaseData, pathMac, jsonStr))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }

  delay(4000);
}
