#include "config.h"
#include <ODriveArduino.h>
#include <Metro.h>

int motorsActive = 0; // motor state

ODriveArduino odrive(Serial2); // instantiate ODrive

Metro ledMetro = Metro(BLINK_INTERVAL);
Metro controllerMetro = Metro(CONTROLLER_INTERVAL);
Metro activationMetro = Metro(ACTIVATION_INTERVAL);

// PWM decoder variables
int pwmDutyCycle_throttle = 0;
int pwmDutyCycle_steering = 0;
int pwmDutyCycle_mode = 0;

void setup() {
  pinMode(LEDPIN, OUTPUT);  
  Serial2.begin(BAUDRATE_ODRIVE); // ODrive uses 115200 baud
  
  Serial.begin(BAUDRATE_PC); // Serial to PC

   // pwm decoder interrupts
  attachInterrupt(digitalPinToInterrupt(PWM_CHANNEL_1), decodePwm_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PWM_CHANNEL_2), decodePwm_2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PWM_CHANNEL_3), decodePwm_3, CHANGE);
}

void loop() {
  controlTask();
  activationTask();
  blinkTask();
}

void controlTask() {
  if (controllerMetro.check()) {
    motionController();
  }
}

void activationTask() {
  if (activationMetro.check()) {
    modeSwitch(pwmDutyCycle_mode > ENGAGE_THRESHOLD);
  }
}

void blinkTask() {
  if (ledMetro.check()) {
    digitalWrite(LEDPIN, !digitalRead(LEDPIN));
  }
}
void motionController() {
  
  // planar controllera (lateral position and steering angle)
  float positionControllerOutput = KP_POSITION * (pwmDutyCycle_throttle - PWM_CENTER);
  float steeringControllerOutput = KP_STEERING * (pwmDutyCycle_steering - PWM_CENTER);  

  float controllerOutput_right = positionControllerOutput + steeringControllerOutput;
  float controllerOutput_left  = positionControllerOutput - steeringControllerOutput;
  
  odrive.SetCurrent(0, MOTORDIR_0 * controllerOutput_right);
  odrive.SetCurrent(1, MOTORDIR_1 * controllerOutput_left);
}

void modeSwitch(int mode_desired) {
  if (mode_desired == motorsActive) {
  }
  else {
    if (mode_desired == 1) {
      int requested_state = ODriveArduino::AXIS_STATE_CLOSED_LOOP_CONTROL;
      Serial.println("Engaging motors");
      odrive.run_state(0, requested_state, false);
      odrive.run_state(1, requested_state, false);
    }
    else if (mode_desired == 0) {
      int requested_state = ODriveArduino::AXIS_STATE_IDLE;
      Serial.println("Disengaging motors");
      odrive.run_state(0, requested_state, false);
      odrive.run_state(1, requested_state, false);
    }
    else {
      Serial.println("Invalid mode selection");
    }
    motorsActive = mode_desired;
  }
  return;
}
