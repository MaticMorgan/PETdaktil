// knjiznice
#include <AccelStepper.h>
#include <PID_v2.h>

// PID setup
#define NTC_PIN A4
#define PWM_PIN 5
double NTC_analog;
double Setpoint = 940; //240C
double Input, Output;
double Kp = 30, Ki = 0, Kd = 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT); // PID instanca

// setup za koracni motor
#define STP_PIN 2
#define DIR_PIN 20

AccelStepper stepper1(AccelStepper::FULL2WIRE, STP_PIN, DIR_PIN);


// FUNKCIJE

// PID functions
double getNtcAnalog() {  // povprecje 10 meritev
  NTC_analog = 0;
  for (int i = 0; i < 10; i++) {
      NTC_analog += analogRead(NTC_PIN);
  }
  NTC_analog = NTC_analog / 10.0;
  return NTC_analog;
}

void adjustPID() {
  Input = getNtcAnalog();
  myPID.Compute();
  analogWrite(PWM_PIN, Output);
}


void setup() {
  
  pinMode(PWM_PIN, OUTPUT);
  pinMode(NTC_PIN, INPUT);
  pinMode(STP_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  myPID.SetMode(AUTOMATIC);
  myPID.SetTunings(Kp, Ki, Kd);

  stepper1.setMaxSpeed(1000); 
  stepper1.setSpeed(500);

  // sekundni utrip vgrajene LED, signal, da vse deluje po planu
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);

}

  // glavni, ponavljajoc del programa. Vsako iteracijo se izvrsi PID in ukaz za premik motorja.
  // Ko je temperatura sobe blizu nastavljeni temperaturi se prizge LED in zacne vrteti motor.

void loop() {

  adjustPID();
  
  if (abs(Setpoint - analogRead(NTC_PIN)) < 20) {
    digitalWrite(LED_BUILTIN, HIGH);
    stepper1.runSpeed();
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  
}
