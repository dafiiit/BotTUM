

const int HallSensor = 3; //Sensor pin
//pin
const int ledPin = 13; //LED pin

volatile int hallState = 0;   //Variable for reading the hall status
void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(HallSensor, INPUT);
  attachInterrupt(0,pin_ISR,CHANGE);
}

void pin_ISR(){       //Interrupt Service Routine
  hallState = digitalRead(HallSensor);
  digitalWrite(ledPin, hallState);
}

void loop(){
  
}