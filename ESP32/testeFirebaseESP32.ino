

/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2019 mobizt
 *
 *23.04.2019 - Incluindo código para eduroam - compilou e transferiu.
*/

//This example shows how to read, store and update database using get, set, push and update functions.
//Required HTTPClientESP32Ex library to be installed  https://github.com/mobizt/HTTPClientESP32Ex

#include <WiFi.h>
#include "FirebaseESP32.h"


#define FIREBASE_HOST "redesensoresgit.firebaseio.com" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "Big6OmN1pQLrHByhrVI99Ne5Mfaq3PvyLC0wnz7G"

/** HOME AP
#define WIFI_SSID "andro"
#define WIFI_PASSWORD "AoInfinitoEAl3m"
*/

/** eduroam */
#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks
#define EAP_IDENTITY "10723795@usp.br" //if connecting from another corporation, use identity@organisation.domain in Eduroam 
#define EAP_PASSWORD "ZXASQ!W@8c35aebc" //your Eduroam password
const char* ssid = "eduroam"; // Eduroam SSID
int counter=0;
/*******/

//Define Firebase Data object
FirebaseData firebaseData;

void setup()
{

  Serial.begin(115200);
  Serial.println();
  Serial.println();

/******* Home AP
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
*********/

/*******eduroam **********/
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

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  String path = "/ESP32_Test";
  String jsonStr;

  //Firebase.deleteNode(firebaseData, path);

  Serial.println("------------------------------------");
  Serial.println("Path exist test...");
  if (Firebase.pathExist(firebaseData, path))
  {
    Serial.println("Path " + path + " exists");
  }
  else
  {
    Serial.println("Path " + path + " is not exist");
  }
  Serial.println("------------------------------------");
  Serial.println();

  Serial.println("------------------------------------");
  Serial.println("Set integer test...");

  for (uint8_t i = 0; i < 10; i++)
  {

    if (Firebase.setInt(firebaseData, path + "/Int/Data" + (i + 1), (i + 1) * 10))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.print("VALUE: ");
      if (firebaseData.dataType() == "int")
        Serial.println(firebaseData.intData());
      else if (firebaseData.dataType() == "float")
        Serial.println(firebaseData.floatData());
      else if (firebaseData.dataType() == "boolean")
        Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
      else if (firebaseData.dataType() == "string")
        Serial.println(firebaseData.stringData());
      else if (firebaseData.dataType() == "json")
        Serial.println(firebaseData.jsonData());
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
  }

  Serial.println("------------------------------------");
  Serial.println("Get integer test...");

  for (uint8_t i = 0; i < 10; i++)
  {

    if (Firebase.getInt(firebaseData, path + "/Int/Data" + (i + 1)))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.print("VALUE: ");
      if (firebaseData.dataType() == "int")
        Serial.println(firebaseData.intData());
      else if (firebaseData.dataType() == "float")
        Serial.println(firebaseData.floatData());
      else if (firebaseData.dataType() == "boolean")
        Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
      else if (firebaseData.dataType() == "string")
        Serial.println(firebaseData.stringData());
      else if (firebaseData.dataType() == "json")
        Serial.println(firebaseData.jsonData());
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
  }

  Serial.println("------------------------------------");
  Serial.println("Push integer test...");

  for (uint8_t i = 0; i < 5; i++)
  {

    if (Firebase.pushInt(firebaseData, path + "/Push/Int", (i + 1)))
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
  }

  Serial.println("------------------------------------");
  Serial.println("Push JSON test...");

  for (uint8_t i = 5; i < 10; i++)
  {

    jsonStr = "{\"Data" + String(i + 1) + "\":" + String(i + 1) + "}";

    if (Firebase.pushJSON(firebaseData, path + "/Push/Int", jsonStr))
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
  }

  Serial.println("------------------------------------");
  Serial.println("Update test...");

  for (uint8_t i = 0; i < 5; i++)
  {

    jsonStr = "{\"Data" + String(i + 1) + "\":" + String(i + 5.5) + "}";

    if (Firebase.updateNode(firebaseData, path + "/Int", jsonStr))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.print("VALUE: ");
      if (firebaseData.dataType() == "int")
        Serial.println(firebaseData.intData());
      else if (firebaseData.dataType() == "float")
        Serial.println(firebaseData.floatData());
      else if (firebaseData.dataType() == "boolean")
        Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
      else if (firebaseData.dataType() == "string")
        Serial.println(firebaseData.stringData());
      else if (firebaseData.dataType() == "json")
        Serial.println(firebaseData.jsonData());
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
  }

  Serial.println("------------------------------------");
  Serial.println("Get JSON test...");
  if (Firebase.getJSON(firebaseData, path))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.print("VALUE: ");
    if (firebaseData.dataType() == "int")
      Serial.println(firebaseData.intData());
    else if (firebaseData.dataType() == "float")
      Serial.println(firebaseData.floatData());
    else if (firebaseData.dataType() == "boolean")
      Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
    else if (firebaseData.dataType() == "string")
      Serial.println(firebaseData.stringData());
    else if (firebaseData.dataType() == "json")
      Serial.println(firebaseData.jsonData());
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

  //Quit Firebase and release all resources
  Firebase.end(firebaseData);
}

void loop()
{

}
