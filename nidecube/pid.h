#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
class pid_controller {
private:
  float p, i, d;           // Proportionaler, Integraler, Differenzieller Verstärkungsfaktor
  float error_sum = 0.0;   // Summe der Fehler für die I-Komponente
  float last_error = 0.0;  // Letzter Fehlerwert für die D-Komponente
  float output = 0.0;      // Ausgangswert des Reglers

public:
  pid_controller(float p, float i, float d) {
    this->p = p;
    this->i = i;
    this->d = d;
  }
  float compute(float current_value, float target_value) {
    float error = target_value - current_value;
    error_sum += error;
    float dError = error - last_error;
    last_error = error;

    // Berechnung der Reglerausgabe
    return output = p * error + i * error_sum + d * dError;
  }
};
#endif
