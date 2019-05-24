#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>

//BMP280
#include <Adafruit_BMP280.h>

// Set these to run example.
#define FIREBASE_HOST "nomedohost.firebaseio.com"
#define FIREBASE_AUTH "segredo-database"
#define WIFI_SSID "Nome wifi"
#define WIFI_PASSWORD "senha wifi"

//BMP280
Adafruit_BMP280 bme; // I2C

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conectando");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("conectado: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //BMP280
  Serial.println(F("BMP280 test"));
  if (!bme.begin()) { 
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}
void loop() {
  int sensorValue = analogRead(A0);   // Ler o pino Analógico A0 onde está o LDR
  float voltagem = sensorValue * (3.3 / 1024.0);   // Converter a leitura analógica (que vai de 0 - 1023) para uma voltagem (0 - 3.3V), quanto de acordo com a intensidade de luz no LDR a voltagem diminui.
  
  //Configura o Buffer
  const int capacity = JSON_OBJECT_SIZE(20);
  StaticJsonBuffer<capacity> jb;
  // Cria o JsonObject
  JsonObject& obj = jb.createObject();
  
  obj["LDR"] = voltagem;
  obj["PRESSAOBMP"] = bme.readPressure();
  obj["TEMPBMP"] = bme.readTemperature();

  Firebase.push(WiFi.macAddress(), obj);
  delay(5000); // Espera 5 segundos
}
