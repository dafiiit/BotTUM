//Code für das Quadrat
//deklaration
#ifndef QUADRAT_H
#define QUADRAT_H
class QUADRAT {
  private:
    double hoehe_schwerpunkt;
    double gewicht_body;
    double gewicht_scheibe;
    POSITION position;          //Position des Quadrats
    INERTIA inertia;          // Inertia als Attribut von Quadrat
    HALLSENSOR hall_sensor;     // HallSensor als Attribut von Quadrat
    IMU imu;                    // IMU als Attribut von Quadrat
    IMU_6DOF imu_6dof;          // IMU_6DOF als Attribut von Quadrat
    IMU_9DOF imu_9dof;          // IMU_9DOF als Attribut von Quadrat
  
  public:
    QUADRAT(double hoehe_schwerpunkt, double gewicht_body, double gewicht_scheibe, POSITION position, INERTIA inertia, HALLSENSOR hall_sensor, IMU imu, IMU_6DOF imu_6dof, IMU_9DOF imu_9dof);
    //basic funktionalitäten
    void stand_up();
    void balance();
    //sinnvolle funktionalitäten
    void KannteAufFlaeche();
    void FlaecheAufKannte();
    void EckeAufKannte();
    void KannteAufEcke();
    void EckeAufFlaeche();
    void FlaecheAufEcke();
    //schwere funktionalitäten
    void turn_left();
    void turn_right();
};
#endif

//implementierung
Quadrat_hoehe_schwerpunkt = 0.1 //m über dem Boden
Quadrat_gewicht_body = 0.6 //kg von allem außer der Scheibe/n
Quadrat_gewicht_scheibe = 0.1 //kg pro Scheibe
QUADRAT::QUADRAT(double hoehe_schwerpunkt, double gewicht_body, double gewicht_scheibe, POSITION position, INERTIA inertia, HALLSENSOR hall_sensor, IMU imu, IMU_6DOF imu_6dof, IMU_9DOF imu_9dof);{
  this->hoehe_schwerpunkt = Quadrat_hoehe_schwerpunkt;
  this->gewicht_body = Quadrat_gewicht_body;
  this->gewicht_scheibe = Quadrat_gewicht_scheibe;
}
void QUADRAT::stand_up() {
  Serial.println("stand_up");
}
void QUADRAT::balance() {
  Serial.println("balance");
}
void QUADRAT::KannteAufFlaeche() {
  Serial.println("KannteAufFlaeche");
}
void QUADRAT::FlaecheAufKannte() {
  Serial.println("FlaecheAufKannte");
}
void QUADRAT::EckeAufKannte() {
  Serial.println("EckeAufKannte");
}
void QUADRAT::KannteAufEcke() {
  Serial.println("KannteAufEcke");
}
void QUADRAT::EckeAufFlaeche() {
  Serial.println("EckeAufFlaeche");
}
void QUADRAT::FlaecheAufEcke() {
  Serial.println("FlaecheAufEcke");
}
void QUADRAT::turn_left() {
  Serial.println("turn_left");
}
void QUADRAT::turn_right() {
  Serial.println("turn_right");
}