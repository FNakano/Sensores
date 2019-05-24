#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "FirebaseESP32.h"

/*------------------ EDUROAM*/
#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks
#define EAP_IDENTITY "xxxxxx@usp.br" //if connecting from another corporation, use identity@organisation.domain in Eduroam 
#define EAP_PASSWORD "senha" //your Eduroam password
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


  /*------------------ LDR*/
  valorLDR = analogRead(A0); // read analog input pin 0 isso é no VP
  Serial.print("LDR: ");
  Serial.println(valorLDR, DEC); // prints the value read
  Serial.print(" \n"); // prints a space between the numbers

  /*------------------ Firebase*/
  String pathMac = "/" + WiFi.macAddress();

  String jsonStr = "{\"TempBME\" : " + String(bme.readTemperature()) + ", \"UmidadeBME\" : " + String(bme.readHumidity()) + ", \"PressaoBME\" : " + String(bme.readPressure() / 100.0F) + ", \"LDR\" : " + String(valorLDR) + "}";
  Serial.print(jsonStr);

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
