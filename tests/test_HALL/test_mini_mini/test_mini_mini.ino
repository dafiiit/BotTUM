//funktioniert so
volatile long temp, counter = 0;  //This variable will increase or decrease depending on the rotation of encoder

void setup() {
  Serial.begin(9600);

  pinMode(25, INPUT_PULLUP);  // internal pullup input pin 2

  pinMode(26, INPUT_PULLUP);  // internalเป็น pullup input pin 3
                             //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(25, ai0, RISING);

  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(26, ai1, RISING);
}

void loop() {
  // Send the value of counter
  if (counter != temp) {
    Serial.println(counter);
    temp = counter;
  }
}

void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if (digitalRead(26) == LOW) {
    counter++;
  } else {
    counter--;
  }
}

void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if (digitalRead(25) == LOW) {
    counter--;
  } else {
    counter++;
  }
}