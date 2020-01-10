/* Includes */
#include <Servo.h>
#include "ServoController.h"
#include "IRremote.h"

/* Code defines - do not change */
#define SYSTEM_ON       0x01
#define SYSTEM_OFF      0x00

/* Pin configuration - adapt to own wiring */
#define SYS_STAT_LED    13 // led on digital pin 13
#define IR_RECV_PIN     11 // ir receiver on digital pin 11
#define SERVO_PIN       9  // servo on digital pin 9
#define INC_DECR_LED    7  // led on digital pin 7

/* Servo configuration - change per use case */
#define DEFAULT_ANGLE   90  // starting position in degree on first start
#define MAX_ANGLE       130 // maximum rotary angle in degree
#define MIN_ANGLE       50  // minimum rotary angle in degree

/* Configure the remote keys - adapt to the remote in use */
#define REMOTE_ON_OFF   0xFFA25D  // key for turning the system on and off
#define REMOTE_DOWN     0xFFE01F  // key for increasing the servo speed
#define REMOTE_UP       0xFF906F  // key for decreasing the servo speed


/* Variables */
Servo servo;                                                          // servo instance
IRrecv irRecv(IR_RECV_PIN);                                           // ir receiver instance
decode_results irCommand;                                             // received ir signal
ServoController servoCntrl(DEFAULT_ANGLE, MAX_ANGLE, MIN_ANGLE);      // custom servo control wrapper instance

int systemState = SYSTEM_OFF;     // system should be off on boot
boolean reachedMinMax = true;     // servo controller starts with minimum speed


/** 
 * Let the INC_DECR led blink or turn it on permanently to indicate
 * a speed change or if the max/min was reached respectively
 */
void setIncDecrLED(boolean permanent) {
  digitalWrite(INC_DECR_LED, systemState == SYSTEM_ON? HIGH: LOW);
  if (!permanent) {
    delay(50);
    digitalWrite(INC_DECR_LED, LOW);
  }
}


/** 
 * Check what button was pressed on the remote 
 */
boolean setIRCommando() {
  //Serial.println(irCommand.value, HEX); // debugging - print all received signals
  boolean needDelay = true;
  switch (irCommand.value) {
    case REMOTE_ON_OFF: 
      if ( systemState == SYSTEM_ON ) {
        systemState = SYSTEM_OFF;
        digitalWrite(SYS_STAT_LED, LOW);
      } else {
        systemState = SYSTEM_ON;
        digitalWrite(SYS_STAT_LED, HIGH);
      }
      needDelay = true;
      break;
    case REMOTE_DOWN:
       reachedMinMax = servoCntrl.decreaseSpeed();
       setIncDecrLED(reachedMinMax);
      break;
    case REMOTE_UP:
      reachedMinMax = servoCntrl.increaseSpeed();
      setIncDecrLED(reachedMinMax);
      break;
    default:
      // invalid command
      needDelay = false;
      break;
  }
  return needDelay;
}

/** 
 * Setup servo, ir-receiver and leds 
 */
void setup() {
  //Serial.begin(115200); // uncomment for prints
  /* Configure and turn off leds */
  pinMode(SYS_STAT_LED, OUTPUT);
  digitalWrite(SYS_STAT_LED, LOW);
  pinMode(INC_DECR_LED, OUTPUT);
  digitalWrite(INC_DECR_LED, LOW);
  
  /* Setup servo motor */
  servo.attach(SERVO_PIN);
  /* Set servo start position */
  servo.write(DEFAULT_ANGLE);

  /* Start ir receiver */
  irRecv.enableIRIn();
}


int prevDegree = DEFAULT_ANGLE; // reminder for previous servo angle
void loop() {

  if ( irRecv.decode(&irCommand) ) {
    boolean commandValid = setIRCommando();
    if (commandValid) {
      delay(200); // debounce delay
    }
    irRecv.resume(); // allow next signal
  }

  if (systemState == SYSTEM_ON) { 
    int degree = servoCntrl.nextStep(); // get new angle
    if (degree != prevDegree){
      servo.write(degree); // update only when angle has actually changed
    }  
    prevDegree = degree;
  }
}
