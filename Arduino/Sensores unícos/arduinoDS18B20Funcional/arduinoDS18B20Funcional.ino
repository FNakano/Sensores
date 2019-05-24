//Importamos as livrarias necessarias para a leitura do sensor
#include  <OneWire.h>
#include <DallasTemperature.h>
 
//Declaramos o pino onde se vai ligar o cabo DATA do sensor
#define Pin 2
 
//Declaramos o pino como bus para a comunicação OneWire
OneWire ourWire(Pin);
 
//Iniciamos 1 instancia da livraria DallasTemperature
DallasTemperature sensors(&ourWire);
 
//Esta função executa-se quando se inicia o Arduino
void setup() {
//Iniciamos a comunicação serial
Serial.begin(9600);
//Iniciamos o sensor
sensors.begin();
//Pequena pausa
delay(1000);
}
 
//Esta função executa-se continuamente em laço
void loop() {
//Enviamos uma petição ao sensor para que nos devolva a temperatura
sensors.requestTemperatures();
//Lê-se e imprime a temperatura em graus Celsius no monitor serie
Serial.print(sensors.getTempCByIndex(0));
Serial.println(" graus Centigrados");
//Lê-se e imprime a temperatura em graus Farenheith no monitor serie
Serial.print(sensors.getTempFByIndex(0)); //Lê-se e imprime a temperatura en graus Fahrenheit
Serial.println(" graus Fahrenheit");
//Pequena pausa de 1 segundo antes da próxima leitura
delay(1000);
}
