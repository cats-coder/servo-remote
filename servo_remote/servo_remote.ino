/* Includes */
#include <Servo.h>


/* Defines */
#define SERVO_PIN       9
#define DEFAULT_ANGLE   90


/* Variables */
Servo servo;


void setup() {
  /* Setup servo motor on digital pin 9 */
  servo.attach(SERVO_PIN);
  /* Set servo start position */
  servo.write(DEFAULT_ANGLE);
}

void loop() {
}
