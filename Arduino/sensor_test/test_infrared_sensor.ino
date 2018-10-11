#define infrared_pin D2
#define led_infrared 10
void setup() {
  
  
  
  pinMode(infrared_pin, INPUT);
  
  pinMode(led_infrared, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  int state = digitalRead(infrared_pin);

  Serial.print("Infrared = ");
  Serial.println(state);

  if(state == 0){
    digitalWrite(led_infrared, HIGH);
    Serial.println("Warning");
  }

  else{
    digitalWrite(led_infrared, LOW);
    Serial.println("Safe");
  }
  delay(1000);
}
