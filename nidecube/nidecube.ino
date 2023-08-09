#include <pidautotuner.h>
#include <Wire.h>
#include <algorithm>
#include <Arduino.h>

#include "mpu6050.h"
#include "motor.h"
#include "pid.h"
#include "hall.h"
#include "vektorrechnung.h"
#include "globals.h"
#include "servo.h"

extern motor motor_1;
extern hall hall_1;
extern mpu6050 mpu;
extern servo servo_1;

int loopInterval = 10;
void setup() {
  
  Serial.begin(115200);
  mpu.initialize();
  mpu.calibrate();  // Führe die Kalibrierung aus
  //delay(1000);*/

  // alles für hall
  //if (!hall_1.begin()) { Serial.println("Failed to start hall_1"); }
  //if (!hall_2.begin()){Serial.println("Failed to start hall_2");}
  //if (!hall_3.begin()){Serial.println("Failed to start hall_3");}

  //ab hier autotuner fürs schwungrad
  /*
  PIDAutotuner tuner = PIDAutotuner();
  tuner.setTargetInputValue(0.4);       //Hier die Ziel Beschleunigung der Achwungscheibe eintragen
  tuner.setLoopInterval(loopInterval);  //delay von 100 einbauen und die Zeit messen, welche zum ausführen der loop benötigt wird
  tuner.setOutputRange(-255, 255);
  tuner.setZNMode(PIDAutotuner::ZNModeBasicPID);
  tuner.startTuningLoop(micros());
  long microseconds;
  while (!tuner.isFinished()) {
    if (aktuellezeit = 0){
      aktuellezeit = micros();
    }
     
    // This loop must run at the same speed as the PID control loop being tuned
    long prevMicroseconds = microseconds;
    microseconds = micros();
    // Get input value here (temperature, encoder position, velocity, etc)
    double input = hall_1.get_omega_punkt();

    // Call tunePID() with the input value and current time in microseconds
    double output = tuner.tunePID(input, microseconds);

    // Set the output - tunePid() will return values within the range configured
    // by setOutputRange(). Don't change the value or the tuning results will be
    // incorrect.
    motor_1.run_at_pwm(output);

    // This loop must run at the same speed as the PID control loop being tuned
    while (micros() - microseconds < loopInterval) delayMicroseconds(1);
  }
  // Get PID gains - set your PID controller's gains to these
  double kp = tuner.getKp();
  double ki = tuner.getKi();
  double kd = tuner.getKd();
  */
};

void loop(){

  
  switch (cube_state) {
    /*
    case home:
      // Von hier aus werden alle Aktionen unternommen =)
      if (hall_1.get_omega() > 0.5 or hall_2.get_omega()>0.5 hall_3.get_omega()>0.5) {
        cube_state = slow_wheels_on_face;
      } else {
        mpu.get_cc_to_ground(cc_to_ground[cc_to_ground_current].values);  //diese Zeile stimmt noch nicht
      }
      break;

    case test_autotune:
      // Code für den Zustand "test_autotune"
      break;

    case slow_wheels_on_face:
      if (hall_1.get_omega() > 0.5 /*or hall_2.get_omega()>0.5 hall_3.get_omega()>0.5) {
        cube_state = home;
      } else {
        motor_1.brake();
        //motor_2.brake();
        //motor_3.brake();
      }
      break;

    case slow_wheels_on_edge:
      Serial.print("cube_state = slow_wheels_on_edge");
      // Code für den Zustand 
      break;

    case slow_wheels_on_corner:
      Serial.print("cube_state = slow_wheels_on_corner");
      // Code für den Zustand "slow_wheels_on_corner"
      break;

    case balence_edge:
      //hier könnte man evtl. noch einbauen, dass sich nur ein Rad dreht
      mpu.get_torque();
      motor_1.run(cube_torque[0]);
      break;

    case balence_corner:
      mpu.get_torque();
      motor_1.run(cube_torque[0]);
      //motor_2.run(cube_torque[1]);
      //motor_3.run(cube_torque[2]);
      break;

    case face_to_edge:
      motor_1.run_at_omega(fte_target_omega);
      if (hall_1.get_omega() >= fte_target_omega){
        motor_1.brake();
        servo_1.brake();
      }
      break;

    case face_to_corner:
      motor_1.run_at_omega(ftc_target_omega);
      //motor_2.run_at_omega(ftc_target_omega);
      if (hall_1.get_omega() >= ftc_target_omega and hall_2.get_omega() >= ftc_target_omega){
        motor_1.brake();
        //motor_2.brake();
        servo_1.brake();
        //servo_2.brake();
      }
      break;

    case edge_to_corner:
      //erstmal der Code um auf der Kante zu balancieren
      mpu.get_torque();
      motor_1.run(cube_torque[0]);
      
      //die beiden anderen Motoren sollen auf die Zieldrehzahl hochdrehen
      //motor_2.run_at_omega(etc_target_omega);
      //motor_3.run_at_omega(etc_target_omega);
      if (hall_2.get_omega() >= etc_target_omega and hall_3.get_omega() >= etc_target_omega){
        motor_1.brake();
        //motor_2.brake();
        servo_1.brake();
        //servo_2.brake();
      }
      break;

    case edge_to_face:
      mpu.get_torque();
      motor_1.run(cube_torque[0]+50.0); //unbalanciert, daher sollte der Cube gezielt fallen
      break;

    case corner_to_face:
      // Code für den Zustand "corner_to_face"
      break;

    case corner_to_edge:
      // Code für den Zustand "corner_to_edge"
      break;

    default:
      // Code für den Fall, dass der Zustand nicht erkannt wird
      Serial.print("Zustand konnte nicht erkannt werden. Fatal Error. ");
      break;
  }
  */
  // unsigned long startTime = micros();  // Startzeit erfassen

  // Testen von imu
  //mpu.read_data(accel, gyro);
  mpu.get_torque();
  String output = String(cube_torque[0]) + "," + String(cube_torque[1]) + "," + String(cube_torque[2]);
  motor_1.run(cube_torque[0]);
  Serial.println(output);
  //String output2 = String(gyro[0]) + "," + String(gyro[1]) + "," + String(gyro[2]);
  //Serial.println(output2);

  // Testen des Motors
  // motor_1.run(cube_angle[0]);
  //motor_1.run_at_pwm(200);
  // motor_1.run_at_omega(1);

  //double omegap1 = hall_1.get_omega();
  //Serial.println(omegap1);

  /*
  // Ausführungszeit berechnen
  unsigned long executionTime = micros() - startTime;
  Serial.print("Loop-Ausführungszeit: ");
  Serial.print(executionTime);
  Serial.println(" Mikrosekunden");
  */
};
