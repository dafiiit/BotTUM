//kompiliert
#define max_isr 3

class hall {
public:
  hall(uint8_t pin_a, uint8_t pin_b)
    : pin_a(pin_a), pin_b(pin_b), counter(0), last_time(0) {}

  bool begin() {
    int8_t irq_a = digitalPinToInterrupt(pin_a);
    int8_t irq_b = digitalPinToInterrupt(pin_b);

    if (irq_a != NOT_AN_INTERRUPT && irq_b != NOT_AN_INTERRUPT) {
      pinMode(pin_a, INPUT_PULLUP);
      pinMode(pin_b, INPUT_PULLUP);

      isr_ID = UINT8_MAX;
      for (uint8_t i = 0; i < max_isr; i++) {
        if (!(isr_used & _BV(i))) {
          isr_ID = i;
          my_instance[isr_ID] = this;
          isr_used |= _BV(isr_ID);
          break;
        }
      }
    
      {
        static void((*isr_func[max_isr])(void)) = {
          global_isr_0,
          global_isr_1,
          global_isr_2,
        };

        if (isr_ID != UINT8_MAX) {
          attachInterrupt(irq_a, isr_func[isr_ID], RISING);
          attachInterrupt(irq_b, isr_func[isr_ID], RISING);
        } else {
          irq_a = NOT_AN_INTERRUPT;
          irq_b = NOT_AN_INTERRUPT;
        }
      }

      reset();
    }

    return (irq_a != NOT_AN_INTERRUPT && irq_b != NOT_AN_INTERRUPT);
  }

  inline void reset() {
    counter = 0;
    last_time = micros();
  }

  int get_counter() {
    return counter;
  }

  double get_omega() {
    if (start_time == 0) {
      start_time = micros();
      }
    if ((start_time + 10000) < micros()) {
      current_time = micros();
      delta_counter = counter - last_counter;
      last_counter = counter;
      omega = (1000000.0 * delta_counter) / ((double)(current_time - last_time) * 380.0);
      last_time = current_time;
      
      start_time = 0;
    }
  return omega;
  }

private:
  uint8_t pin_a;
  uint8_t pin_b;
  uint8_t isr_ID;
  volatile int counter;
  volatile int last_counter = 0;
  unsigned long last_time;
  unsigned long start_time = 0;

  static uint8_t isr_used;
  static hall* my_instance[max_isr];

  unsigned long current_time;
  double delta_counter;
  double omega;

  void instance_isr() {
    if (digitalRead(pin_a) == LOW) {
      counter++;
    } else {
      counter--;
    }
    if (digitalRead(pin_b) == LOW) {
      counter--;
    } else {
      counter++;
    }
  }

  static void global_isr_0() {
    my_instance[0]->instance_isr();
  }
  static void global_isr_1() {
    my_instance[1]->instance_isr();
  }
  static void global_isr_2() {
    my_instance[2]->instance_isr();
  }
};

uint8_t hall::isr_used = 0;
hall* hall::my_instance[max_isr];

hall hall_1(32, 35);
//hall hall_2(27, 14);
//hall hall_3(10, 11);

double omega1;

void setup() {
  Serial.begin(115200);
  Serial.print("Setup");

  if (!hall_1.begin()) { Serial.println("Failed to start hall_1"); }
  //if (!hall_2.begin()) { Serial.println("Failed to start hall_2"); }
  //if (!hall_3.begin()) { Serial.println("Failed to start hall_3"); }
}

void loop() {
  int counter1 = hall_1.get_counter();
  omega1 = hall_1.get_omega();
  
  //Serial.println(counter1);
  Serial.println(omega1);
  delay(1000);
}
