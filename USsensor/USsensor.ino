
#include <NewPing.h>

#define TRIGGER_PIN_1  42  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_1     41  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_2  32  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_2     31  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define LED_PIN      13

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS1 = sonar1.ping_cm(); // Send ping, get ping time in microseconds (uS).
  unsigned int uS2 = sonar2.ping_cm(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS1);
  Serial.print("  //  ");  
  Serial.print(uS2);
  //Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println(" cm");
  if (uS1 <= 3 || uS2 <= 3) { digitalWrite(LED_PIN, HIGH);  }
  else { digitalWrite(LED_PIN, LOW); }
}


