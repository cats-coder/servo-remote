# Servo Remote
This is an arduino project where we want to control a servo motor via an IR remote. 

- The servo motor can be turned on and off using the On/Off button
- The speed of the servo motor going between 0 and 180 degree can be made faster or slower by using the Up and Down buttons respectively

## Parts used:

- Servo Motor SG90
- IR-Remote, IR-Receiver module (AX-1838HS)
- 2 x LED 
  - On/Off indicator
  - Button pressed indicator
- 2 x 220 Ohm resistor
- Arduino UNO R3

## Libraries used:
- [Servo](https://www.arduino.cc/en/Reference/Servo)
- [IRremote](https://www.arduinolibraries.info/libraries/i-rremote)