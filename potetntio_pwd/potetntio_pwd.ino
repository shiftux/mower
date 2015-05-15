#include <Filters.h>

int ledPort = 13;
// filters out changes faster that 5 Hz.
float filterFrequency = 5.0;
// create a one pole (RC) lowpass filter
FilterOnePole lowpassFilter( LOWPASS, filterFrequency ); 

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = lowpassFilter.input( analogRead(A0));
  int divSensorValue = sensorValue / 4;
  // print out the value you read:
  Serial.println(divSensorValue);
  analogWrite(ledPort, divSensorValue);        
  // wait for 30 milliseconds to see the dimming effect    
  delay(30); 
}
