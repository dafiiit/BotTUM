#define ENCODER_A 32 // Pin for Encoder A
#define ENCODER_B 35 // Pin for Encoder B

volatile int encoder_value = 0; // Global variable for storing the encoder position

void encoder_isr() {
  // If the state of A changed, it means the encoder has been rotated
    if (digitalRead(ENCODER_A) == LOW) {
      encoder_value++;
    } else {
      encoder_value--;
    }
    if (digitalRead(ENCODER_B) == LOW) {
      encoder_value--;
    } else {
      encoder_value++;
    }
}

void setup() {
  Serial.begin(115200); // Initialize serial communication
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);

  // Attaching the ISR to encoder A
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoder_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), encoder_isr, RISING);
}

void loop() {
  Serial.println("Encoder value: " + String(encoder_value));
  delay(100);
}