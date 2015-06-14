/***********************
* NOTE:
* Forward sensor is fixed to 10cm, readout is deactivated!
* Serial output is still enabled and printing
* avoidanc manoeuvre only lights a led
* move only outputs sound so far
* motor movement speed has to be defined
* init est is commented, it seems the esc controller stays initiated...
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
  //activateInterrupt();
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
      stop_movement();
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
  pinMode(MOTOR_LEFT_PWM,     OUTPUT);
  pinMode(MOTOR_RIGHT_PWM,    OUTPUT);
  pinMode(MOTOR_LEFT_BRAKE,   OUTPUT);
  pinMode(MOTOR_RIGHT_BRAKE,  OUTPUT);
}

//void activateInterrupt(){
//  attachInterrupt(CUT_SWITCH, cutSwitch, CHANGE);
//}

/****************/
// Timing
boolean intervalReached(){
  if (millis() - previousTime > INTERVAL) { return true; }
  else { return false; }
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
  readCutSwitch();
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
  if (dist_L <= SONAR_OBSTACLE_DISTANCE || dist_F <= SONAR_OBSTACLE_DISTANCE || dist_R <= SONAR_OBSTACLE_DISTANCE) {
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
  releaseMotorBrakes();
  setMovementDirection(BOTH, "forward");
  setForwardSpeed();
}

void stop_movement(){
  engageMotorBrakes();
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

void releaseMotorBrakes(){
  digitalWrite(MOTOR_LEFT_BRAKE, LOW);
  digitalWrite(MOTOR_RIGHT_BRAKE, LOW);
}

void engageMotorBrakes(){
  digitalWrite(MOTOR_LEFT_BRAKE, HIGH);
  digitalWrite(MOTOR_RIGHT_BRAKE, HIGH);
}

void setForwardSpeed(){
  analogWrite(MOTOR_LEFT_PWM, FORWARD_SPEED);
  analogWrite(MOTOR_RIGHT_PWM, FORWARD_SPEED);
}

void setMovementDirection(int motor, String direction){
  uint8_t value;
  if (direction == "forward") {value = HIGH; }
  else {value = LOW; }
  switch (motor){
    case BOTH:
    digitalWrite(MOTOR_LEFT_DIR, value);
    digitalWrite(MOTOR_RIGHT_DIR, value);
    break;
    case LEFT:
    digitalWrite(MOTOR_LEFT_DIR, value);
    break;
    case RIGHT:
    digitalWrite(MOTOR_RIGHT_DIR, value);
    break;
  }
}

/****************/
// Cutting
void setupCutting(){
  esc.attach(ESC_PORT);
  //initESC();
}

void cut(){
  if ( !stopCut ){ esc.write(ESC_MAX); }
  else { stopCutting(); }
}

void stopCutting(){
  esc.write(ESC_MIN);
}

void readCutSwitch(){
  if ( digitalRead(CUT_SWITCH) == HIGH ) {
    Serial.println("cut switch is high, cutting");
    stopCut = false;
  }
  else {
    stopCut = true;
    Serial.println("cut switch is low, no cut");
    stopCutting();
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
