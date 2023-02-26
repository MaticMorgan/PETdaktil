#include <AccelStepper.h>
#include <PID_v2.h>

# define NTC_pin A0
# define pot_pin A6
# define pwm_pin 9

 // variables
double NTC_analog;
double nozzle_temperature;
byte spd;

// variables for PID
double Setpoint = 950;
double Input, Output;
double Kp = 50, Ki = 0, Kd = 100;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT); // instance of the PID class

AccelStepper stepper(1, 4, 5); // AccelStepper class instance of a stepper of type 1 with pin 4 for stp and pin 5 for dir

 // functions
double getNtcAnalog() {
  for (int i = 0; i < 10; i++) {
      NTC_analog += analogRead(NTC_pin);
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

void printAll() {
  Serial.println(NTC_analog);
  Serial.println(calculateNozzleTemperature());
  Serial.println(Output);
  Serial.println(spd);
}


void setup() {

  Serial.begin(9600);

  // setting up all the usual
  pinMode(pwm_pin, OUTPUT);
  pinMode(NTC_pin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  myPID.SetMode(AUTOMATIC);

  stepper.setMaxSpeed(1023);
  stepper.setSpeed(analogRead(pot_pin));
  
  delay(3000); // wait for a bit

}


void loop() {

   NTC_analog = getNtcAnalog();
   while (abs(NTC_analog - Setpoint) > 20) {
    adjustPID();
    
   }
   adjustPID();
   spd = analogRead(A6);
   stepper.setSpeed(-spd);
   stepper.runSpeed();
   printAll();

}
