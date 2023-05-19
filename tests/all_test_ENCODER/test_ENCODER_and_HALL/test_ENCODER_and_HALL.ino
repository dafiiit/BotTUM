volatile long temp, enc_counter, hl_counter = 0; 
float divi =1;
int s =1;
int enc_pin1 =12;
int enc_pin2 =14;
int led = 2; //LED pin
int hallSensor = 19; //Sensor pin
volatile double time_trig;
volatile double time_now;
volatile float time_delta;
float rpm_1;
bool state=false;
    
void setup() {
  Serial.begin (115200);
  //Setup Encoder
  pinMode(enc_pin1, INPUT_PULLUP);
  pinMode(enc_pin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(enc_pin1), enc_ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(enc_pin2), enc_ai1, RISING);
  //Setup Hall Sensor
  pinMode(led, OUTPUT);
  pinMode(hallSensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(hallSensor), isr, RISING);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  }
   
  void loop() {

  /*time_now=millis();
  if(time_delta)
  {
    rpm_1=1/(time_delta/1000)*60;
    print(rpm_1);
  }
  
  print(time_delta);
  delay(5);*/

  
  // Send the value of enc_counter
  /*if(s==3){if( hl_counter != temp){
  Serial.println(hl_counter);
  temp = hl_counter;
  }}*/
  
  if( enc_counter != temp ){
  Serial.print(hl_counter/1.0);
  Serial.print(" | ");
  if(s==1)Serial.println (enc_counter/divi);
  else if(s==2) Serial.println(((enc_counter/1200.0)-(enc_counter/1200))*360);
  //else if(s==3) Serial.println(hl_counter);
  temp = enc_counter;
  }

  
  if (Serial.available() > 0) {
    char inbyte = (char)Serial.read();
    switch (inbyte){
      case 'r': hl_counter=0; enc_counter = 0; break;
      case 'u': divi=1200; s=1; break;
      case 'o': divi=1; s=1; break;
      case 'd': s=2; break;
      case 'a': Serial.println("awake (*^_^*)"); break;
      case 'h': s=3; break;
      case 'x': hl_counter = 0; break;
    }
  }
  }


  //Encoder interrupt functions
  void enc_ai0() {
  if(digitalRead(enc_pin2)==LOW)enc_counter++;
  else enc_counter--;
  } 
  void enc_ai1() {
  if(digitalRead(enc_pin1)==LOW)enc_counter--;
  else enc_counter++;
  }
  // IRAM_ATTR
  //Hall Sensor interrupt functions
  void isr(){
  hl_counter++;
  /*state=!state;
  time_delta=time_now-time_trig;
  time_trig=time_now;*/
  }
