#include <ESP32Servo.h>
Servo s1;
int spin= 27;
int mpin= 12;
int apin= 14;
int dpin= 5;
int bpin= 23;
int ppin= 19;
int hall= 2;
int h1pin= 32;
int h2pin= 33;
int h3pin= 34;

int h1_counter=0;
int h2_counter=0;
int h3_counter=0;
long currT=0;
long prevT=0;
int prevCount1=0;
int prevCount2=0;
int prevCount3=0;
float motorVelocity=0;
int samplingT =20.0e4;
int tmp=0;

void setup() {
  Serial.begin(115200);
  pinMode(h1pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(h1pin), h1, RISING);
  pinMode(h2pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(h2pin), h2, RISING);
  pinMode(h3pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(h3pin), h3, RISING);
  
  s1.attach(spin);
  pinMode(mpin,OUTPUT);
  //res();
  s1.write(20);
  analogWrite(mpin, 0);
  pinMode(apin,OUTPUT);
  digitalWrite(apin, 0);
  pinMode(bpin,OUTPUT);
  digitalWrite(bpin, 0);
  pinMode(dpin,OUTPUT);
  digitalWrite(dpin, 0);
  pinMode(ppin,OUTPUT);
  digitalWrite(ppin, 0);
}

void loop() {
  currT = micros();
  if (currT - prevT >= samplingT) {
    float motorVelocity1 = (h1_counter - prevCount1)/(samplingT/1000000.0)/8.0;
    float motorVelocity2 = (h2_counter - prevCount2)/(samplingT/1000000.0)/8.0;
    float motorVelocity3 = (h3_counter - prevCount3)/(samplingT/1000000.0)/8.0;
    motorVelocity = (motorVelocity1+motorVelocity2+motorVelocity3)/3*60;
    prevT = currT; 
    prevCount1 = h1_counter;
    prevCount2 = h2_counter;
    prevCount3 = h3_counter;
    Serial.print(" 1: "); Serial.print(motorVelocity1*60);
  Serial.print(" 2: "); Serial.print(motorVelocity2*60);
  Serial.print(" 3: "); Serial.print(motorVelocity3*60);
    Serial.print(" A: "); Serial.println(motorVelocity);
  }
  
  

  
    if (Serial.available() > 0){
    char inbyte = (char)Serial.read();
    switch (inbyte){
      case '1': analogWrite(mpin,30); break;
      case '2': analogWrite(mpin,60); break;
      case '3': analogWrite(mpin,90); break;
      case '4': analogWrite(mpin,120); break;
      case '5': analogWrite(mpin,150); break;
      case '6': analogWrite(mpin,180); break;
      case '7': analogWrite(mpin,210); break;
      case '8': analogWrite(mpin,230); break;
      case '9': analogWrite(mpin,255); break;
      case '0': analogWrite(mpin,0); break;
      case 'r': res(); break;
      case 'n': s1.write(0);tmp=0; break;
      case '+': tmp+=2; s1.write(tmp); break;
      case '-': tmp-=2; s1.write(tmp); break;
      case 'a': brake_l(100); break;
      case 'b': brake_s(100); break;
      case 'c': digitalWrite(apin,1); digitalWrite(ppin,1); break;
      case 'x': digitalWrite(apin,0); digitalWrite(ppin,0); break;
      case '<': digitalWrite(dpin,1); break;
      case '>': digitalWrite(dpin,0); break;
      case 'q': digitalWrite(bpin,1);  break;
      case 'w': digitalWrite(bpin,0);  break;
    }
  }

}

void res(){
  s1.write(90);
  tmp=90;
}

void brake_s(int del){
  
  delay(del);
  analogWrite(mpin,0);
  delay(20);
  s1.write(16);
  tmp=16;
}

void brake_l(int del){
  
  delay(del);
  analogWrite(mpin,0);
  delay(20);
  digitalWrite(apin,1);
  digitalWrite(ppin,1);
  delay(500);
  digitalWrite(apin,0);
  digitalWrite(ppin,0);
}

void h1(){
  if(digitalRead(h3pin)) h1_counter++;
  else if(digitalRead(h2pin)) h1_counter--;
  }
  void h2(){
  if(digitalRead(h1pin)) h2_counter++;
  else if(digitalRead(h3pin)) h2_counter--;
  }
  void h3(){
  if(digitalRead(h2pin)) h3_counter++;
  else if(digitalRead(h1pin)) h3_counter--;
  }
