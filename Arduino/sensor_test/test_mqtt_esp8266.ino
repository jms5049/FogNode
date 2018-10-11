#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <SPI.h>
#include <Wire.h>

//----- OLED display



//----- WiFi settings
const char *ssid = "2kminnn";
const char *password = "84vtjfcgi3a1b";
const char* mqtt_server = "test.mosquitto.org";
const char* mqtt_topic = "test_fognode";
char* mqtt_message = "Hello world #%ld";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

#define USE_SERIAL Serial


void setup() {
   
    
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
}


void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
  
    long now = millis();
    long randNumber = random(0, 15000);
    if (now - lastMsg > 15000 + randNumber) {
        lastMsg = now;
        ++value;
        snprintf (msg, 75, mqtt_message, value);
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish(mqtt_topic, msg);
  
    }
}


void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");


    String msgText = "=> ";
    
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      msgText += (char)payload[i];
    }
    Serial.println();
  
}


void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP8266Client")) {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish(mqtt_topic, "hello world");
            // ... and resubscribe
            client.subscribe(mqtt_topic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

