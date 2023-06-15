//deklaration
//Hilfsstrukturen
#ifndef DATENTYPEN_H
#define DATENTYPEN_H
/*
#include <ArduinoEigen.h>

#ifndef INERTIA_H
#define INERTIA_H
class INERTIA {
  private:
    Eigen::Matrix3d inertia;
  public:
    INERTIA(const Eigen::Matrix3d& inertiaMatrix) : inertia(inertiaMatrix) {}
};
#endif

//enthält die Position in relation zum Ursprung
#ifndef POSITION_H
#define POSITION_H
class VEKTOR {
  private:
    float x;
    float y;
    float z;
  public: 
    VEKTOR(float x, float y, float z) : x(x), y(y), z(z) {};
}
#endif

kann durch 
Eigen::Vector3d pos(0.0, 0.0, 0.0);
ersetzt werden

*/
/*
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
*/

//typedef enum {kante_auf_flaeche ,flaeche_auf_kante, flaeche_auf_ecke, ecke_auf_flaeche, ecke_auf_kante, kante_auf_ecke, balancieren_ecke, balancieren_kante} ZUSTAND;
//typedef enum {auf_kante, auf_flaeche, auf_ecke, im_uebergang} USER_ZUSTAND;

/*
typedef enum {nicht_auf_flaeche, f_eins, f_zwei, f_drei, f_vier, f_fünf, f_sechs} FLAECHEN;
typedef enum {nicht_auf_kante, k_eins_zwei, k_eins_drei, k_eins_vier, k_eins_fünf, k_zwei_drei, k_drei_vier, k_vier_fünf, k_fünf_zwei, k_sechs_zwei, k_sechs_drei, k_sechs_vier, k_sechs_fünf} KANTEN;
typedef enum {nicht_auf_ecke, e_eins_zwei_drei, e_eins_drei_vier, e_eins_vier_fünf, e_eins_fünf_zwei, e_sechs_zwei_drei, e_sechs_drei_vier, e_sechs_vier_fünf, e_sechs_fünf_zwei} ECKEN;
*/

//Dieser Array beschreibt alle möglichen Zustände des Systems
int std::alle_zustaende_array[3][8] = {
  {0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 0, 5}, {0, 0, 6}, /*Flächen*/
  {0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 1, 5}, {0, 2, 3}, {0, 3, 4}, {0, 4, 5}, {0, 5, 2}, {0, 6, 2}, {0, 6, 3}, {0, 6, 4}, {0, 6, 5}, /*Kanten*/
  {1, 2, 3}, {1, 3, 4}, {1, 4, 5}, {1, 5, 2}, {6, 2, 3}, {6, 3, 4}, {6, 4, 5}, {6, 5, 2} /*Ecken*/
};

int std::zustands_array[3] =  {0,0,1};

class STEUERUNG{
  private: 
    //initialisieren aller Zustände als NaN
    KANTEN aktuelle_kante = nicht_auf_kante;
    KANTEN ziel_kante = nicht_auf_kante;
    FLAECHEN aktuelle_flaeche = f_eins;           //f_eins ist die Bodenfläche
    FLAECHEN ziel_flaeche = nicht_auf_flaeche;
    ECKEN aktuelle_ecke = nicht_auf_ecke;
    ECKEN ziel_ecke = nicht_auf_ecke;
    
  public: 
    steuerung() {};
    void kante_auf_flaeche(KANTEN aktuelle_kante, FLAECHEN ziel_flaeche) 
      {
      this->aktuelle_kante = aktuelle_kante; 
      this->ziel_flaeche = ziel_flaeche;
      //hier kommt die Implementierung hin
      aktuelle_kante = nicht_auf_kante;
      aktuelle_flaeche = ziel_flaeche;
      aktueller_zustand = 

      };
    void flaeche_auf_kante(FLAECHEN aktuelle_flaeche, KANTEN ziel_kante) 
      {
      this->ziel_kante = ziel_kante; 
      this->aktuelle_flaeche = aktuelle_flaeche;
      //hier kommt die Implementierung hin
      aktuelle_flaeche = nicht_auf_flaeche;
      aktuelle_kante = ziel_kante;
      };
    void flaeche_auf_ecke(FLAECHEN aktuelle_flaeche, ECKEN ziel_ecke) 
      {
      this->aktuelle_flaeche = aktuelle_flaeche; 
      this->ziel_ecke = ziel_ecke;
      //hier kommt die Implementierung hin
      aktuelle_flaeche = nicht_auf_flaeche;
      aktuelle_ecke = ziel_ecke;
      };
    void ecke_auf_flaeche(ECKEN aktuelle_ecke, FLAECHEN ziel_flaeche) 
      {
      this->aktuelle_ecke = aktuelle_ecke;
      this->ziel_flaeche = ziel_flaeche;
      //hier kommt die Implementierung hin
      aktuelle_ecke = nicht_auf_ecke;
      aktuelle_flaeche = ziel_flaeche;
      };
    void ecke_auf_kante(ECKEN aktuelle_ecke, KANTEN ziel_kante) 
      { 
      this->aktuelle_ecke = aktuelle_ecke;
      this->ziel_kante = ziel_kante;
      //hier kommt die Implementierung hin
      aktuelle_ecke = nicht_auf_ecke;
      aktuelle_kante = ziel_kante;
      };
    void kante_auf_ecke(KANTEN aktuelle_kante, ECKEN ziel_ecke) 
      {
      this->aktuelle_kante = aktuelle_kante;
      this->ziel_ecke = ziel_ecke;
      //hier kommt die Implementierung hin
      aktuelle_kante = nicht_auf_kante;
      aktuelle_ecke = ziel_ecke;
      };
    void balancieren_ecke(ECKEN aktuelle_ecke) 
      {
      this->aktuelle_ecke = aktuelle_ecke;
      //hier kommt die Implementierung hin
      };
    void balancieren_kante(KANTEN aktuelle_kante) 
      {
      this->aktuelle_kante = aktuelle_kante;
      //hier kommt die Implementierung hin
      };
};