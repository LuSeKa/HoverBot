#include "config.h"
#include <Wire.h>
#include <Metro.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <ODriveArduino.h>
#if USE_PPM
#include <PPMReader.h> // https://github.com/Nikkilae/PPM-reader
#endif // USE_PPM

int motorsActive = 0; // motor state
bool tilt_limit_exceeded = false; // motor desired state

Adafruit_BNO055 bno = Adafruit_BNO055(); // instantiate IMU
ODriveArduino odrive(Serial2); // instantiate ODrive

Metro ledMetro = Metro(BLINK_INTERVAL);
Metro controllerMetro = Metro(CONTROLLER_INTERVAL);
Metro activationMetro = Metro(ACTIVATION_INTERVAL);

// PWM decoder variables
int steeringCommand_us = 0;
int throttleCommand_us = 0;
int modeCommand_us = 0;

#if USE_PPM
// Initialize a PPMReader
PPMReader ppmDecoder(PPM_PIN, NUM_PPM_CHANNELS);
#endif // USE_PPM

void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial2.begin(BAUDRATE_ODRIVE); // ODrive uses 115200 baud

  Serial.begin(BAUDRATE_PC); // Serial to PC

  // IMU
  if (!bno.begin())
  {
    Serial.print("No BNO found. Check wiring or I2C address!");
    while (1); // halt for safety
  }
  delay(1000);
  bno.setExtCrystalUse(true);

#if !USE_PPM
  // pwm decoder interrupts
  attachInterrupt(digitalPinToInterrupt(PWM_PIN_STEERING), decodeSteeringPwm, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PWM_PIN_THROTTLE), decodeThrottlePwm, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PWM_PIN_MODE), decodeModePwm, CHANGE);
#endif // !USE_PPM
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
#if USE_PPM
    // Get command from PPM signal
    modeCommand_us = ppmDecoder.latestValidChannelValue(PPM_MODE_CHANNEL, ENGAGE_THRESHOLD);
#endif // USE_PPM
    // If using PWM, command will be updated in the ISR
    modeSwitch(modeCommand_us > ENGAGE_THRESHOLD && !tilt_limit_exceeded);
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

  if (abs(euler.z()) > TILT_LIMIT) {
    tilt_limit_exceeded = true;
  }
  else {
    tilt_limit_exceeded = false;
  }

  // balance controller
  float balanceControllerOutput = euler.z() * KP_BALANCE + gyro.x() * KD_BALANCE;

  // planar controllers (lateral position and steering angle)
#if USE_PPM
  // Get commands from PPM signal
  throttleCommand_us = ppmDecoder.latestValidChannelValue(PPM_THROTTLE_CHANNEL, PWM_CENTER);
  steeringCommand_us = ppmDecoder.latestValidChannelValue(PPM_STEERING_CHANNEL, PWM_CENTER);
#endif // USE_PPM
  // If using PWM, commands will be updated in the ISRs
  float positionControllerOutput = KP_POSITION * (throttleCommand_us - PWM_CENTER);
  float steeringControllerOutput = KP_STEERING * (steeringCommand_us - PWM_CENTER) + gyro.z() * KD_ORIENTATION;

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
      int requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL;
      Serial.println("Engaging motors");
      odrive.run_state(0, requested_state, false);
      odrive.run_state(1, requested_state, false);
    }
    else if (mode_desired == 0) {
      int requested_state = AXIS_STATE_IDLE;
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
