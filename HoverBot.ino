#include "config.h"
#include <Wire.h>
#include <Metro.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <ODriveArduino.h>

int motorsActive = 0; // motor state

Adafruit_BNO055 bno = Adafruit_BNO055(); // instantiate IMU
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
  Serial2.begin(115200); // ODrive uses 115200 baud
  
  Serial.begin(115200); // Serial to PC

  // IMU
  if (!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1); // halt for safety
  }
  delay(1000);
  bno.setExtCrystalUse(true);

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
  // IMU sampling
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  // ODrive sampling
  float vel = 0;
  #if ENABLE_POSITIONCONTROL != 0
  float vel_right = MOTORDIR_0 * odrive.GetVelocity(0);
  float vel_left = MOTORDIR_1 * odrive.GetVelocity(1);
  vel = (vel_right + vel_left)/2;
  //Serial.print(vel_right);
  //Serial.print('\t');
  //Serial.println(vel_left);
  #endif
  
  // balance controller
  float balanceControllerOutput = euler.z() * KP_BALANCE + gyro.x() * KD_BALANCE;

  // planar controllera (lateral position and steering angle)
  float positionControllerOutput = KP_POSITION * (pwmDutyCycle_throttle - PWM_CENTER) - KD_POSITION * vel;
  float steeringControllerOutput = KP_STEERING * (pwmDutyCycle_steering - PWM_CENTER) + gyro.z() * KD_ORIENTATION;  

  float controllerOutput_right = balanceControllerOutput + positionControllerOutput + steeringControllerOutput;
  float controllerOutput_left  = balanceControllerOutput + positionControllerOutput - steeringControllerOutput;
  
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
