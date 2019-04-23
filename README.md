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

## Video
[![YouTube Video](https://img.youtube.com/vi/jp_vRK7mbwY/0.jpg)](https://www.youtube.com/watch?v=jp_vRK7mbwY)

