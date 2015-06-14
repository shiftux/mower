int val = 0;    // variable to read the value from the analog pin
int soundPort = 7;
String readString;

void setup()
{
  Serial.begin(9600);        // initialize serial communication at 9600 bits per second:
}

void loop()
{
  analogWrite(soundPort, val);
  delay(15);                           

  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() >0) {
    Serial.println("readString = " + readString);  //so you can see the captured string
    delay(2);
    val = readString.toInt();
    delay(2);
    Serial.print("val = ");
    Serial.println(val, DEC);
    readString = "";
  }
}
