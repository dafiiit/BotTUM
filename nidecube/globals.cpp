#include "globals.h"
#include "globals.h"
#include "hall.h"
#include "mpu6050.h"
#include "pid.h"
#include "motor.h"
#include "servo.h"

// globals.h übernimmt die initialisierung globals.cpp die initialisierung
float cube_torque[3] = {0.0, 0.0, 0.0};
float etc_target_omega = 1234.56;       //etc steht für edge to cube
float ftc_target_omega = 1234.56;       //ftc steht für face to corner
float fte_target_omega = 1234.56;       //fte steht für face to edge
float max_torque = 123.456;             //noch anpassen
float disk_inertia = 123.4;             //noch anpassen
float l = 0.11;                         // cube_edge_length/2
float cube_mass = 1.0;                  // in  kg

float pid_omega_value[3] = { 10, 1, 0.1 };
float pid_omega_punkt_value[3] = { 10, 1, 0.1 };
float pid_change_alpha_value[3] = { 10, 0.2, 0.1 };

float vec_mpu_to_cc[3] = { 1, 1, 1 };  //noch anpassen
float vec_cc_to_cg[3] = { 1, 2, 3 };   //noch anpassen
int mpu_address = 0x68;                //stimmt

// Statische Variable initialisieren
uint8_t hall::isr_used = 0;
hall* hall::my_instance[hall_max_isr];

cube_state_enum cube_state = test_autotune;

label_with_array cc_to_ground[26] = {
  //Flächen
  { "001", { 0, 0, -l } },
  { "002", { l, 0, 0 } },
  { "003", { 0, l, 0 } },
  { "004", { 0, -l, 0 } },
  { "005", { -l, 0, 0 } },
  { "006", { 0, 0, l } },
  //Kanten
  { "012", { l, 0, -l } },
  { "013", { 0, l, -l } },
  { "014", { 0, -l, -l } },
  { "015", { -l, 0, -l } },
  { "062", { l, 0, l } },
  { "063", { 0, l, l } },
  { "064", { 0, -l, l } },
  { "065", { -l, 0, l } },
  { "023", { l, l, 0 } },
  { "024", { l, -l, 0 } },
  { "053", { -l, l, 0 } },
  { "054", { -l, -l, 0 } },
  //Ecken
  { "123", { l, l, -l } },
  { "134", { -l, l, -l } },
  { "145", { -l, -l, -l } },
  { "152", { l, -l, -l } },
  { "623", { l, l, l } },
  { "634", { -l, l, l } },
  { "645", { -l, -l, l } },
  { "652", { l, -l, l } }
};
int cc_to_ground_current = 7;

// Other global variables, objects, and pointers to objects
hall hall_1(35, 32);
mpu6050 mpu(mpu_address);
pid_controller pid_omega(pid_omega_value[0], pid_omega_value[1], pid_omega_value[2]);
pid_controller pid_omega_punkt(pid_omega_punkt_value[0], pid_omega_punkt_value[1], pid_omega_punkt_value[2]);
pid_controller pid_change_alpha(pid_change_alpha_value[0], pid_change_alpha_value[1], pid_change_alpha_value[2]);
motor motor_1(motor_pin_1, direction_pin_1, brake_pin_1, pid_omega, pid_omega_punkt, pid_change_alpha, hall_1);
servo servo_1(servo_pin_1);
