# HoverBot
Self-balancing robot using hoverboard hub motors

Arduino code for a radio controlled self-balancing vehicle.
The key components are
* An Arduino Mega https://store.arduino.cc/mega-2560-r3. Using the Mega because the project needs three hardware interrupt pins to decode the RC receiver's PWM signals
* A Bosch BNO055 IMU https://www.adafruit.com/product/2472. Gives read-to-use tilt angle estimtation as well as gyro and accelerometer raw values
* An ODrive motor controller (48V) https://odriverobotics.com/shop/odrive-v35. Enables very smooth current control for the two motors
* Two hoverboard hub motors (easy to source from ebay). Very affordable, powerful and easy-to-use motors.

## External Dependencies
* Metro https://github.com/LuSeKa/Metro
* ODriveArduino https://github.com/madcowswe/ODrive
* Adafruit_Sensor https://github.com/adafruit/Adafruit_Sensor
* Adafruit_BNO055 https://github.com/adafruit/Adafruit_BNO055


[![YouTube Video](https://img.youtube.com/vi/jp_vRK7mbwY/0.jpg)](https://www.youtube.com/watch?v=jp_vRK7mbwY)
