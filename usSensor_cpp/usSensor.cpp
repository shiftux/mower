#include "usSensor.h"

// constructor
usSensor::usSensor(int tp, int ep) : ECHO_PIN(ep), TRIGGER_PIN(tp) {
   sonar = NewPing(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
}

unsigned int usSensor::get_distance(){
  return sonar.ping_cm();
}
