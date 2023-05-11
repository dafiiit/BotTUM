

int Led = 2;         // LED pin
int HallSensor = 19; // Sensor pin
volatile double time_trig;
volatile double time_now;
volatile float time_delta;
float rpm_1;
bool state = false;

void IRAM_ATTR isr()
{
  state = !state;
  time_delta = time_now - time_trig;
  time_trig = time_now;
}

void setup()
{
  pinMode(Led, OUTPUT);
  pinMode(HallSensor, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(HallSensor), isr, RISING);
}
int i = 0;
void loop()
{

  time_now = millis();
  if (time_delta)
  {
    rpm_1 = 1 / (time_delta / 1000) * 60;
    print(rpm_1);
  }

  print(time_delta);
  delay(5);
}

void print(float delta)
{
  Serial.println(delta);
}