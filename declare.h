//Diese Datei ist zur implementierung der Klassen gedacht.

// Hier definieren wir die Klasse Quadrat mit den privaten Attributen hoehe, schwerpunkt und Gewicht
#include "header.h"
#include <cmath>
#include <Wire.h>
#include <tgmath.h>

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

#ifndef HALLSENSOR_H
#define HALLSENSOR_H
class HALLSENSOR {
  private: 
    double HallSensor_phi_p_s;
    int HallSensor_pin;
    unsigned long HallSensor_previous_time = 0;
    int HallSensor_anz_magneten = 2;
  
  public:
    HALLSENSOR(double HallSensor_phi_p_s, int HallSensor_pin);
    void hall_setup();
    double getHallPhiPS();
    
  private:
    static void pin_ISR();
    double calculateAngularVelocity(int x, double timeInSeconds);
};
#endif

#ifndef IMU_H
#define IMU_H
class IMU {
  private: 
    double x;
    double y;
    double z;
    double pin_SCL;
    double pin_SCA;
  
  public:
    IMU(double x, double y, double z, double pin_SCL, double pin_SCA);
    void imu_setup();
};

#endif

#ifndef IMU_6DOF_H
#define IMU_6DOF_H
class IMU_6DOF : public IMU {
  private: 
    double gyro_x;
    double gyro_y;
    double gyro_z;
  public:
      IMU_6DOF(double x, double y, double z, double gyro_x, double gyro_y, double gyro_z, double pin_SCL, double pin_SCA);
};
#endif

#ifndef IMU_9DOF_H
#define IMU_9DOF_H
class IMU_9DOF : public IMU_6DOF {
    private: 
        double mag_x;
        double mag_y;
        double mag_z;
    
    public:
        IMU_9DOF(double x, double y, double z, double gyro_x, double gyro_y, double gyro_z, double mag_x, double mag_y, double mag_z, , double pin_SCL, double pin_SCA);
};
#endif

//Hilfsstrukturen
#ifndef INERTIA_H
#define INERTIA_H
class INERTIA {
    private:
        double m11, m12, m13;
        double m21, m22, m23;
        double m31, m32, m33;
    public:
        // Konstruktor
        INERTIA(double m11, double m12, double m13,
                double m21, double m22, double m23,
                double m31, double m32, double m33)
            : m11(m11), m12(m12), m13(m13),
            m21(m21), m22(m22), m23(m23),
            m31(m31), m32(m32), m33(m33){}

        // Elementzugriffsfunktionen
        double& operator()(int i, int j) {
            switch (i) {
            case 0:
                switch (j) {
                case 0: return m11;
                case 1: return m12;
                case 2: return m13;
                }
            case 1:
                switch (j) {
                case 0: return m21;
                case 1: return m22;
                case 2: return m23;
                }
            case 2:
                switch (j) {
                case 0: return m31;
                case 1: return m32;
                case 2: return m33;
                }
            }
        }

        double operator()(int i, int j) const {
            switch (i) {
            case 0:
                switch (j) {
                case 0: return m11;
                case 1: return m12;
                case 2: return m13;
                }
            case 1:
                switch (j) {
                case 0: return m21;
                case 1: return m22;
                case 2: return m23;
                }
            case 2:
                switch (j) {
                case 0: return m31;
                case 1: return m32;
                case 2: return m33;
                }
            }
        }
};
#endif

//enthält die Position in relation zum Ursprung
#ifndef POSITION_H
#define POSITION_H
class POSITION {
  private:
    double x;
    double y;
  public: 
    POSITION(double x, double y);
}
#endif

#ifndef ROUTE_H
#define ROUTE_H
class ROUTE{
  private: 
    //hier soll ein Vektor aus Routenelementen, welcher die zukünftige Route beschreibt hinein
  public: 
    ROUTE(ROUTENVEKTOR routenvektor);
    void plane_route(POSITION ziel);   
}
#endif

#ifndef ROUTENELEMENT_H
#define ROUTENELEMENT_H
class ROUTENELEMENT{
  private: 
    bool KannteAufFlaeche;
    bool FlaecheAufKante;
    bool FlaecheAufEcke;
    bool EckeAufFlaeche;
    bool EckeAufKante;
    bool KanteAufEcke;
  public: 
    ROUTENELEMENT(bool KannteAufFlaeche, bool FlaecheAufKante, bool FlaecheAufEcke, bool EckeAufFlaeche, bool EckeAufKante, bool KanteAufEcke);
    void setRoutenelement();   //sorgt dafür, dass immmer nur ein Bool Wert True wird. Benötigt noch eine übergabe.
}
#endif