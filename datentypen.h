//deklaration
//Hilfsstrukturen
#ifndef INERTIA_H
#define INERTIA_H
class INERTIA {
  private:
    double m11, m12, m13;
    double m21, m22, m23;
    double m31, m32, m33;
  public:
    // Konstruktor wird schon hier implementiert
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

//implementierung
// Hier implementieren wir die Klasse Inertia
INERTIA::INERTIA(double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33){
  this->m11 = m11;
  this->m12 = m11;
  this->m13 = m11;
  this->m21 = m11;
  this->m22 = m11;
  this->m23 = m11;
  this->m31 = m11;
  this->m32 = m11;
  this->m33 = m11;
}// noch mal schauen, ob nicht das andere schon die Implementierung ist. 

// Hier implementieren wir die Klasse Position
POSITION::POSITION(double x, double y){
  this->x = x;
  this->y = y;
}

