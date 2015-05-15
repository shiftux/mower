
int ledPin = 50;                 // LED connected to digital pin 13
int sensorPin = A0;

void setup()
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  pinMode(48, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(ledPin, HIGH);   // sets the LED on
  digitalWrite(48, HIGH);
  Serial.write("\nled is on\n");
  Serial.write("input value is ");
  Serial.print(analogRead(sensorPin), DEC);  
  delay(1000);                  // waits for a second
  digitalWrite(ledPin, LOW);    // sets the LED off
  digitalWrite(48, LOW);
  Serial.write("\nled is off\n");
  Serial.write("input value is ");
  Serial.print(analogRead(sensorPin), DEC);  
  delay(1000);                  // waits for a second
}

