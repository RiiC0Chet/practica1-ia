#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "../include/comportamientos/comportamiento.hpp"
#include <map>
using namespace std;

class ComportamientoJugador : public Comportamiento
{

public:
  ComportamientoJugador(unsigned int size) : Comportamiento(size)
  {
    // Constructor de la clase
    // Dar el valor inicial a las variables de estado
    fil = col = fil_aux = col_aux = 99;
    brujula = max_giros = posicion_vector = esta_en_bucle = has_esperado = num_giros = num_ciclo_sin_descubrir = 0; // max_giros contabiliza el numero de veces que gira sobre si mismo antes de tener que volver sobre sus propios pasos
    origen = (brujula + 2) % 4;                                                                                     // origen tiene que apuntar al lugar contrario a donde nos dirigimos
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
    g_visto = false;
    b_visto = false;
    z_visto = false;
    ha_chocado = false;
    buen_spawn = false;
    cadena_acciones_finalizada = true;
    has_repostado = false;
    avanzar = true;

    for (int i = 0; i < 5; i++)
      ultimasCuatro.push_back(std::make_pair(i * 2, i * 2));

    for (int i = 0; i < MAX_FILAS; i++)
    {
      for (int j = 0; j < MAX_COLUMNAS; j++)
      {
        esta_pintada[i][j] = false;
        ciclo_anterior[i][j] = false;
      }
    }
  }

  ComportamientoJugador(const ComportamientoJugador &comport) : Comportamiento(comport) {}
  ~ComportamientoJugador() {}

  /*
    Movemos al personaje hasta una posicion concreta y hacemos que vuelva a donde estaba
  */
  void irHasta(int filas_inicio, int columnas_inicio, int filas, int columnas);

  /*
    Comprobamos si podemos avanzar hasta esa posicion del sensor
  */
  bool puedoPisar(int pos, Sensores sensores);

  /*
    Comprobamos si ha entrado en bucle
  */
  bool estaEnBucle();

  /*
    Comprobamos si ha explotado y empezamos de 0
  */
  bool restart();

  /*
    Buscamos una posicion, devolviendo un bool y reyenando el par con las posiciones si lo ha encontrado
  */
  bool busca(const char casilla, pair<int, int> &par, Sensores sensores);
  /*
    Comprobamos si estamos rodeando por fuera
  */
  // bool RodeaPorFuera();

  Action think(Sensores sensores);
  int interact(Action accion, int valor);

private:
  // Declarar aquí las variables de estado
  // Con origen alamcenamos desde que posicion venimos (para no volver sobre nuestros pasos)

  const static int MAX_FILAS = 999, MAX_COLUMNAS = 999;

  int fil, col, brujula, origen, max_giros,
      principio_fil, principio_col, // Almacenamos las coordenadas de donde emppiez a recorer la pared
      fil_aux, col_aux,             // fila y columna auxiliar
      posicion_vector,              // Para acceder al vector de ultimas 5
      esta_en_bucle,                // contamos que este en bucle por mas de 2 ciclos
      has_esperado,                 // esperamos unos movimientos para que no se quede ciclando en la misma posicion por una casilla a la que no puede acceder
      num_giros,                    // numero de veces que gira para ver si estamos girando sobre nosotros mismos
      num_ciclo_sin_descubrir;      // numero de ciclos que pasamos sin avanzar

  Action ultimaAccion;
  bool girar_izq, // Con girar_izq comprobamos si hay que girar a la izquierda para no salirse de la pared
      bien_situados,
      esta_pintada[MAX_FILAS][MAX_COLUMNAS], // Matriz donde almacenamos las posiciones visitadas antes de pisar 'G'
      ciclo_anterior[MAX_FILAS][MAX_COLUMNAS],
      primeraPared,               // Recogemos la primera vez que tocamos una pared
      girar_der,                  // Forzamos el giro a la derecha
      ya_visitada,                // comprobamos si esa casilla ya ha sido visitada antes de girar a la izquierda
      final_ciclo,                // Comprobamos si hemos llegado al final de un ciclo
      ya_visitada_enfrente,       // comprobamos que en frente no hayamos estado
      ha_chocado,                 // comprobamos si se ha llegado a chocar o no
      buen_spawn,                 // Comprobamos si hemos encontrado un camino viable hasta tierra en caso de haber spawneado en bosque o agua
      cadena_acciones_finalizada, // comprobamos que las cadenas de acciones totalmente necesarias del vector no se cortan
      has_repostado;              // comprobamos que hayamos estado repostando bateria ya alguna vez en una casilla 'X'

  bool paredEncontrad, // Comporbamos si hemos encontrado pared y estamos pegados para ir mirando si esta se acaba
      bikini,
      zapatillas,
      g_visto, // Almacenamos si ya hemos visto una casilla para no volver hacia ella
      b_visto,
      z_visto,
      avanzar; // comprobamos si estamos en un pasillo parano meterlo en el mapa

  // Creamos un vector con las siguientes acciones a realizar por el personaje
  vector<Action> cadenaAcciones;

  // Creamos un vector de pares donde almacenamos las ultimas 4 posiciones donde ha estado el personaje
  vector<pair<int, int>> ultimasCuatro;

  std::pair<int, int> posiciones, // par auxiliar que iremos utilizando para almacenar coordenadas
      puerta;                     // almacenamos la posicion de alguna puerta para volver cuando estemos un rato sin avanzar

  std::map<pair<int, int>, int> RecuentoPasos; // contamos el numero de veces que pasamos por cada casilla
};

#endif