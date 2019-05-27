# Testing the ODrive and remote control without the IMU

This test is inteded to make sure the Arduiono communicates with the ODrive, the motors can be controlled via the remote control and the turn in the correct directions.
Make sure the robot's wheels are not touching the ground. Slide the activation switch on the remote to the low position. Then power-up the ODrive. The motors should be in free wheel mode (idle). Once you slide the activation switch, the should bet activated (making a brief audible sound).
When applieng throttle, the wheels should turn in the same direction. When applying steering, they should move in opposite directions. These two commands are superimposed.
If the directions are off, you can change them with the MOTORDIR-Macros in https://github.com/LuSeKa/HoverBot/blob/master/config.h.


