#include "IRremote.h"

#define IR_RECV_PIN /* ! put the connected input pin to the IR receiver here ! e.g. 11 */

IRrecv irRecv(IR_RECV_PIN); // ir receiver instance
decode_results irCommand;   // received ir signal

void setup() {
  Serial.begin(115200); // make sure to use the same baudrate on the serial monitor (Tools->Serial Monitor)
  irRecv.enableIRIn();
  Serial.println("IR Remote Logger using the IRremote library by shirriff");
  Serial.println("\n[TIP] Hit keys multiple times to make sure the value is right.\n");
}


void loop() {
  if ( irRecv.decode(&irCommand) ) {
    Serial.print("Captured hex value: ");
    Serial.println(irCommand.value, HEX);
    delay(200); // debounce delay
    irRecv.resume(); // allow next signal
  }
}
