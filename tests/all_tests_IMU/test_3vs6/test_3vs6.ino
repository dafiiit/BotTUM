#include<Wire.h>
#include<math.h>
#include<ADXL345_WE.h>
#define ADXL345_I2CADDR_1 0x53
#define ADXL345_I2CADDR_2 0x1D
volatile long counter = 0;
int degree=0;
int enc_pin1 =12;
int enc_pin2 =14;
const int numSamples = 200;
float acc1BiasX=0.0, acc1BiasY=0.0, acc1BiasZ=0.0;
float acc2BiasX=0.0, acc2BiasY=0.0, acc2BiasZ=0.0;
float diff_x,diff_y,diff_z;
float g_rotiert_x, g_rotiert_y, g_rotiert_z, Angle_X, Angle_Y, Angle_Z;
/* There are several ways to create your ADXL345 object:
 * ADXL345_WE myAcc = ADXL345_WE()                -> uses Wire / I2C Address = 0x53
 * ADXL345_WE myAcc = ADXL345_WE(ADXL345_I2CADDR) -> uses Wire / ADXL345_I2CADDR
 * ADXL345_WE myAcc = ADXL345_WE(&wire2)          -> uses the TwoWire object wire2 / ADXL345_I2CADDR
 * ADXL345_WE myAcc = ADXL345_WE(&wire2, ADXL345_I2CADDR) -> all together
 */
ADXL345_WE myAcc1 = ADXL345_WE(ADXL345_I2CADDR_1);
ADXL345_WE myAcc2 = ADXL345_WE(ADXL345_I2CADDR_2);
void setup(){
  pinMode(enc_pin1, INPUT_PULLUP);
  pinMode(enc_pin2, INPUT_PULLUP);
  attachInterrupt(enc_pin1, ai0, RISING);
  attachInterrupt(enc_pin2, ai1, RISING);

  ////////////////////////////////////
  
  Wire.begin();
  Serial.begin(9600);
  Serial.println("ADXL345_Sketch - Basic Data");
  Serial.println();
  if(!myAcc1.init()){
    Serial.println("ADXL345_1 not connected!");
  }
   if(!myAcc2.init()){
    Serial.println("ADXL345_2 not connected!");
  }
/* Choose the data rate         Hz
    ADXL345_DATA_RATE_3200    3200
    ADXL345_DATA_RATE_1600    1600
    ADXL345_DATA_RATE_800      800
    ADXL345_DATA_RATE_400      400
    ADXL345_DATA_RATE_200      200
    ADXL345_DATA_RATE_100      100
    ADXL345_DATA_RATE_50        50
    ADXL345_DATA_RATE_25        25
    ADXL345_DATA_RATE_12_5      12.5  
    ADXL345_DATA_RATE_6_25       6.25
    ADXL345_DATA_RATE_3_13       3.13
    ADXL345_DATA_RATE_1_56       1.56
    ADXL345_DATA_RATE_0_78       0.78
    ADXL345_DATA_RATE_0_39       0.39
    ADXL345_DATA_RATE_0_20       0.20
    ADXL345_DATA_RATE_0_10       0.10
*/
  myAcc1.setDataRate(ADXL345_DATA_RATE_100);
  myAcc2.setDataRate(ADXL345_DATA_RATE_100);
  Serial.print("Data rate: ");
  Serial.print(myAcc1.getDataRateAsString());
  Serial.print(myAcc2.getDataRateAsString());
/* In full resolution raw values the size of the raw values depend 
    on the range: 2g = 10 bit; 4g = 11 bit; 8g = 12 bit; 16g =13 bit;
    uncomment to change to 10 bit for all ranges. 
 */
  // myAcc.setFullRes(false);

/* Choose the measurement range
    ADXL345_RANGE_16G    16g     
    ADXL345_RANGE_8G      8g     
    ADXL345_RANGE_4G      4g   
    ADXL345_RANGE_2G      2g
*/ 
  myAcc1.setRange(ADXL345_RANGE_4G);
  myAcc2.setRange(ADXL345_RANGE_4G);
  Serial.print("  /  g-Range: ");
  Serial.println(myAcc1.getRangeAsString());
  Serial.println(myAcc2.getRangeAsString());
  Serial.println();
  
   for (int i = 0; i < numSamples; i++)
   {
  xyzFloat raw1 = myAcc1.getRawValues();
  xyzFloat g1 = myAcc1.getGValues();
  acc1BiasX += g1.x;
  acc1BiasY += g1.y;
  acc1BiasZ += g1.z;
   }
   acc1BiasX /= numSamples;
   acc1BiasY /= numSamples;
   acc1BiasZ /= numSamples;

  for (int j = 0; j < numSamples; j++)
   {
  xyzFloat raw2 = myAcc2.getRawValues();
  xyzFloat g2 = myAcc2.getGValues();
  acc2BiasX += g2.x;
  acc2BiasY += g2.y;
  acc2BiasZ += g2.z;
   }
   acc2BiasX /= numSamples;
   acc2BiasY /= numSamples;
   acc2BiasZ /= numSamples;

/* Uncomment to enable Low Power Mode. It saves power but slightly
    increases noise. LowPower only affetcs Data Rates 12.5 Hz to 400 Hz.
*/
  // myAcc.setLowPower(true);
}

/* The LSB of the Data registers is 3.9 mg (milli-g, not milligramm).
    This value is used calculating g from raw. However, this is an ideal
    value which you might want to calibrate. 
*/

void loop() {
  degree=((counter/1200.0)-(counter/1200))*360;
  Serial.print("degree: ");
  Serial.print(counter);
  Serial.print("/");

  ////////////////////////////////////////////////

  xyzFloat raw1 = myAcc1.getRawValues();
  xyzFloat g1 = myAcc1.getGValues();
  g1.x -= acc1BiasX+1;
  g1.y -= acc1BiasY;
  g1.z -= acc1BiasZ;

  xyzFloat raw2 = myAcc2.getRawValues();
  xyzFloat g2 = myAcc2.getGValues();
  g2.x -= acc2BiasX+1;
  g2.y -= acc2BiasY;
  g2.z -= acc2BiasZ;
  /*
  Serial.print("Raw1-x = ");
  Serial.print(raw1.x);
  Serial.print("  |  Raw1-y = ");
  Serial.print(raw1.y);
  Serial.print("  |  Raw1-z = ");
  Serial.println(raw1.z);
  
  Serial.print("g1-x   = ");
  Serial.print(g1.x);
  Serial.print("  |  g1-y   = ");
  Serial.print(g1.y);
  Serial.print("  |  g1-z   = ");
  Serial.println(g1.z);
  
  Serial.print("Raw2-x = ");
  Serial.print(raw2.x);
  Serial.print("  |  Raw2-y = ");
  Serial.print(raw2.y);
  Serial.print("  |  Raw2-z = ");
  Serial.println(raw2.z);
  
  Serial.print("g2-x   = ");
  Serial.print(g2.x);
  Serial.print("  |  g2-y   = ");
  Serial.print(g2.y);
  Serial.print("  |  g2-z   = ");
  Serial.println(g2.z);
  Serial.println();
  */
  diff_x=g2.x-g1.x;
  diff_y=g2.y-g1.y;
  diff_z=g2.z-g1.z;            //man zieht g sowie nen Anteil von der lin Beschleunigung ab
  /* Serial.print("diff_x=");
  Serial.println(diff_x);
  Serial.print("diff_y=");
  Serial.println(diff_y);
  Serial.print("diff_z=");
  Serial.println(diff_z); */
  diff_x *= 20/150;          // skaliert mit Hebelarm, sodass man letztendlich die linBeschl vom unteren Sensor kriegt
  diff_y *= 20/150;
  diff_z *= 20/150;
  g_rotiert_x= -diff_x+g1.x;   // -linBeschl vom unteren Sensor+ Werte vom unteren Sensor != g 
  g_rotiert_y= -diff_y+g1.y;
  g_rotiert_z= -diff_z+g1.z;
 /* Serial.print("g_rotiert_x=");
  Serial.println(g_rotiert_x);
  Serial.print("g_rotiert_y=");
  Serial.println(g_rotiert_y);
  Serial.print("g_rotiert_z=");
  Serial.println(g_rotiert_z); */
  //Angle_X = atan2(g_rotiert_y, sqrt(pow(g_rotiert_x, 2) + pow(g_rotiert_z, 2))) * 180.0 / PI;
  Angle_Z = atan2(g_rotiert_y, -g_rotiert_x) * 180.0 / PI;
  //Angle_Y = atan2(-g_rotiert_x, sqrt(pow(g_rotiert_y, 2) + pow(g_rotiert_z, 2))) * 180.0 / PI;
  //Serial.print("Angle_X=");
  //Serial.println(Angle_X);
  //Serial.print("Angle_Y=");
  //Serial.println(Angle_Y-90);
  Serial.print("Angle_Z=");
  Serial.println(Angle_Z);
  delay(1000);

/////////////Debug
  if (Serial.available() > 0){
    char inbyte = (char)Serial.read();
    switch (inbyte){
      case 'r': counter = 0; break;
      case 'a': counter = 0; break;
      case 'b': counter = 0; break;
      case 'c': counter = 0; break;
    }
  }
}


void ai0() {
  if(digitalRead(enc_pin2)==LOW) {
  counter++;
  }else{
  counter--;
  }
}

  void ai1() {
  if(digitalRead(enc_pin1)==LOW) {
  counter--;
  }else{
  counter++;
  }
}