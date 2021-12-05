/*
   General configuration for HoverBot.ino
   Tested on an Arduino Mega
*/

// HARDWARE
#define LEDPIN 13

// MOTOR DIRECTIONS
#define MOTORDIR_0 -1
#define MOTORDIR_1 1

// CONTROLLER
#define KP_BALANCE 0.4
#define KD_BALANCE -0.065
#define KP_POSITION 0.015
#define KP_STEERING 0.01
#define KD_ORIENTATION 0.01
#define TILT_LIMIT 40

// RADIO CONTROL HARDWARE
// true for PPM receivers, false for PWM reicevers
#define USE_PPM false
#if USE_PPM
#define PPM_PIN 2 // Arduino interrupt pin connected to receiver PPM output
#define NUM_PPM_CHANNELS 8 // Number of channels transmitted in the PPM signal
#define PPM_STEERING_CHANNEL 1 // RC channel for steering
#define PPM_THROTTLE_CHANNEL 2 // RC channel for throttle
#define PPM_MODE_CHANNEL 3 // RC channel for mode selection
#else // Using PWM
#define PWM_PIN_STEERING 2
#define PWM_PIN_THROTTLE 3
#define PWM_PIN_MODE 18
#endif // USE_PPM

// RADIO CONTROL PARAMETERS
#define ENGAGE_THRESHOLD 1500
#define PWM_CENTER 1500

// SCHEDULING
#define BLINK_INTERVAL 200
#define CONTROLLER_INTERVAL 10
#define ACTIVATION_INTERVAL 50

// SERIAL
#define BAUDRATE_ODRIVE 115200
#define BAUDRATE_PC 115200
