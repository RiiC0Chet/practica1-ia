#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      fil = col = MAX_FILAS;
      brujula = max_giros =0; // max_giros contabiliza el numero de veces que gira sobre si mismo antes de tener que volver sobre sus propios pasos
      origen = (brujula+2)%4; // origen tiene que apuntar al lugar contrario a donde nos dirigimos
      ultimaAccion = actIDLE;
      girar_izq = false;
      bien_situados = false;

      for(int i=0;i<fil;i++)
        for(int j=0;j<col;j++)
          esta_pintada[i][j] = false;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
  
  // Declarar aquí las variables de estado
  // Con origen alamcenamos desde que posicion venimos (para no volver sobre nuestros pasos)

  const int MAX_FILAS = MAX_COLUMNAS = 99;

  int fil, col, brujula, origen, max_giros;
  Action ultimaAccion;
  bool girar_izq, bien_situados, esta_pintada[MAX_FILAS][MAX_COLUMNAS];

  // Creamos un vector con las siguientes acciones a realizar por el personaje
  vector <Action> cadenaAcciones(MAX_FILAS);
};

#endif
