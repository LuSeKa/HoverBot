/*
 * General configuration for HoverBot.ino
 * Tested on an Arduino Mega
 */

// HARDWARE
#define PWM_CHANNEL_1 2
#define PWM_CHANNEL_2 3
#define PWM_CHANNEL_3 18
#define LEDPIN 13

#define MOTORDIR_0 -1
#define MOTORDIR_1 1

// CONTROLLER
#define KP_POSITION 0.015
#define KP_STEERING 0.01

// RADIO CONTROL
#define ENGAGE_THRESHOLD 1500
#define PWM_CENTER 1500

// SCHEDULING
#define BLINK_INTERVAL 200
#define CONTROLLER_INTERVAL 10
#define ACTIVATION_INTERVAL 50

// SERIAL
#define BAUDRATE_ODRIVE 115200
#define BAUDRATE_PC 115200
