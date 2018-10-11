#include "DHT.h"
#include <ArduinoJson.h>

#define DHTPIN 2     // data pin to DHT22
#define DHTTYPE DHT22   // using DHT 22
#define led_dht 8
int motor = 5;
DHT dht(DHTPIN, DHTTYPE);
float hum;
float tmp;

void setup() {
  pinMode(motor, OUTPUT);
  //Serial.begin(9600);
  //온습도
  dht.begin();
  pinMode(led_dht,OUTPUT);


  
  Serial.begin(9600);
}
void loop() {
  hum = dht.readHumidity();
  tmp = dht.readTemperature();

  json_tmp_hum();
  
  if (isnan(tmp) || isnan(hum)) {
    Serial.println("Reading error..");
  }
  if(tmp>31) {
    digitalWrite(motor, HIGH);
  }
  
  else {
  
    digitalWrite(motor, LOW);
  }
  delay(3000);
}

void json_tmp_hum() {
  String jsondata = "";
  
  //jsonbuffer 생성
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  //"key" & value
  root["tempvalue"] = tmp; 
  root["humivalue"] = hum;

  root.printTo(jsondata);
  Serial.println(jsondata);
}
