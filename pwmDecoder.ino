// Interrupt callbacks to measure the pwm duty cycle

void decodePwm_1() {
  static unsigned long riseTime = micros(); // initialize riseTime
  if (digitalRead(PWM_CHANNEL_1) == 1) { // the signal has risen
    riseTime = micros(); // save the rise time
  }
  else { // the signal has fallen
    pwmDutyCycle_steering = micros() - riseTime; // compute the duration of the high pulse
  }
}

void decodePwm_2() {
  static unsigned long riseTime = micros(); // initialize riseTime
  if (digitalRead(PWM_CHANNEL_2) == 1) { // the signal has risen
    riseTime = micros(); // save the rise time
  }
  else { // the signal has fallen
    pwmDutyCycle_throttle = micros() - riseTime; // compute the duration of the high pulse
  }
}

void decodePwm_3() {
  static unsigned long riseTime = micros(); // initialize riseTime
  if (digitalRead(PWM_CHANNEL_3) == 1) { // the signal has risen
    riseTime = micros(); // save the rise time
  }
  else { // the signal has fallen
    pwmDutyCycle_mode = micros() - riseTime; // compute the duration of the high pulse
  }
}
