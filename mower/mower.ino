/***********************
* NOTE:
* Forward sensor is fixed to 10cm, readout is deactivated!
* Serial output is still enabled and printing
* avoidanc manoeuvre only lights a led
* move and cut are empty functions for now
* cut_switch and obstacle_switch pins are not defined
* init ESC is commented to save time
***********************/

// includes
#include "mower.h"
#include <NewPing.h>
#include <Servo.h>

// variables
unsigned long previousTime = 0;
boolean avoidanceManoeuvre = false;
boolean stopCut = true;

// objects
NewPing sonarL(TRIGGER_PIN_L, ECHO_PIN_L, MAX_DISTANCE); // NewPing sonar setup of pins and maximum distance.
NewPing sonarF(TRIGGER_PIN_F, ECHO_PIN_F, MAX_DISTANCE);
NewPing sonarR(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE);
Servo esc;  // create servo object to control a servo

/*********************
* Main Functions
*********************/

// setup routine
void setup() {
  pinSetup();
  ativateInterrupt();
  Serial.begin(9600);         // Open serial monitor to have USB debug
  setupCutting();
}

// main loop
void loop() {
  if ( !avoidanceManoeuvre ) {
    if ( intervalReached() ) {
      readSensors();
      resetInterval();
    }
    move();
    cut();
  }
  else {
    while ( avoidanceManoeuvre ) {
      executeAvoidanceManoeuvre();
    }
  }
  overflowSafety();
} // main loop


/*********************
* Aid Functions
*********************/

/****************/
// pins
void pinSetup(){
  pinMode(LED_PIN,            OUTPUT);
  pinMode(OBSTACLE_SWITCH_L,  INPUT);
  pinMode(OBSTACLE_SWITCH_F,  INPUT);
  pinMode(OBSTACLE_SWITCH_R,  INPUT);
}

void activateInterrupt(){
  attachInterrupt(CUT_SWITCH, cutSwitch, CHANGE);
}

/****************/
// Timing
boolean intervalReached(){
  if (millis() - previousTime > INTERVAL) { return true }
  else { return false }
}

void resetInterval(){
  previousTime = millis();
}

void overflowSafety(){
  if ( millis() - previousTime >= 5 * INTERVAL ) {
    previousTime = millis();
  }
}

/****************/
// Sensors
void readSensors(){
  readUSsensor();
  readObstacleSwitches();
}

void readUSsensor(){
  unsigned int dist_L = sonarL.ping_cm(); // Send ping, get distance in cm
  unsigned int dist_F = 10;//sonarF.ping_cm();
  unsigned int dist_R = sonarR.ping_cm();
  Serial.print("Ping: ");
  Serial.print(dist_L);
  Serial.print("  //  ");
  Serial.print(dist_F);
  Serial.print("  //  ");
  Serial.print(dist_R);
  Serial.println(" cm");
  if (dist_L <= 3 || dist_F <= 3 || dist_R <= 3) {
    doAvoidance();
  }
} // readUSsensor

void readObstacleSwitches(){
  int osr = digitalRead(OBSTACLE_SWITCH_R);
  int osf = digitalRead(OBSTACLE_SWITCH_F);
  int osl = digitalRead(OBSTACLE_SWITCH_L);
  if (osr == HIGH || osf == HIGH || osl == HIGH ) {
    doAvoidance();
  }
}

/****************/
// Movement
void move(){
}

void doAvoidance(){
  avoidanceManoeuvre = true;
}

void resetAvoidance(){
  avoidanceManoeuvre = false;
}

void executeAvoidanceManoeuvre(){
  digitalWrite(LED_PIN, HIGH);
  delay(2000);
  digitalWrite(LED_PIN, LOW);
  resetAvoidance();
}

/****************/
// Cutting
void setupCutting(){
  esc.attach(ESC_PIN);
  // initESC();
}

void cut(){
  if ( !stopCut ){ esc.write(ESC_MAX) }
  else { stopCut() }
}

void stopCut(){
  esc.write(ESC_MIN);
}

void cutSwitch(){
  if ( digitalRead(CUT_SWITCH) == HIGH ) {
    stopCut = false;
  }
  else {
    stopCut = true;
    stopCut();
  }
}

void initESC() {
  Serial.println("initiating ESC");
  Serial.println("throttle 0");
  esc.write(0);
  delay(2000);
  Serial.println("throttle 179");
  esc.write(179);
  delay(3000);
  Serial.println("throttle Min");
  esc.write(ESC_MIN);
  delay(8000);
  Serial.println("ESC initiated");
  stopCut = false;
}