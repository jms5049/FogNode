#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>

//----- WiFi settings
//const char *ssid = "ProBrain_5G";
//const char *password = "cse54020325!";

const char *ssid = "2kminnn";
const char *password = "84vtjfcgi3a1b";
const char* mqtt_server = "iot.eclipse.org";
const char* mqtt_topic = "test_fognode";
const char* sub_topic = "f2a";
String check_tmp="";
int swit=1;
//////////////////////온습도센서 변수///////////////////
#include "DHT.h"///////////////////////////////////////
#define DHTPIN D1 ////////////////////////////////////////
#define DHTTYPE DHT22///////////////////////////////////
#define LED_fan D6////////////////////////////////////////
DHT dht(DHTPIN, DHTTYPE);//////////////////////////////
float hum;/////////////////////////////////////////////
float tmp;/////////////////////////////////////////////

//////////////사이렌 및 전구 /////////////////////////
#define led_red_1 D0//////////////////////////////////
#define led_red_2 D5//////////////////////////////////
#define led_blue_1 D2//////////////////////////////////
#define led_blue_2 D6//////////////////////////////////
 
WiFiClient espClient;
PubSubClient client(espClient); 
char msg_tmp[50];
char msg_hum[50];

int value = 0;
String message_tmp;
String message_hum;
#define USE_SERIAL Serial

void setup(){  
//////////////////////온습도 센서/////////////////////
    dht.begin();
    Serial.begin(115200);
    pinMode(led_red_1, OUTPUT);
    pinMode(led_red_2, OUTPUT);
    pinMode(led_blue_1, OUTPUT);
    pinMode(led_blue_2, OUTPUT);
    
    for(uint8_t t = 3; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.begin(ssid, password);

    Serial.print("Connecting to AP");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    
    randomSeed(analogRead(0));
}


void loop() {
    if (!client.connected()) {
        reconnect();
    }
    //온습도 감지
    dht_func();
    delay(100);
    convert_json();
    ++value;
    //메시지 발행.
    client.publish(mqtt_topic, msg_tmp);
    delay(200);
    //메시지 구독.
    client.publish(mqtt_topic, msg_hum);
    swit = client.subscribe(sub_topic);
    
    //publish한 메시지 출력.
    if(swit){
      Serial.println("\n<<<publish message>>>");
      Serial.print(msg_tmp);
      Serial.print(msg_hum);
      if(check_tmp.equals("temperature")){ 
        digitalWrite(led_red_2, HIGH);
      }
    }
    else{
      Serial.print("fail subscribe");
    }
    Serial.print("\n=====================");
    client.loop();
    delay(1000);
}

//온습도 센서
void dht_func(){
  hum = dht.readHumidity();
  tmp = dht.readTemperature();
  if (isnan(tmp) || isnan(hum)) {
    Serial.println("Reading error..");
  } 
}

//값 json 변환
void convert_json() {
  message_tmp = "temperature:";
  message_tmp += tmp;
  message_tmp += "\n";
  message_hum = "humidity:";
  message_hum += hum;
  message_hum += "\n";
  message_tmp.toCharArray(msg_tmp,message_tmp.length()+1);
  message_hum.toCharArray(msg_hum,message_hum.length()+1);
} 

//메시지 구독
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] :  ");

    String msgText = "";
    
    for (int i = 0; i < length; i++) {
      //Serial.print((char)payload[i]);
      msgText += (char)payload[i];
    }
    check_tmp = msgText;
    Serial.println(msgText);
}
//wifi 재연결
void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP8266Client")) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
} 

//void led_siren(){
//    digitalWrite(led_red_1, HIGH);
//    digitalWrite(led_red_2, HIGH);
//    delay(150);
//    digitalWrite(led_red_1, LOW);
//    digitalWrite(led_red_2, LOW);
//    
//    digitalWrite(led_blue_1, HIGH);
//    digitalWrite(led_blue_2, HIGH);
//    delay(150);
//    digitalWrite(led_blue_1, LOW);
//    digitalWrite(led_blue_2, LOW);
//
//}

