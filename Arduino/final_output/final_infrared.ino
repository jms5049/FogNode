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
String check_infrared="";

////////////// 피에조 부저/////////////////////
#define piezo D5
#define PI 3.141592
float sinVal; //정현파 값 저장
int toneVal; //경보음 발생을 위한 값 저장

////////////////장애물 감지센서 변수/////////////////////
#define infrared_pin D2///////////////////////////////////
#define led_red_1 D0//////////////////////////////////
#define led_red_2 D1//////////////////////////////////
#define led_blue_1 D5//////////////////////////////////
#define led_blue_2 D6//////////////////////////////////
int infrared_state;////////////////////////////////////// 
float infrared_value;
int swit=1;


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[250];
int value = 0;
String message;
#define USE_SERIAL Serial

//초기실행 시 설정
void setup(){
    pinMode(piezo, OUTPUT);
///////////////////////장애물 감지센서///////////////////
    pinMode(infrared_pin, INPUT);
    //pinMode(led_infrared, OUTPUT);
    //USE_SERIAL.begin(921600);
    USE_SERIAL.begin(115200);
    USE_SERIAL.setDebugOutput(true);
    USE_SERIAL.println();


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
    //감지센서 함수
    infrared_func();
    convert_json();
    
    client.publish(mqtt_topic, msg); 
    delay(100); 
    ++value;
    swit = client.subscribe(sub_topic);
    Serial.print("swithch number: ");
    Serial.println(swit);
    //움직임이 감지되었을 경우
    if(swit){
        Serial.print("Publish message: \n");
        Serial.println(msg);   
      if(check_infrared.equals("infrared_state")&&infrared_state==0.0){
        analogWrite(piezo, 64);
        delay(100);
        noTone(piezo); 

        }
    }
    else{
      Serial.print("FAIL CONNECT");
      
    }
    client.loop();
    delay(500);
}

//구독한 메시지 수신
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    String msgText = "";
    
    for (int i = 0; i < length; i++) {
      //Serial.print((char)payload[i]);
      msgText += (char)payload[i];
    }
    check_infrared = msgText; 
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


//움직임 감지 센서 함수
void infrared_func(){
  infrared_state = digitalRead(infrared_pin);
  if(infrared_state){
    infrared_value=0.0; 
  }
  else{
    infrared_value=1.0;
  }
}

//json으로 값 변환
void convert_json() {

  message = "infrared_state:";
  message += infrared_value;
  message += "\n";
  message.toCharArray(msg,message.length()+1);
  // publish message
  //Serial.println("Let's publish message now!");
  //mqtt.publish("home/thirdroom/temp_humi", message, true); // retained message
  // ......
} 
//움직임 감지 시 led점등
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
//움직임 감지 시 사운드 
void playTone(long duration, int freq) {
  duration *= 1000;
  int period = (1.0 / freq) * 1000000;
  long elapsed_time = 0;
  while (elapsed_time < duration) {
    digitalWrite(piezo,HIGH);
    delayMicroseconds(period / 2);
    digitalWrite(piezo, LOW);
    delayMicroseconds(period / 2);
    elapsed_time += (period);
  }
}
