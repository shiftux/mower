// pins
#define TRIGGER_PIN_L     22  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_L        23  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_F     24
#define ECHO_PIN_F        25
#define TRIGGER_PIN_R     26
#define ECHO_PIN_R        27
#define LED_PIN           13
#define CUT_SWITCH        36
#define OBSTACLE_SWITCH_L 30
#define OBSTACLE_SWITCH_F 31
#define OBSTACLE_SWITCH_R 32
#define ESC_PORT          4
#define MOTOR_LEFT_DIR    12  // Motor A direction
#define MOTOR_RIGHT_DIR   13  // Motor B direction
#define MOTOR_LEFT_BRAKE  9   // Brake Motor A
#define MOTOR_RIGHT_BRAKE 8   // Brake Motor B
#define MOTOR_LEFT_PWM    3   // Motor A PWM signal
#define MOTOR_RIGHT_PWM   11  // Motor B PWM signal

// definitions
#define MAX_DISTANCE            200 // Maximum sonar distance to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define INTERVAL                100 // intervall between sensor readouts in ms
#define ESC_MAX                 75  // ESC cut motôr control Max and Min Speeds
#define ESC_MIN                 50
#define SONAR_OBSTACLE_DISTANCE 4   // in cm, distance at which an obstacle should be detected
#define FORWARD_SPEED           200 // PWM signal

// enums
#define BOTH  0
#define LEFT  1
#define RIGHT 2