# HoverBot
Self-balancing robot using hoverboard hub motors.

Arduino code for a radio controlled self-balancing vehicle.
The key components are
* An Arduino Mega https://store.arduino.cc/mega-2560-r3. Using the Mega because the project needs three hardware interrupt pins to decode the RC receiver's PWM signals.
* A Bosch BNO055 IMU https://www.adafruit.com/product/2472. Gives ready-to-use tilt angle estimation as well as gyro and accelerometer raw readings.
* An ODrive motor controller (48V) https://odriverobotics.com/shop/odrive-v35. Enables very smooth current control for the two motors.
* Two hoverboard hub motors (easy to source from ebay). Very affordable, powerful and easy-to-use motors.

## External Dependencies
* Metro https://github.com/LuSeKa/Metro
* ODriveArduino https://github.com/madcowswe/ODrive
* Adafruit_Sensor https://github.com/adafruit/Adafruit_Sensor
* Adafruit_BNO055 https://github.com/adafruit/Adafruit_BNO055

## Control Scheme
The ODrive is operated in current control mode. The current is computed by the Arduino from the pitch and pitching velocity to control balancing, from the throttle command to control the forward and backward velocity, and from the steering command and the yaw velocity to control the steering. The controller is tuned with five parameters listed in the config.h file.

![HoverBot_control](https://user-images.githubusercontent.com/8363989/56305285-4aaa8080-6140-11e9-976f-1688bf279cee.png)

A problem of this control scheme is that the onboard controller does not get velocity feedback. If the vehicle goes too fast, the balance controller cannot compensate a forward fall anymore, and it will fall over eventually. The human at the sticks therefore needs to make sure that the velocity is kept sufficiently slow.

## Schematic
The following diagram roughly explains the data flow and types of electrical connections.
![HoverBot_wiring](https://user-images.githubusercontent.com/8363989/56580510-f5a0bb80-65d2-11e9-9292-611b99229bdf.png)

### ODrive
The wiring of the ODrive is explained on the ODrive website (that has very nice docs overall!):
https://docs.odriverobotics.com/#wiring-up-the-odrive
It is powered from the battey via its DC clamps, and each motor's three phases (A,B,C) are connected to one of its motor outputs (M0 and M1). The order in which the motor wires are connected does not matter, the ODrive figures this out by itself during calibration.
Since the HoverBot is running on batteries, no auxiliary breaking resistor is required (the ODrive dumps recuperated energy into the battery).
Each hoverboard motor comes with hall sensors that tell the ODrive when to power which of the three phases. Each hall sensor has five wires: Two for power (5V, usually red and GND, usually black) and three for signal (ofen blue, yellow and green). A motor's hall sensors are connected to the its correspoinding sensor inputs. The three signal lines are connected to inputs A, B and Z where the order again does not matter. Note that it might be necessary (depending on the version of the ODrive) to add some a 22nF capacitor between each of the three signals and ground for signal integrity, as is mentioned here:
https://discourse.odriverobotics.com/t/encoder-error-error-illegal-hall-state/1047/6
The ODrive powers the 5V power supply of all other components, so its GND and 5V rail are connected to a breadboard that acts as power distribution.
The ODrive communicates with the Arduino via the serial port, or UART. The UART-pins ar GPIO 1 and GPIO 2 as explained here:
https://docs.odriverobotics.com/interfaces#ports

## Video
[![YouTube Video](https://img.youtube.com/vi/jp_vRK7mbwY/0.jpg)](https://www.youtube.com/watch?v=jp_vRK7mbwY)

