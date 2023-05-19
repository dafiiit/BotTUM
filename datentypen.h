//deklaration
//Hilfsstrukturen
#include <Eigen>

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

// Hier implementieren wir die Klasse Position
POSITION::POSITION(double x, double y){
  this->x = x;
  this->y = y;
}

