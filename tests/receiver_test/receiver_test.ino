#include "config.h"
#include <Metro.h>

Metro ledMetro = Metro(BLINK_INTERVAL);
Metro printMetro = Metro(PRINT_INTERVAL);

// PWM decoder variables
int pwmDutyCycle_throttle = 0;
int pwmDutyCycle_steering = 0;
int pwmDutyCycle_mode = 0;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(BAUDRATE_PC); // Serial to PC

  // pwm decoder interrupts
  attachInterrupt(digitalPinToInterrupt(PWM_CHANNEL_1), decodePwm_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PWM_CHANNEL_2), decodePwm_2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PWM_CHANNEL_3), decodePwm_3, CHANGE);
}

void loop() {
  blinkTask(); // show that the sketch is running
  printTask(); // print PWM values, formatted for the Serial Plotter
}

void blinkTask() {
  if (ledMetro.check()) {
    digitalWrite(LEDPIN, !digitalRead(LEDPIN));
  }
}

void printTask() {
  if (printMetro.check()) {
    Serial.print(pwmDutyCycle_throttle);
    Serial.print('\t');
    Serial.print(pwmDutyCycle_steering);
    Serial.print('\t');
    Serial.println(pwmDutyCycle_mode);
  }
}
