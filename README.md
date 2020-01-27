# Servo Remote 
This is an Arduino project to control a servo motor via an IR remote. It also includes an example for controlling a stepper motor featuring the same functionality. 

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

## Description
The **servo_remote** directory contains the arduino sketch as well as a custom control class for the servo motor (ServoController.cpp and ServoController.h) to control the speed and direction without using delay(). 

The **stepper_remote** directory contains an Arduino sketch with the stepper example.

In **remote_logger** you will find a very simple Arduino sketch that will print the hex values of received IR-signals.

## Usage
### Install Libraries
Firstly make sure the libraries listed above are installed correctly (Stepper and Servo are most likely to exist by default). See [here](https://www.arduino.cc/en/Guide/Libraries) for more information on how to install libraries in the Arduino IDE.

### Setup the IR Remote
Before uploading the sketch to the Arduino you must configure thed< values for the keys of your remote. This application uses 3 keys:
`ON/OFF`, `UP` and `DOWN`

Each key is mapped to its specific hex value sent by the remote. In this repository under **remote_logger** you can find a simple helper sketch for printing the hex value of IR-signals. Simply replace the connection pin in remote_logger.ino, open the serial monitor, upload the sketch and write down the values.

Once you collected the values for the keys you'd like to use replace the following `define`s in the servo/stepper_remote.ino with your values.

- `REMOTE_ON_OFF 0x<value>`
- `REMOTE_DOWN 0x<value>`
- `REMOTE_UP 0x<value>`

### Check the Wiring
Connect the components as depicted [here](#Wiring). Using the components listed above, it's worth mentioning that on the IR-Receiver Module **G** connects to Ground, **R** to VCC (5V) and **Y** to a digital input pin.

In case of custom connections see [here](#Custom-Wiring).

### Upload Sketch
Once the connections in the code match the actual wiring and the libraries are installed you are ready to go.

## Tweaks
Some of the `define`s in the servo/stepper_remote.ino can be changed to alter the motor behavior.

### Max-Min Rotation Angle
Setting the rotation span.
#### Servo Motor (0-180°)
- `DEFAULT_ANGLE <degree>`: position on boot
- `MAX_ANGLE <degree>`
- `MIN_ANGLE <degree>`

`degree` is the absolute position and must be between 0 and 180°
#### Stepper Motor (360°)
- `MAX_ROTATION <degree>`
- `MIN_ROTATION <degree>`

`degree` is the relative position (distance to the starting point)

Note that the starting position will always be the motor position on boot. Everytime the system is turned off (via remote) the motor will return to this starting position. On reset/error/powercut it will not, causing a new starting position on the next boot!
### Max-Min Speed
Setting the allowed speeds to switch between with the remote.
#### Servo Motor
The speed-levels for the servo motor are defined in ServoController/ServoController.h (not the servo_remote.ino)
- `SERVO_MAX_SPEED <number>`
- `SERVO_MIN_SPEED <number>`

The servo starts with the minimum speed on boot.
#### Stepper Motor
- `STEP_MAX_SPEED <number>`
- `STEP_MIN_SPEED <number>`
- `DEFAULT_SPEED <number>`: speed on boot

### Custom Wiring
When connecting components differently to what's depicted under [Wiring](#Wiring) make sure to update the code accordingly. The connected pins can be configured the same way in both servo_remote.ino and stepper_remote.ino in the `define` section.
- `SYS_STAT_LED <pin>`: This LED indicates the system state (On or Off) - toggled when the user uses the remote-key "on/off"

- `INC_DECR_LED <pin>`: This LED indicates everytime the Up or Down button was pressed (flash) and when the speed reached the maximum or minimum
- `IR_RECV_PIN <pin>`: Connects to the IR-Receiver Module
#### Servo
- `SERVO_PIN <pin>`: Connects to the servo motor
#### Stepper
- `STEPPER_A <pin>`: Connects to INV 1 of the stepper motor
- `STEPPER_B <pin>`: Connects to INV 2 of the stepper motor
- `STEPPER_C <pin>`: Connects to INV 3 of the stepper motor
- `STEPPER_D <pin>`: Connects to INV 3 of the stepper motor

Note that the `STEPPER` pins do not actually connect to the motor but the motor driver.

## Wiring
### Using the Servo Motor
![Servo - Example Wiring](wiring/servo_remote.png?raw=true "Servo - Example Wiring")
### Using the Stepper Motor
![Stepper - Example Wiring](wiring/stepper_remote.png?raw=true "Stepper - Example Wiring")
## License
The code is licensed under the [WTFPL](License.txt)

cats-coder © 2020
