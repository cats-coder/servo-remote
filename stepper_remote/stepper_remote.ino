/* Includes */
#include <Stepper.h>
#include "IRremote.h"


/* Code defines - do not change */
#define SYSTEM_ON       0x01
#define SYSTEM_OFF      0x00
#define UP              1
#define DOWN            -1
#define STEP_DEGREE     6
#define STEPPER_STEPS   32    // motor specific steps

/* Pin configuration - adapt to own wiring */
#define INC_DECR_LED    7  // led on digital pin 7
#define SYS_STAT_LED    13 // led on digital pin 13
#define IR_RECV_PIN     11 // ir receiver on digital pin 11
#define STEPPER_A       2  // coil 1 on digital pin 2
#define STEPPER_B       3  // coil 2 on digital pin 3
#define STEPPER_C       4  // coil 3 on digital pin 4
#define STEPPER_D       5  // coil 4 on digital pin 5

/* Stepper configuration - change per use case */
#define STEP_MAX_SPEED  700   
#define DEFAULT_SPEED   500   // should be between max and min speed
#define STEP_MIN_SPEED  100
#define MAX_ROTATION    +90
#define MIN_ROTATION    -90
#define START_DIRECTION UP    // moving direction on first start

/* Configure the remote keys - adapt to the remote in use */
#define REMOTE_ON_OFF   0xFFA25D  // key for turning the system on and off
#define REMOTE_DOWN     0xFFE01F  // key for increasing the servo speed
#define REMOTE_UP       0xFF906F  // key for decreasing the servo speed


/* Variables */
IRrecv irRecv(IR_RECV_PIN);                                                   // ir receiver instance
decode_results irCommand;                                                     // received ir signal
Stepper stepper(STEPPER_STEPS, STEPPER_D, STEPPER_B, STEPPER_C, STEPPER_A);   // stepper motor instance

int systemState = SYSTEM_OFF;     // system should be off on boot
int currentSpeed = DEFAULT_SPEED;
boolean reachedMinMax = false;    // if default speed is not max or min speed, set this to false

int currentRotation = 0; // the position of the motor on boot will be the start position
int currentDirection = START_DIRECTION;


/**
 * Increase stepper speed (by 100 seems okay, can be adapted however)
 *  @return: true if maximal speed was reached
 */
boolean increaseSpeed() {
  boolean maxReached = false;
  currentSpeed+=100;
  if (currentSpeed >= STEP_MAX_SPEED){
    currentSpeed = STEP_MAX_SPEED;
    maxReached = true;
  }
  stepper.setSpeed(currentSpeed);
  return maxReached;
}


/**
 * Decrease stepper speed (by 100 seems okay, can be adapted however)
 *  @return: true if minimal speed was reached
 */
boolean decreaseSpeed() {
  boolean minReached = false;
  currentSpeed-=100;
  if (currentSpeed <= STEP_MIN_SPEED){
    currentSpeed = STEP_MIN_SPEED;
    minReached = true;
  }
  stepper.setSpeed(currentSpeed);
  return minReached;
}


/**
 * Reset the stepper motor angle to the boot-position
 * 
 * Hint: if the start rotation (default 0) is modifed then you might want to adapt this for correct behavior
 */
void stepToStartRotation() {
  int toRotate = -currentRotation * STEP_DEGREE;
  stepper.step(toRotate);
  currentRotation = 0;
}

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
        digitalWrite(INC_DECR_LED, LOW);
        stepToStartRotation();
      } else {
        systemState = SYSTEM_ON;
        digitalWrite(SYS_STAT_LED, HIGH);
        digitalWrite(INC_DECR_LED, reachedMinMax? HIGH: LOW);
      }
      needDelay = true;
      break;
    case REMOTE_DOWN:
      reachedMinMax = decreaseSpeed();
      setIncDecrLED( reachedMinMax );
      break;
    case REMOTE_UP:
      reachedMinMax = increaseSpeed();
      setIncDecrLED( reachedMinMax );
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

  /* Start ir receiver */
  irRecv.enableIRIn();

  stepper.setSpeed(currentSpeed);
}


void loop() {

  if ( irRecv.decode(&irCommand) ) {
    boolean commandValid = setIRCommando();
    if (commandValid) {
      delay(200); // debounce delay
    }
    irRecv.resume(); // allow next signal
  }

  if (systemState == SYSTEM_ON) { 
    currentRotation += currentDirection; // save current position
    int toRotate = STEP_DEGREE * currentDirection;
    stepper.step(toRotate); // move 1 degree up or down
    if (currentRotation == MAX_ROTATION){
      currentDirection = DOWN;
    }else if ( currentRotation == MIN_ROTATION ) {
      currentDirection = UP;
    }
  }
}
