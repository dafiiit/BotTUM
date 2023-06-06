#include <Wire.h>
#include <PID_v1.h>
//#include <ESP32Servo.h> //Just dont forget about this lib


//Register map:

  #define ADXL345 0x53 //Adress chosen by grounding SDO
  #define DATAx0 0x32
  #define DATAx1 0x33
  #define DATAy0 0x34
  #define DATAy1 0x35
  #define DATAz0 0x36
  #define DATAz1 0x37
  #define POWER_CTL 0x2D
  #define BW_RATE 0x2C
  #define POWER_CTL_WRITE B00001000
  #define DATA_FORMAT 0x31
  #define DATA_RATE 8 //1000 corresponds to 25hz Output rate. Too low for PID. Try 14-1110 or 15 1111 instead
  #define FULLRES_2g B00001000
  #define FULLRES_16g B00001011
  #define WRITE 0xA6
  #define READ 0xA7

//I2C pins:
const int esp32_SCL=22;
const int esp32_SDA=21;

//PID init
  double input_1, setpoint, output_1;
  double Kp=3, Ki=0.072, Kd=0;


//Motor init
  bool direction_1=false;
  const int PWM_OUT=15;
  const int DIR_OUT=2;
  const int BRAKE_OUT=4;
  bool BRK_bool=false;
  volatile int BRK_time=0;

PID PID_1(&input_1, &output_1, &setpoint, Kp, Ki, Kd, DIRECT);

 

void setup() {
  
  attachInterrupt(digitalPinToInterrupt(DIR_OUT), ISRswitch, CHANGE);

  setpoint = 180; //Waagerecht
  PID_1.SetSampleTime(5);
  PID_1.SetMode(AUTOMATIC);
  PID_1.SetOutputLimits(-255, 255);



  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("Start");
  delay(5);
  Wire.begin(esp32_SDA, esp32_SCL, 500000);
  
  //I2C: MSBfirst, 5mhz max, CS set to HIGH for ADXL necessary


  //Setup power management  

  Wire.beginTransmission(ADXL345);
  Wire.write(POWER_CTL);
  Wire.write(POWER_CTL_WRITE); 
  Wire.endTransmission(true);
  delay(20);

  Wire.beginTransmission(ADXL345);
  Wire.write(BW_RATE);
  Wire.write(8); //15 to binary: 1111, corresponds to 3200Hz data rate and 1600Hz Bandwidth
  Wire.endTransmission(true);
  delay(20);

  Serial.println("Powermode & BW_RATE written");
  delay(20);

//Setup range

  Wire.beginTransmission(ADXL345);
  Wire.write(DATA_FORMAT);
  Wire.write(FULLRES_2g);
  Wire.endTransmission(true);
  Serial.println("Range set to 2g");
  delay(20);

  pinMode(PWM_OUT, OUTPUT);
  pinMode(DIR_OUT, OUTPUT);

Serial.println("Setup complete");
delay(1000);
}

//Axis data init
  float DATA[3]; //Array for storing Acceleration data. DATA[0] for x, DATA[1] for y and DATA[2] for z. Range is -90 to 90
  float ANGLE[3]; //Array for storing calculated Angle data.

void loop() {
  //Brake timer loop
  if(BRK_bool)
  {
    while(millis()<(BRK_time+100))
    {
      analogWrite(PWM_OUT, 0);
      digitalWrite(BRAKE_OUT, HIGH);
    }
  digitalWrite(BRAKE_OUT, LOW);
  BRK_bool=false;
  }
  
  //PID loop
  readDATA();
  if(ANGLE[1]>170&&ANGLE[1]<190)
  {
    if(ANGLE[1]>=180)
    {
      input_1=(360-ANGLE[1]);
      direction_1=false;
    }
    else
    {
      input_1 = ANGLE[1];
      direction_1=true;
    }
  
  PID_1.Compute();
  analogWrite(PWM_OUT, output_1);
  digitalWrite(DIR_OUT, direction_1);
  Serial.print("Computered PID value:  ");
  Serial.print(output_1);
  Serial.print("  Corresponding x Angle:  ");
  Serial.print(ANGLE[1]);
  Serial.print("  Dir: ");
  Serial.print(direction_1);
  Serial.print("  BRK bool: ");
  Serial.print(BRK_bool);
  Serial.println();
  
  }


  else{
    Serial.println(ANGLE[1]);
    analogWrite(PWM_OUT, 0);
    //Serial.println("Enter PID range");
  }
  
}





//Func for reading x axis accelerometer Data. Integer num represents the number of bytes requested from the accelerometer.
void readDATA(){
  
  byte buff[2];
  int num =1;

  Wire.beginTransmission(ADXL345);
  Wire.write(DATAx1);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345, num, true);
  int n = 0;

  while(Wire.available())
    {

      buff[n] = Wire.read();
      n++;    
    }
  
  Wire.beginTransmission(ADXL345);
  Wire.write(DATAx0);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345, num, true);

  while(Wire.available())
  {
    buff[n]=Wire.read();
    n++;
  }
  //Refer to fig.49 of Datasheet
  //Format Datatype from byte to 10bit int number

  Wire.endTransmission();

  DATA[0]=(int16_t)(buff[0]<<8|buff[1]);
  //Save x axis data to first array spot

  Wire.beginTransmission(ADXL345);
  Wire.write(DATAy1);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345, num, true);
  n = 0;

  while(Wire.available())
    {

      buff[n] = Wire.read();
      n++;    
    }
  
  Wire.beginTransmission(ADXL345);
  Wire.write(DATAy0);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345, num, true);

  while(Wire.available())
  {
    buff[n]=Wire.read();
    n++;
  }
  DATA[1]=(int16_t)(buff[0]<<8|buff[1]);
  //Save y axis data to second array spot

  Wire.beginTransmission(ADXL345);
  Wire.write(DATAz1);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345, num, true);
  n = 0;

  while(Wire.available())
    {

      buff[n] = Wire.read();
      n++;    
    }
  
  Wire.beginTransmission(ADXL345);
  Wire.write(DATAz0);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345, num, true);

  while(Wire.available())
  {
    buff[n]=Wire.read();
    n++;
  }
  DATA[2]=(int16_t)(buff[0]<<8|buff[1]);
  //Save z axis data to last array spot

  //Convert to usable format for trig
  DATA[0]=map(DATA[0],-256, 256, -90,90);
  DATA[1]=map(DATA[1],-256,256,-90,90);
  DATA[2]=map(DATA[2],-256, 256, -90,90);

  ANGLE[0] = RAD_TO_DEG * (atan2 (-DATA[1], -DATA[2])+PI); //x angle
  ANGLE[1] = RAD_TO_DEG * (atan2 (-DATA[0], -DATA[2])+PI); //y angle
  ANGLE[2] = RAD_TO_DEG * (atan2 (-DATA[1], -DATA[0])+PI); //z angle

}

void ISRswitch(){
  BRK_bool=true;
  BRK_time=millis();
}