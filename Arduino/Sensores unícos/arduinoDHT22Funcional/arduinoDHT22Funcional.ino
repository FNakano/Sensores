#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int chk;
float umidade;
float temp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  umidade = dht.readHumidity();
  temp = dht.readTemperature();

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.print(" %, Temperatura: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  delay(1000); //Delay 2 sec.
}
