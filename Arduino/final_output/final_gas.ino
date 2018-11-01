#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>

//----- WiFi settings
const char *ssid = "2kminnn";
const char *password = "84vtjfcgi3a1b";
const char* mqtt_server = "iot.eclipse.org";
const char* mqtt_topic = "test_fognode"; 
const char* sub_topic = "f2a";
String check_gas="";
////////////////가스 감지 센서 변수///////////////////
#include "MQ135.h"//////////////////////////////////
#define ANALOGPIN A0   //  Define Analog PIN on Arduino Board
#define led_red_1 D1//////////////////////////////////
#define led_red_2 D2//////////////////////////////////
#define led_blue_1 D5//////////////////////////////////
#define led_blue_2 D6//////////////////////////////////
#define RZERO 206.85//  Define RZERO Calibration Value
MQ135 gasSensor = MQ135(ANALOGPIN);////////////////////
float ppm;////////////////////////////////////////////

WiFiClient espClient;
PubSubClient client(espClient);
char msg_gas[250];
int value = 0;
String message_gas;
#define USE_SERIAL Serial
int swit=1;
//최초 실행시 셋팅
void setup(){
/////////////가스감지센서/////////////////////////////
    pinMode(led_red_1, OUTPUT);
    pinMode(led_red_2, OUTPUT);
    pinMode(led_blue_1, OUTPUT);
    pinMode(led_blue_2, OUTPUT);
    float rzero = gasSensor.getRZero(); 
    pinMode(A0, INPUT);
    Serial.begin(9600);
    for(uint8_t t = 3; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
    //WiFi.mode(WIFI_STA);
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
    if (!client.connected()) { //wifi 연결을 지속적으로 확인
        reconnect();
    }
    //가스 감지 센서
    gas_func();
    convert_json(); 
    ++value; 
    //가스 감지에 대한 메시지 발행.
    client.publish(mqtt_topic,msg_gas);
    swit = client.subscribe(sub_topic);
    
    //이상치 감지시 fognode에서 보낸 topic 수신 및 사이렌 알림
    if(swit){ 
      Serial.print("Publish message: \n");
      Serial.println(msg_gas);   
      if(check_gas.equals("gas_ppm")){
        led_siren();
      }
    } 
    client.loop();
    delay(1000);
}

//구독한 topic 수신
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    String msgText = "";
    
    for (int i = 0; i < length; i++) {
      //Serial.print((char)payload[i]);
      msgText += (char)payload[i];
    }
    check_gas = msgText;
}

// wifi 재연결
void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP8266Client")) {
            Serial.println("connected");
            // Once connected, publish an announcement...  
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

//gas 감지센서로 가스 수치 읽어옴.
void gas_func(){
  ppm = gasSensor.getPPM();
}

//읽어온 가스 수치 json형태로 변환
void convert_json() {
  message_gas = "gas_ppm:";
  message_gas += ppm;
  message_gas += "\n";
  message_gas.toCharArray(msg_gas,message_gas.length()+1);
  // publish message
  //Serial.println("Let's publish message now!");
  //mqtt.publish("home/thirdroom/temp_humi", message, true); // retained message
  // ......
} 

//이상 발생 시 siren 점등
void led_siren(){
    digitalWrite(led_red_1, HIGH);
    digitalWrite(led_red_2, HIGH);
    delay(150);
    digitalWrite(led_red_1, LOW);
    digitalWrite(led_red_2, LOW);
    
    digitalWrite(led_blue_1, HIGH);
    digitalWrite(led_blue_2, HIGH);
    delay(150);
    digitalWrite(led_blue_1, LOW);
    digitalWrite(led_blue_2, LOW);
}
