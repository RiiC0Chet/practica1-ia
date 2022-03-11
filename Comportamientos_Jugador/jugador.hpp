#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      fil = col = 99;
      brujula =0;
      origen = (brujula+2)%4; // origen tiene que apuntar al lugar contrario a donde nos dirigimos
      ultimaAccion = actIDLE;
      girar_derecha = false;
      bien_situados = false;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
  
  // Declarar aquí las variables de estado
  // Con origen alamcenamos desde que posicion venimos (para no volver sobre nuestros pasos)
  int fil, col, brujula, origen;
  Action ultimaAccion;
  bool girar_derecha, bien_situados;
};

#endif
