/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_AUTH_TOKEN    "<TOKEN>"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <Stepper.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hotspot";
char pass[] = "123456789";

BlynkTimer timer;
const int stepsPerRevolution = 500;
int inputSteps = 0;
int reverseMotor = 1;
Stepper myStepper(stepsPerRevolution,D0,D1,D2,D3);
int pinValue = 0;
boolean pinChanged = false;


void moveMotor(){
 if(pinChanged){
    Serial.println(pinValue);
    if(pinValue == 1){
      myStepper.step(-inputSteps * reverseMotor);
      delay(200);
      myStepper.step(inputSteps * reverseMotor);
      Blynk.virtualWrite(V1, LOW);
    }
    pinChanged = false;
  }
  
}
void setup(){
  // Debug console
  Serial.begin(9600);
  myStepper.setSpeed(60);
  pinMode(BUILTIN_LED, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10, moveMotor);
  
  // You can also specify server:
  // Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8080);
  // Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

BLYNK_WRITE(V1){
   pinValue = param.asInt();
   //Serial.println(pinValue);
   pinChanged = true;
}

BLYNK_WRITE(V2){
  pinValue = param.asInt();
  inputSteps = pinValue;
  Serial.println(inputSteps);
}

BLYNK_WRITE(V3){
  pinValue = param.asInt();
  reverseMotor = pinValue;
}


BLYNK_APP_CONNECTED() {
  Serial.println("phone connected");
}


void loop(){
  digitalWrite(BUILTIN_LED, HIGH);
  Blynk.run();
  timer.run();
}
  
