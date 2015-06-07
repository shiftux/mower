#ifndef usSensor_h
#define usSensor_h

#include <NewPing.h>

#define MAX_DISTANCE 200

class usSensor{

  public:
    usSensor(int tp, int ep);
    unsigned int get_distance();

  private:
     int TRIGGER_PIN;
     int ECHO_PIN;
     NewPing sonar;

};

#endif
