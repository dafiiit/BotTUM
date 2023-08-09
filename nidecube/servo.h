#ifndef SERVO_H
#define SERVO_H

#include <ESP32Servo.h>
#include "globals.h"

class servo{
private:
  int servo_pin;
  int servo_brake_angle = 0;
  int servo_home_angle = 90;
  Servo servo_in_class;

public:
    servo(int servo_pin){
      this->servo_pin = servo_pin;
      servo_in_class.attach(servo_pin); // GPIO-Pin, an dem der Servo angeschlossen ist (kann an deine Verbindung angepasst werden)
    }

    void brake() {
      servo_in_class.write(servo_brake_angle);
    }

    void unbrake(){
      servo_in_class.write(servo_home_angle);
    }
};

#endif