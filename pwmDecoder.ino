#if !USE_PPM
// Interrupt callbacks to measure the pwm duty cycle

void decodeSteeringPwm() {
  static unsigned long riseTime = micros(); // initialize riseTime
  if (digitalRead(PWM_PIN_STEERING) == 1) { // the signal has risen
    riseTime = micros(); // save the rise time
  }
  else { // the signal has fallen
    steeringCommand_us = micros() - riseTime; // compute the duration of the high pulse
  }
}

void decodeThrottlePwm() {
  static unsigned long riseTime = micros(); // initialize riseTime
  if (digitalRead(PWM_PIN_THROTTLE) == 1) { // the signal has risen
    riseTime = micros(); // save the rise time
  }
  else { // the signal has fallen
    throttleCommand_us = micros() - riseTime; // compute the duration of the high pulse
  }
}

void decodeModePwm() {
  static unsigned long riseTime = micros(); // initialize riseTime
  if (digitalRead(PWM_PIN_MODE) == 1) { // the signal has risen
    riseTime = micros(); // save the rise time
  }
  else { // the signal has fallen
    modeCommand_us = micros() - riseTime; // compute the duration of the high pulse
  }
}
#endif // !USE_PPM
