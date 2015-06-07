// pins
#define TRIGGER_PIN_L     22  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_L        23  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_F     24
#define ECHO_PIN_F        25
#define TRIGGER_PIN_R     26
#define ECHO_PIN_R        27
#define LED_PIN           13
#define CUT_SWITCH        XXXX
#define OBSTACLE_SWITCH_L XXXXX
#define OBSTACLE_SWITCH_F XXXXX
#define OBSTACLE_SWITCH_R XXXXX
#define ESC_PIN           XXXXX

// definitions
#define MAX_DISTANCE 200 // Maximum sonar distance to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define INTERVAL     100 // intervall between sensor readouts in ms
#define ESC_MAX      75  // ESC cut motôr control Max and Min Speeds
#define ESC_MIN      50
