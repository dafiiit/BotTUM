# Dies ist die Dokumentation zu dem Code des Quadrats

## Code Stuktur
Die Funkitonalität des Codes ist wie folgt unterteilt:

```mermaid 
graph TD
IMU --> interrupt_IMU
HALL_Sensor --> interrupt_HALL
interrupt_HALL & interrupt_IMU --> Steuerung --> aufstehen & balancieren

```

Hier ein Klassendiagramm um zu zeigen, welche Klassen ich nutze

```mermaid
classDiagram
IMU --> cube
IMU: x,y,z
IMU: r_x, r_y, r_z
IMU: read_IMU()


HALL --> cube
HALL: phi_p_s
HALL: read_HALL() 

cube: stand_up()
cube: balance()

```

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
        + Quadrat(hoehe_schwerpunkt: double, schwerpunkt: double, gewicht: double, features: FEATURES, hall_sensor: HALLSENSOR, imu: IMU, imu_6dof: IMU_6DOF, imu_9dof: IMU_9DOF)
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
        + getHoehecSchwerpunkt(): double
        + getSchwerpunkt(): double
        + getGewicht(): double
    }
```

```mermaid
classDiagram
    class Matrix3x3{
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
        + Matrix3x3(m11: double, m12: double, m13: double, m21: double, m22: double, m23: double, m31: double, m32: double, m33: double, ix: double, iy: double, iz: double)
        + operator()(i: int, j: int): double&
        + operator()(i: int, j: int): double const
        + getInertiaX(): double
        + getInertiaY(): double
        + getInertiaZ(): double
    }
```

```mermaid
classDiagram
    class HALLSENSOR{
        - double hall1
        - double hall2
        - double hall3
        + HALLSENSOR(hall1: double, hall2: double, hall3: double)
        + getHall1(): double
        + getHall2(): double
        + getHall3(): double
    }
```

```mermaid
classDiagram
    class IMU{
        - double x
        - double y
        - double z
        + IMU(x: double, y: double, z: double)
        + getX(): double
        + getY(): double
        + getZ(): double
    }
```

```mermaid
classDiagram
    class IMU_6DOF{
        - double gyro_x
        - double gyro_y
        - double gyro_z
        + IMU_6DOF(x: double, y: double, z: double, gyro_x: double, gyro_y: double, gyro_z: double)
        + getGyroX(): double
        + getGyroY(): double
        + getGyroZ(): double
    }
```

```mermaid
classDiagram
    class IMU_9DOF{
        - double mag_x
        - double mag_y
        - double mag_z
        + IMU_9DOF(x: double, y: double, z: double, gyro_x: double, gyro_y: double, gyro_z: double, mag_x: double, mag_y: double, mag_z: double)
        + getMagX(): double
        + getMagY(): double
        + getMagZ(): double
    }
```