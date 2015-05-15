#include <Servo.h>

Servo esc;  // create servo object to control a servo

int val = 0;    // variable to read the value from the analog pin
int servopin = 10;
int escMax = 75;
int escMin = 50;
String readString;

void setup()
{
  esc.attach(servopin);  // attaches the servo on the servopin to the servo object
  Serial.begin(9600);        // initialize serial communication at 9600 bits per second:
  initESC();
}

void loop()
{
  esc.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there

  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() >0) {
    Serial.println("readString = " + readString);  //so you can see the captured string 
    delay(2);
    val = readString.toInt();
    val = trimSignal(val);
    delay(2);
    Serial.print("val = ");
    Serial.println(val, DEC);
    readString = "";
  }
}

void initESC()
{
  Serial.println("initiating ESC");
  Serial.println("throttle 0");
  esc.write(0);
  delay(2000);
  Serial.println("throttle 179");
  esc.write(179);
  delay(3000);
  Serial.println("throttle Min");
  esc.write(escMin);
  delay(8000);
  val = escMin;
  Serial.println("ESC initiated");
}

int trimSignal(int inputSignal) {
  if (inputSignal > escMax) {
    inputSignal = escMax;
  }
  else if (inputSignal < escMin) {
    inputSignal = escMin;
  }
  return inputSignal;
}

