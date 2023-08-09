#include "hall2.h"

hall2 hall(2, 3);

setup(){
    Serial.begin(9600);
}

loop(){
    Serial.println(hall.get_count());
    delay(1000);
}