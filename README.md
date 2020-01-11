# Servo Remote 
This is an arduino project to control a servo motor via an IR remote. It also includes an example for controlling a stepper motor featuring the same functionality.

- The motor can be turned on and off using the On/Off button
- The speed of the motor going between 0 and 180 degree can be made faster or slower by using the IR-Remote (Up and Down buttons respectively)
  - The motor can be configured to rotate between a given set of min and max degrees

## Parts used:

- Servo Motor SG90
  - Alternatively: 
    - 28BYJ-48 Stepper Motor
    - ULN2003A Stepper Motor Driver
- IR-Remote, IR-Receiver module (AX-1838HS)
- 2 x LED 
  - On/Off indicator
  - Button pressed indicator
- 2 x 220 Ohm resistor
- Arduino UNO R3

## Libraries used:
- [Servo](https://www.arduino.cc/en/Reference/Servo) - Arduino
- or [Stepper](https://www.arduino.cc/en/Reference/Stepper) - Arduino
- [IRremote](https://www.arduinolibraries.info/libraries/i-rremote) - shirriff

## Usage
The servo_remote directory contains the arduino sketch as well as a custom control class for the servo motor (ServoController.cpp and ServoController.h) to control the speed and direction without using delay(). 

The stepper_remote directory contains one arduino sketch with the stepper example. 

Make sure the listed libraries are installed correctly. See below for wiring and simply run the respective Arduino sketch.

## Tweaks
See code comments on the `#define`s for setting the maximum and minimum angle for example.

## Wiring
### Using the Servo Motor
![Servo - Example Wiring](wiring/servo_remote.png?raw=true "Servo - Example Wiring")
### Using the Stepper Motor
![Stepper - Example Wiring](wiring/stepper_remote.png?raw=true "Stepper - Example Wiring")
## License
WTFPL - See License.txt