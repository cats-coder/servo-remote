/* Includes */
#include <Servo.h>
#include <IRremote.h>

/* Defines */
#define SYS_STAT_LED    13 // digital pin 13
#define IR_RECV_PIN     11 // digital pin 11
#define SERVO_PIN       9  // digital pin 9
#define DEFAULT_ANGLE   90

#define REMOTE_ON_OFF   0xFFA25D
#define REMOTE_DOWN     0xFFE01F
#define REMOTE_UP       0xFF906F

#define SYSTEM_ON       0x01
#define SYSTEM_OFF      0x00

/* Variables */
Servo servo; // servo instance
IRrecv irRecv(IR_RECV_PIN); // ir receiver instance
decode_results *irCommand; // decoded signals

int systemState = SYSTEM_OFF;

/* Check what button was pressed on the remote */
void setIRCommando() {
  switch (irCommand->value) {
    case REMOTE_ON_OFF: 
      systemState = !systemState;
      if ( systemState == SYSTEM_ON ) {
        digitalWrite(SYS_STAT_LED, HIGH);
      } else {
        digitalWrite(SYS_STAT_LED, LOW);
      }
      break;
    case REMOTE_DOWN:
      Serial.println("Received Slower");
      // increase speed
      break;
    case REMOTE_UP:
      Serial.println("Received Faster");
      // decrease speed
      break;
    default:
      // invalid commando
      break;
  }
}

void setup() {

  pinMode(SYS_STAT_LED, OUTPUT);
  digitalWrite(SYS_STAT_LED, LOW);
  
  /* Setup servo motor on digital pin 9 */
  servo.attach(SERVO_PIN);
  /* Set servo start position */
  servo.write(DEFAULT_ANGLE);

  Serial.begin(115200);
  /* Start ir receiver */
  irRecv.enableIRIn();
}

void loop() {
  /* Check if signal was caught */
  if (irRecv.decode(irCommand) ) {
    setIRCommando();
    delay(200); // debounce delay
    irRecv.resume();
  }

  if (systemState == SYSTEM_ON) {
    // rotate motor
    //Serial.println("Spinning :)");
  }
}
