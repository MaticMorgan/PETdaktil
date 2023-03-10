#include <PID_v2.h>

 // constants
const byte Ntc_pin = A0;
const byte pwm_pin = 9;
const byte stp_pin = 3;
const byte slp_pin = 2;

 // variables
double NTC_analog;
double nozzle_temperature;

// variables for PID
double Setpoint = 991;
//double pidSecondThreshold = 50;
double Input, Output;
double Kp = 50, Ki = 0, Kd = 0;
//double closeKp = 50, closeKi = 0, closeKd = 0;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


 // functions
double getNtcAnalog() {
  for (int i = 0; i < 10; i++) {
      NTC_analog += analogRead(Ntc_pin);
  }
  NTC_analog = NTC_analog / 10.0;
  return NTC_analog;
}

double calculateNozzleTemperature() {
  return NTC_analog * 0.21 + 14.3;
}

void adjustPID() {
  Input = getNtcAnalog();
  myPID.Compute();
  analogWrite(pwm_pin, Output);
}

void printPID() {
  Serial.println(NTC_analog);
  Serial.println(calculateNozzleTemperature());
  Serial.println(Output);
}

void makeOneStep() {
  digitalWrite(stp_pin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(stp_pin, LOW);
  delayMicroseconds(1000);
}

void stepperSleep() {
  digitalWrite(slp_pin, LOW);
}


void setup() {

  // setting up all the usual
  pinMode(pwm_pin, OUTPUT);
  pinMode(Ntc_pin, INPUT);
  pinMode(stp_pin, OUTPUT);
  pinMode(slp_pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  myPID.SetMode(AUTOMATIC);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  stepperSleep();
  delay(5000); // wait for 5 seconds so all other systems come online

}


void loop() {


   NTC_analog = getNtcAnalog();

   if ( abs(Setpoint - NTC_analog) < 10) {
//     myPID.SetTunings(closeKp, closeKi, closeKd);
     digitalWrite(LED_BUILTIN, HIGH);
   }
   else {
     digitalWrite(LED_BUILTIN, LOW);
   }

   adjustPID();
   printPID();
  // Serial.println(calculateNozzleTemperature());

   delay(100);

}
