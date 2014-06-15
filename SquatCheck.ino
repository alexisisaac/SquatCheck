#include <NewPing.h>

#define POWER_LED 11
#define LASER 2
      
#define SENSOR_POWER_PIN 9
#define TRIGGER_PIN  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

enum State {
  STATE_SETUP, 
  STATE_LOOP
};

#define TONE_LOW 3
#define TONE_MID 2
#define TONE_HIGH 1
#define TONE_CLICK 0

State state;

unsigned int ref;
unsigned int count;
unsigned long lastClick;
boolean previousPosition;

void setup(){
  state = STATE_SETUP;
  pinMode(POWER_LED, OUTPUT);
  pinMode(LASER, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(SENSOR_POWER_PIN, OUTPUT);
  digitalWrite(SENSOR_POWER_PIN, HIGH);
  digitalWrite(POWER_LED, HIGH);
  beep(TONE_LOW,120);
  beep(TONE_HIGH,80);
  ref = 0;
  count = 0;
  lastClick = 0;
}
void loop(){
  float cm = sonar.convert_mm(sonar.ping_median())/10.0f;
  switch(state){
      case STATE_SETUP:
        digitalWrite(POWER_LED, (millis()/100)%2!=0);
        if(cm>10 && cm<150){
          if(abs(ref-cm)<2){
            count++;
          } else {
            count = 0;
          }
          if (count==5){
            state = STATE_LOOP;  
            beep(TONE_MID,120);  
            beep(TONE_LOW,80);  
            beep(TONE_MID,120);  
            beep(TONE_LOW,80);  
            beep(TONE_HIGH,120);
          }
          ref = cm;
        }
        break;
      case STATE_LOOP:
        analogWrite(POWER_LED, map(cm, 0, 200, 0, 255));
        if(cm<ref&&cm>2){
          digitalWrite(LASER, HIGH);
          if(!previousPosition){
              beep(TONE_MID,120);  
          }
        } else {
          
          if(cm>ref && (cm-ref)<50 && millis()>lastClick+(cm-ref)*20){
              lastClick = millis();
              digitalWrite(LASER, HIGH);
              beep(TONE_CLICK,0);
              delay(10);
              digitalWrite(LASER, LOW);
          }       
          digitalWrite(LASER, LOW);
        }
        previousPosition = cm<ref&&cm>2;
        break;
    
  }
  delay(10);
}


void beep(unsigned int tone, unsigned long time){
 time = time+millis();
  if (tone!=TONE_CLICK){
    while(millis()<time){
      digitalWrite(8, HIGH);
      delay(tone);
      digitalWrite(8, LOW);
      delay(tone);
    }
  } else {
    digitalWrite(8, HIGH);
    delay(10);
    digitalWrite(8, LOW);
  }
}


