#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6bWoft7-b"
#define BLYNK_TEMPLATE_NAME "Smart Home"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Add Blynk authentication token here
char auth[] = "";

// Wi-Fi credentials here
char ssid[] = "";
char pass[] = "";

String inputString = "";  
bool stringComplete = false;  
int mq7Value = 0; 


#define DHTPIN 2    
#define DHTTYPE DHT11 


#define PIR_PIN 5      


#define MQ7_PIN A0

int threshold = 300;

#define LED_PIN D2     
#define LDR_PIN A0      
#define GAS_SENSOR_PIN A0 

DHT dht(DHTPIN, DHTTYPE);


float temperature;
float humidity;

bool motionDetected = false;

int ldrValue;
int pirState;
int gasLevel;

void setup() {

  Serial.begin(9600);
  

  Blynk.begin(auth, ssid, pass);
  
  dht.begin();
  inputString.reserve(200); 

  pinMode(PIR_PIN, INPUT);


  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);

}


void loop() {

  Blynk.run();

  Serial.println("Hello from ESP8266"); 
  
 
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  temperature += 3;
  
  ldrValue = analogRead(LDR_PIN);
  
  pirState = digitalRead(PIR_PIN);
  
  gasLevel = analogRead(GAS_SENSOR_PIN);

  // Send sensor data to Blynk app
  Blynk.virtualWrite(V5, temperature);
  Blynk.virtualWrite(V6, humidity);
  Blynk.virtualWrite(V7, ldrValue);
  Blynk.virtualWrite(V8, pirState);
  Blynk.virtualWrite(V9, gasLevel);



    if (digitalRead(PIR_PIN) == HIGH && !motionDetected) {
    motionDetected = true;
    Serial.println("Motion detected!");
    Blynk.logEvent("motion_detected");  // Log event to Blynk app
  } else if (digitalRead(PIR_PIN) == LOW && motionDetected) {
    motionDetected = false;
    Serial.println("Motion ended.");
  }

int mq7Value = analogRead(MQ7_PIN);


  Blynk.virtualWrite(V1, mq7Value);
  // Serial.println(mq7Value);

  if (mq7Value > threshold) {
    Blynk.logEvent("smoke_detected");
  }

while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }


  if (stringComplete) {
    mq7Value = inputString.toInt();
    Serial.println("Received MQ-7 Value: " + String(mq7Value));

    Blynk.virtualWrite(V1, mq7Value); 

    inputString = "";
    stringComplete = false;
  }

  delay(1000);

  if (ldrValue < 500) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

}