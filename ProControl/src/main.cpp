#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin 2
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// #define LED D4
DHT dht(dht_dpin, DHTTYPE);

const char *ssid = "NET++";
const char *password = "gilmen0102";
int lamp1 = 5;
int lamp2 = 4;

ESP8266WebServer server(80);
float humidity, temp;
String value = "";
unsigned long previousMillis = 0;
const long interval = 2000;
void getdatas();
void setup()
{
  Serial.begin(9600);
  dht.begin();

  pinMode(lamp1, OUTPUT);
  digitalWrite(lamp1, LOW);
  pinMode(lamp2, OUTPUT);
  digitalWrite(lamp2, LOW);

  Serial.println("Sensor Teste...");
  WiFi.begin(ssid, password);
  while(WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.print("NodeMCU conectado no IP: ");
    Serial.println (WiFi.localIP());
    Serial.print("Conexão efetuada com sucesso!!!");

    server.begin();
    Serial.println("Webserver inicializado");
    delay(500);
    Serial.println("Acesse o endereço pelo: ");
    Serial.println (WiFi.localIP());

     server.on("/", [](){
      server.send(200, "cabeçalho da requisição", "BEM VINDO AO SERVIDOR DO NODEmcu" );
    });

    server.on("/onlamp1", [] (){
      server.send(200, "cabeçalho", "lamp1 acesa");
      digitalWrite(lamp1, HIGH);
      delay(1000);      
      });

    server.on("/offlamp1", [] (){
      server.send(200, "cabeçalho", "Lamp1 apagada");
      digitalWrite(lamp1, LOW);
      delay(1000);      
      });

    server.on("/onlamp2", [] (){
      server.send(200, "cabeçalho", "Lamp2 acesa");
      digitalWrite(lamp2, HIGH);
      delay(1000);      
      });

    server.on("/offlamp2", [] (){
      server.send(200, "cabeçalho", "Lamp2 apagada");
      digitalWrite(lamp2, LOW);
      delay(1000);      
      });

    server.on("/dht11/temp", [](){
      getdatas();
      value = String((int) temp);
      server.send(200, "cabeçalho", value);
      });

     server.on("/dht11/humi", [](){
      getdatas();
      value = String((int) humidity);
      server.send(200, "cabeçalho", value);
      });


    
}


void loop()
{
  server.handleClient(); 
}

void getdatas(){

      unsigned long currentMillis = millis();

      if(currentMillis - previousMillis >= interval){
        previousMillis = currentMillis;
      
        temp = dht.readTemperature();
        humidity = dht.readHumidity();

         if(isnan (temp) || (humidity)){

        Serial.println("Falha na leitura do sensor!!!");

        return;                
        }
      }
  }