//www.elegoo.com
//2016.12.08

// ON/OFF Switch
const int buttonPin = 8;    // the number of the pushbutton pin
bool ON = false;         // the current state of the output pin (initially OFF)
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Ultrasonic Sensor
#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long distance;

// DC Motor
#define ENABLE 5
#define DIRA 3
#define DIRB 4
int i;

void setup() {

  // ON/OFF Switch
  pinMode(buttonPin, INPUT);
  
  // Set DC Motor Pin Direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  
  // Serial Monitor
  Serial.begin(9600);
  delay(1000);
}

void loop() {

  // Detect ON/OFF button press
  checkForButtonPress();

  if (ON) {
    
    // Collect & record distance measure
    distance = sr04.Distance();
//    Serial.print(a);
//    Serial.println("cm");
//    delay(10);

    // Turn on motor if closer than 10cm
    if (distance < 10) {
      // Turn the motor on
      digitalWrite(ENABLE,255); // enable full speed
      digitalWrite(DIRA,HIGH); //one way
      digitalWrite(DIRB,LOW);
    } else {
      digitalWrite(ENABLE,LOW); // then stops
    }
  }
}

void checkForButtonPress() {
  
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        ON = !ON; // Switch the ON/OFF state
      }
    }
  }
  
  lastButtonState = reading;
}
