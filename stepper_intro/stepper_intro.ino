const byte stp_pin = 5;



void setup() {
  
  pinMode(stp_pin, OUTPUT);

}

void loop() {

  analogWrite(stp_pin, 50);

}
