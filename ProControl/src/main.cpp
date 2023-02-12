#include <Arduino.h>
#define LED D4

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Teste porta");
}

void loop() {
  Serial.println("Teste pino da placa");
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
}