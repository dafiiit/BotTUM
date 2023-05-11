# Dies ist die Dokumentation zu dem Code des Quadrats

## Code Stuktur

Das ist eine Änderung


```mermaid 
graph TD
a --> b
```
Die Funkitonalität des Codes ist wie folgt unterteilt:
Hier ein Klassendiagramm um zu zeigen, welche Klassen wir haben.

```mermaid
classDiagram
    class Quadrat{
        - double hoehe
        - double hoehe_schwerpunkt
        - double gewicht
        - Matrix3x3 inertia
        - HALLSENSOR hall_sensor
        - IMU imu
        - IMU_6DOF imu_6dof
        - IMU_9DOF imu_9dof
        + Quadrat(...)
        + stand_up(): void
        + balance(): void
        + KannteAufFlaeche(): void
        + FlaecheAufKannte(): void
        + EckeAufKannte(): void
        + KannteAufEcke(): void
        + EckeAufFlaeche(): void
        + FlaecheAufEcke(): void
        + turn_left(): void
        + turn_right(): void
    }

    class INERTIA{
        - double m11
        - double m12
        - double m13
        - double m21
        - double m22
        - double m23
        - double m31
        - double m32
        - double m33
        - double ix
        - double iy
        - double iz
        + Matrix3x3(...)
        + operator()(i: int, j: int): double&
        + operator()(i: int, j: int): double const
    }

    class ROUTE{
        - Vektor_aus_routenelementen
        + plane_Route(Zielort) 
    }
    
    class ROUTENELEMENT{
        - KannteAufFlaeche
        - FlaecheAufKante
        - FlaecheAufEcke
        - EckeAufFlaeche
        - EckeAufKante
        - KanteAufEcke
        +ROUTENELEMENT ROUTENELEMENT(...)
    }

    class POSITION{
        - x
        - y
    }

    class HALLSENSOR{
        - double hall1
        - double hall2
        - double hall3
        + HALLSENSOR(hall1: double, hall2: double, hall3: double)
        + setup_hall()
    }

    class IMU{
        - double x
        - double y
        - double z
        + IMU(x: double, y: double, z: double)
        + setup_imu()
    }

    class IMU_6DOF{
        - double gyro_x
        - double gyro_y
        - double gyro_z
        + IMU_6DOF(...)
    }

    class IMU_9DOF{
        - double mag_x
        - double mag_y
        - double mag_z
        + IMU_9DOF(...)
    }

    

    IMU --> IMU_6DOF 
    IMU_6DOF --> IMU_9DOF
    HALLSENSOR --> Quadrat
    IMU_9DOF --> Quadrat
    INERTIA --> Quadrat
    ROUTENELEMENT --> ROUTE
    ROUTE --> Quadrat
    POSITION --> Quadrat

```