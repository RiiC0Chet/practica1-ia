#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "../include/comportamientos/comportamiento.hpp"
using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      fil = col = fil_aux = col_aux = 99;
      brujula = max_giros =0; // max_giros contabiliza el numero de veces que gira sobre si mismo antes de tener que volver sobre sus propios pasos
      origen = (brujula+2)%4; // origen tiene que apuntar al lugar contrario a donde nos dirigimos
      ultimaAccion = actIDLE;
      girar_izq = false;
      bien_situados = false;
      primeraPared = true;
      paredEncontrad = false;
      girar_der = false;
      ya_visitada = false;
      final_ciclo = false;
      ya_visitada_enfrente = false;
      bikini = false;
      zapatillas = false;

      for(int i=0;i<MAX_FILAS;i++)
      {
        for(int j=0;j<MAX_COLUMNAS;j++)
        {
          esta_pintada[i][j] = false;
          ciclo_anterior[i][j] = false;
        }
      }
        
          
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    /*
      Movemos al personaje hasta una posicion concreta y hacemos que vuelva a donde estaba
    */
    void irHasta(int filas, int columnas);

    /*
      Comprobamos si podemos avanzar hasta esa posicion del sensor
    */
    bool puedoPisar(int pos);


    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
  
  // Declarar aquí las variables de estado
  // Con origen alamcenamos desde que posicion venimos (para no volver sobre nuestros pasos)

  const static int MAX_FILAS = 999, MAX_COLUMNAS = 999;

  int fil, col, brujula, origen, max_giros,
      principio_fil, principio_col, //Almacenamos las coordenadas de donde emppiez a recorer la pared
      fil_aux,col_aux; // fila y columna auxiliar
  Action ultimaAccion;
  bool girar_izq, // Con girar_izq comprobamos si hay que girar a la izquierda para no salirse de la pared
        bien_situados, 
        esta_pintada[MAX_FILAS][MAX_COLUMNAS], // Matriz donde almacenamos las posiciones visitadas antes de pisar 'G'
        ciclo_anterior[MAX_FILAS][MAX_COLUMNAS],
        primeraPared, // Recogemos la primera vez que tocamos una pared
        girar_der, // Forzamos el giro a la derecha
        ya_visitada, // comprobamos si esa casilla ya ha sido visitada antes de girar a la izquierda
        final_ciclo, // Comprobamos si hemos llegado al final de un ciclo
        ya_visitada_enfrente; // comprobamos que en frente no hayamos estado

  bool paredEncontrad, // Comporbamos si hemos encontrado pared y estamos pegados para ir mirando si esta se acaba
       bikini,
       zapatillas;
  // Creamos un vector con las siguientes acciones a realizar por el personaje
  vector <Action> cadenaAcciones;
};

#endif
