#include <PID_v2.h>

 // constants
const byte Ntc_pin = A0;
const byte pwm_pin = 9;
const int pwm_freq = 5000;
const int resolution = 8;
const int pwmChannel = 0;

 // variables
byte NTC_analog;
double nozzle_temperature;

// variables for PID
double PID_Setpoint = 750;
double PID_Input, PID_Output;

PID myPID(&PID_Input, &PID_Output, &PID_Setpoint, 10, 0, 0, DIRECT);

 // functions
double getNtcAnalog() {
  NTC_analog = analogRead(Ntc_pin);
  return NTC_analog;
}

double calculateNozzleTemperature() {
  nozzle_temperature = NTC_analog * 0.13 - 43.95;
  return nozzle_temperature;
}

void adjustPID() {
  PID_Input = getNtcAnalog();
  myPID.Compute();
  ledcWrite(pwmChannel, PID_Output);
}

void printPID() {
  Serial.println(NTC_analog);
  Serial.println(calculateNozzleTemperature());
  Serial.println(PID_Output);
}


void setup() {

  // setting up all the usual
  pinMode(22, OUTPUT);
  pinMode(32, INPUT);

  Serial.begin(9600);

  // PID setup
  myPID.SetMode(AUTOMATIC);
  PID_Setpoint = 725;
    // PWM setup
    ledcSetup(pwmChannel, pwm_freq, resolution);
    ledcAttachPin(pwm_pin, PID_Output);

}


void loop() {

  NTC_analog = getNtcAnalog();

  delay(1000);

  adjustPID();
  printPID();

  delay(500);

}