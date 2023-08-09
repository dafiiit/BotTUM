#ifndef GLOBALS_H
#define GLOBALS_H

class mpu6050;
class motor;
class hall;
class pid_controller;
class servo;


// Pins stimmen bitte nicht ändern
#define motor_pin_1 26  //!
#define direction_pin_1 27
#define brake_pin_1 25  //!

#define motor_pin_2 25
#define direction_pin_2 26
#define brake_pin_2 33

#define motor_pin_3 13
#define direction_pin_3 9
#define brake_pin_3 12

#define servo_pin_1   1
#define servo_pin_2   3
#define servo_pin_3   19

#define hall_max_isr 3

extern float etc_target_omega;
extern float ftc_target_omega;
extern float fte_target_omega;
extern float max_torque;
extern float disk_inertia;
extern float l;
extern float cube_mass;
extern float cube_torque[3];

//Arrays
extern float pid_omega_value[3];
extern float pid_omega_punkt_value[3];
extern float pid_change_alpha_value[3];
extern float vec_mpu_to_cc[3];
extern float vec_cc_to_cg[3];
extern int mpu_address;
extern float vec_cc_to_ground[3];

enum cube_state_enum {
  home,
  test_autotune,
  slow_wheels_on_face,
  slow_wheels_on_edge,
  slow_wheels_on_corner,
  balence_edge,
  balence_corner,
  face_to_edge,
  face_to_corner,
  edge_to_corner,
  edge_to_face,
  corner_to_face,
  corner_to_edge
};
extern cube_state_enum cube_state;

struct label_with_array {
  const char* label;
  float values[3];
};
extern label_with_array cc_to_ground[26];
extern int cc_to_ground_current;

extern hall hall_1;
extern mpu6050 mpu;
extern pid_controller pid_omega;
extern pid_controller pid_omega_punkt;
extern pid_controller pid_change_alpha;
extern motor motor_1;
extern servo servo_1;

#endif  // GLOBALS_H
