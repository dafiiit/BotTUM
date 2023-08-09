#include <Wire.h>
#include <tgmath.h>
// Register Map:
#define ADXL345 0x53 // Adress chosen by grounding SDO
#define DATAx0 0x32
#define DATAx1 0x33
#define DATAy0 0x34
#define DATAy1 0x35
#define DATAz0 0x36
#define DATAz1 0x37
#define POWER_CTL 0x2D
#define DATA_FORMAT 0x31
#define FULLRES_2g B00001000
#define FULLRES_16g B00001011
#define WRITE 0xA6
#define READ 0xA7
// I2C pins:
const int esp32_SCL = 22;
const int esp32_SDA = 21;

void setup()
{

  Serial.begin(9600);
  Serial.println(); // why???
  Serial.println(); // würd ich auch löschen
  Serial.println("Start");
  delay(5);
  Wire.begin(esp32_SDA, esp32_SCL, 100000);

  pinMode(19, INPUT_PULLUP); // als Variablen definieren
  pinMode(2, OUTPUT);        // auch
  attachInterrupt(digitalPinToInterrupt(19), )

      // Setup power management

      Wire.beginTransmission(ADXL345);
  Wire.write(POWER_CTL);
  Wire.write(8); // 15 to binary: 1111, corresponds to 3200Hz data rate and 1600Hz Bandwidth
  Wire.endTransmission(true);
  Serial.println("Powermode & BW_RATE written");
  delay(20);

  // Setup range

  Wire.beginTransmission(ADXL345);
  Wire.write(DATA_FORMAT);
  Wire.write(FULLRES_2g);
  Wire.endTransmission(true);
  Serial.println("Range set to 2g");
  delay(20);

  //

  Serial.println("Setup complete");
  delay(1000);
}

// Axis data init
int x = 0;
int y = 0;
int z = 0;

void loop()
{
  // I2C: MSBfirst, 5mhz max, CS set to HIGH for ADXL necessary
  // Get Accel data

  readDATAX(1);
}

int DATA, lastDATA;
int err = 0;

// Func for reading x axis accelerometer Data. Integer num represents the number of bytes requested from the accelerometer.
void readDATAX(int num)
{

  byte buff[2];

  Wire.beginTransmission(ADXL345);
  Wire.write(DATAx1);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345, num, true);
  int n = 0;

  while (Wire.available())
  {

    buff[n] = Wire.read();
    n++;
  }

  Wire.beginTransmission(ADXL345);
  Wire.write(DATAx0);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345, num, true);

  while (Wire.available())
  {
    buff[n] = Wire.read();
    n++;
  }
  // Refer to fig.49 of Datasheet
  // Format Datatype from byte to 10bit int number

  Wire.endTransmission();

  DATA = (int16_t)(buff[0] << 8 | buff[1]);

  /*
    if(abs(DATA-lastDATA)>=250)
    {
      err++;
      Serial.print("Error caught, n° ");
      Serial.print(err);
      Serial.print("  ");
      Serial.print(DATA-lastDATA);
      Serial.println();
      }
    lastDATA=DATA;
  */
  Serial.println(DATA);
  delay(10); // 100Hz data rate
}

void blink()
{
  Serial.println("Blinked");
  digitalWrite(2, HIGH);
  delay(200);
  digitalWrite(2, LOW);
  delay(200);
  Serial.println("Blinked");
}

/*
void print(double num, bool dir){

      Serial.print("xAccel: "); Serial.print(num); Serial.print("   ");
      if(dir)
      Serial.print(map(num, 255 , 122 , 180 , 360));
      else
      Serial.print(map(num, 0, 132, 0, 180));
      Serial.print("°"); Serial.println(" ");

}
*/
