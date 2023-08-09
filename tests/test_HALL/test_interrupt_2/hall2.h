
#ifndef HALL2_H
#define HALL2_H

class hall2
{
private:
    int pin_a;
    int pin_b;
    int count;

public:
    hall2(int pin_a, int pin_b){
        this->pin_a = pin_a;
        this->pin_b = pin_b;
        pinMode(pin_a, INPUT);
        pinMode(pin_b, INPUT);

    };
    ~hall2();
    void interrupt_a(){
        count++;
    };
    void interrupt_b(){
        count--;
    };
    int get_count(){
        return count;
        count = 0;
    };
};
attachInterrupt(digitalPinToInterrupt(pin_a), interrupt_a, RISING);
attachInterrupt(digitalPinToInterrupt(pin_b), interrupt_b, RISING);
#endif