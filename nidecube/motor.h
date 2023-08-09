#ifndef MOTOR_H
#define MOTOR_H

#include "pid.h"
#include "hall.h"
#include "globals.h"

class motor {
private:
  int motor_pin, direction_pin, brake_pin;
  float p, i, d;
  float p_omega, i_omega, d_omega;

  pid_controller& pid_omega;
  pid_controller& pid_omega_punkt;
  pid_controller& pid_change_alpha;
  hall& hall_pointer;

  int torque_to_pwm(float torque) {
    //return (max_torque/torque)*255; //nur für torque control

    // Falls das nicht funktioniert folgenden Code nutzen
    float target_omega_punkt = torque / disk_inertia;                     //bei 5cm auslenkung ca. : m*g*0.05 / disk_intertia
    float current_omega_punkt = (float)hall_pointer.get_omega_punkt();    //bei 5cm auslenkung ca. :
    return round(pid_omega_punkt.compute(current_omega_punkt, target_omega_punkt));
  }

public:
  motor(int motor_pin, int direction_pin, int brake_pin, pid_controller& pid_omega, pid_controller& pid_omega_punkt, pid_controller& pid_change_alpha, hall& hall_pointer)
    : pid_omega(pid_omega), pid_omega_punkt(pid_omega_punkt), pid_change_alpha(pid_change_alpha), hall_pointer(hall_pointer) {
    this->motor_pin = motor_pin;
    this->direction_pin = direction_pin;
    this->brake_pin = brake_pin;

    pinMode(this->motor_pin, OUTPUT);
    pinMode(this->direction_pin, OUTPUT);
    pinMode(this->brake_pin, OUTPUT);
  }

  void run(float motor_torque) {
    digitalWrite(brake_pin, HIGH);
    int pwm = torque_to_pwm(motor_torque);
    //float pid_alpha_changer = pid_change_alpha.compute(motor_torque, 0);  //motor torque ist quasi die Abweichung und 0 das Ziel
    if (pwm > 255 or pwm < -255) {
      brake();
    }
    //pwm += (int)round(pid_alpha_changer);
    run_at_pwm(pwm);
    Serial.println(pwm);
  }

  void brake() {
    digitalWrite(brake_pin, LOW);
    digitalWrite(motor_pin, 255);
  }

  void run_at_pwm(int pwm) {
    digitalWrite(brake_pin, HIGH);
    if (pwm < 0) {
      digitalWrite(direction_pin, LOW);
    } else {
      digitalWrite(direction_pin, HIGH);
    }
    analogWrite(motor_pin, 255 - pwm);
  }

  void run_at_omega(float omega) {
    //aktuelles omega holen
    double current_omega = hall_pointer.get_omega();
    float difference = omega - current_omega;
    //pid wert berechnen
    float pid_pwm = pid_omega.compute(difference, 0.0);
    //motor ansteuern
    run_at_pwm(pid_pwm);
  }
};
#endif
