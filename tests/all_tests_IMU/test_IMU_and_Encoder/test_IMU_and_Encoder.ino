//Encoder Essentials

volatile long temp, enc_counter, hl_counter = 0; 
float divi =1;
int s =1;
int enc_pin1 =12;
int enc_pin2 =14;

void setup() {
  Serial.begin (115200);
  //Setup Encoder
  pinMode(enc_pin1, INPUT_PULLUP);
  pinMode(enc_pin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(enc_pin1), enc_ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(enc_pin2), enc_ai1, RISING);
}

void loop() {

  if( enc_counter != temp ){
    //Serial.print(enc_counter/1200.0); //Rotations
    Serial.print(((enc_counter/1200.0)-(enc_counter/1200))*360); //Degrees
    Serial.println(" <<");
    temp = enc_counter;
  }
}

  void enc_ai0() {
  if(digitalRead(enc_pin2)==LOW)enc_counter++;
  else enc_counter--;
  } 
  void enc_ai1() {
  if(digitalRead(enc_pin1)==LOW)enc_counter--;
  else enc_counter++;
  }
