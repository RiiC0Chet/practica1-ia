#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

void ComportamientoJugador::irHasta(int filas, int columnas)
{
	int dif_filas = filas - fil, // Si es negativo queremos subir 
		dif_colmunas = columnas - col; // Si es negativo a la izq

	//Si es negativo giramos hasta estas ubicados al norte
	if(dif_filas < 0)
	{
		while(brujula != 0)
			cadenaAcciones.push_back(actTURN_R);

		dif_filas = dif_filas * (-1);
	}
	else //Si es positivo giramos hasta estas ubicados al sur
	{
		while(brujula != 2)
			cadenaAcciones.push_back(actTURN_R);
	}
		
	for(int i = 0;i < dif_filas;i++)
		cadenaAcciones.push_back(actFORWARD);

	//Si es negativo giramos hasta estas ubicados al oeste
	if(dif_filas < 0)
	{
		while(brujula != 1)
			cadenaAcciones.push_back(actTURN_R);

		dif_columnas = dif_columnas * (-1);
	}
	else //Si es positivo giramos hasta estas ubicados al este
	{
		while(brujula != 3)
			cadenaAcciones.push_back(actTURN_R);
	}


	for(int i = 0; i < dif_columnas ;i++)
		cadenaAcciones.push_back(actFORWARD);
}

bool ComportamientoJugador::puedoPisar(int pos)
{
	if(bikini && zapatillas)
	{}
	
}

Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;

	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC << " ";
	switch(sensores.sentido){
		case 0: cout << "Norte" << endl; break;
		case 1: cout << "Este" << endl; break;
		case 2: cout << "Sur " << endl; break;
		case 3: cout << "Oeste" << endl; break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << endl;

	switch(ultimaAccion)
	{
		case actFORWARD: // si mi utima accion fue ir para delante
			switch(brujula)
			{
				case 0 : fil--; fil_aux--; break;
				case 1 : col++; col_aux++;  break;
				case 2 : fil++; fil_aux++;break;
				case 3 : col--; col_aux--;break;
			}
		break;

		case actTURN_R: // giramos a la derecha
			brujula = (brujula+1)%4;// ya que trabajamos con 4 valores nada mas
			//girar_izq = (rand()%2 == 0);
		break;

		case actTURN_L: // giramos a la izquierda
			brujula = (brujula+3)%4;// ya que trabajamos con 4 valores nada mas y c++ con valores negativos caca,
			//girar_izq = (rand()%2 == 0);// seria igual si le sumamos 3 ya que va a dar la vuelta al estar en modulo 4
		break;						

	}

	

	cout<< "fil: "<<fil<<endl;
	cout<< "col: "<<col<<endl;
	cout<< "brujula: "<<brujula<<endl;
	cout<< "origen: "<<origen<<endl;
	cout<<"Mirando ha :"<<sensores.terreno[2]<<endl;
	
	if (paredEncontrad){
		cout<<"paredEncontrada es true "<<endl;
	} else {
		cout<<"paredEncontrada es false "<<endl;

	}

	if(sensores.terreno[0] == 'G' && !bien_situados)
	{
		fil = sensores.posF;
		col = sensores.posC;
		bien_situados = true;
	}

	if(sensores.terreno[0] == 'D')
	{
		zapatillas = true;
		
	}

	if(sensores.terreno[0] == 'K')
	{
		bikini = true;
	}

	if (bien_situados)
	{

		switch (brujula)
		{
		case 0:
			mapaResultado[fil][col] = sensores.terreno[0];
			mapaResultado[fil - 1][col - 1] = sensores.terreno[1];
			mapaResultado[fil - 1][col] = sensores.terreno[2];
			mapaResultado[fil - 1][col + 1] = sensores.terreno[3];
			mapaResultado[fil - 2][col - 2] = sensores.terreno[4];
			mapaResultado[fil - 2][col - 1] = sensores.terreno[5];
			mapaResultado[fil - 2][col] = sensores.terreno[6];
			mapaResultado[fil - 2][col + 1] = sensores.terreno[7];
			mapaResultado[fil - 2][col + 2] = sensores.terreno[8];
			mapaResultado[fil - 3][col - 3] = sensores.terreno[9];
			mapaResultado[fil - 3][col - 2] = sensores.terreno[10];
			mapaResultado[fil - 3][col - 1] = sensores.terreno[11];
			mapaResultado[fil - 3][col] = sensores.terreno[12];
			mapaResultado[fil - 3][col + 1] = sensores.terreno[13];
			mapaResultado[fil - 3][col + 2] = sensores.terreno[14];
			mapaResultado[fil - 3][col + 3] = sensores.terreno[15];

			break;

		case 1:
			mapaResultado[fil][col] = sensores.terreno[0];
			mapaResultado[fil - 1][col + 1] = sensores.terreno[1];
			mapaResultado[fil][col + 1] = sensores.terreno[2];
			mapaResultado[fil + 1][col + 1] = sensores.terreno[3];
			mapaResultado[fil - 2][col + 2] = sensores.terreno[4];
			mapaResultado[fil - 1][col + 2] = sensores.terreno[5];
			mapaResultado[fil][col + 2] = sensores.terreno[6];
			mapaResultado[fil + 1][col + 2] = sensores.terreno[7];
			mapaResultado[fil + 2][col + 2] = sensores.terreno[8];
			mapaResultado[fil - 3][col + 3] = sensores.terreno[9];
			mapaResultado[fil - 2][col + 3] = sensores.terreno[10];
			mapaResultado[fil - 1][col + 3] = sensores.terreno[11];
			mapaResultado[fil][col + 3] = sensores.terreno[12];
			mapaResultado[fil + 1][col + 3] = sensores.terreno[13];
			mapaResultado[fil + 2][col + 3] = sensores.terreno[14];
			mapaResultado[fil + 3][col + 3] = sensores.terreno[15];

			break;

		case 2:
			mapaResultado[fil][col] = sensores.terreno[0];
			mapaResultado[fil + 1][col + 1] = sensores.terreno[1];
			mapaResultado[fil + 1][col] = sensores.terreno[2];
			mapaResultado[fil + 1][col - 1] = sensores.terreno[3];
			mapaResultado[fil + 2][col + 2] = sensores.terreno[4];
			mapaResultado[fil + 2][col + 1] = sensores.terreno[5];
			mapaResultado[fil + 2][col] = sensores.terreno[6];
			mapaResultado[fil + 2][col - 1] = sensores.terreno[7];
			mapaResultado[fil + 2][col - 2] = sensores.terreno[8];
			mapaResultado[fil + 3][col + 3] = sensores.terreno[9];
			mapaResultado[fil + 3][col + 2] = sensores.terreno[10];
			mapaResultado[fil + 3][col + 1] = sensores.terreno[11];
			mapaResultado[fil + 3][col] = sensores.terreno[12];
			mapaResultado[fil + 3][col - 1] = sensores.terreno[13];
			mapaResultado[fil + 3][col - 2] = sensores.terreno[14];
			mapaResultado[fil + 3][col - 3] = sensores.terreno[15];

			break;
		case 3:
			mapaResultado[fil][col] = sensores.terreno[0];
			mapaResultado[fil + 1][col - 1] = sensores.terreno[1];
			mapaResultado[fil][col - 1] = sensores.terreno[2];
			mapaResultado[fil - 1][col - 1] = sensores.terreno[3];
			mapaResultado[fil + 2][col - 2] = sensores.terreno[4];
			mapaResultado[fil + 1][col - 2] = sensores.terreno[5];
			mapaResultado[fil][col - 2] = sensores.terreno[6];
			mapaResultado[fil - 1][col - 2] = sensores.terreno[7];
			mapaResultado[fil - 2][col - 2] = sensores.terreno[8];
			mapaResultado[fil + 3][col - 3] = sensores.terreno[9];
			mapaResultado[fil + 2][col - 3] = sensores.terreno[10];
			mapaResultado[fil + 1][col - 3] = sensores.terreno[11];
			mapaResultado[fil][col - 3] = sensores.terreno[12];
			mapaResultado[fil - 1][col - 3] = sensores.terreno[13];
			mapaResultado[fil - 2][col - 3] = sensores.terreno[14];
			mapaResultado[fil - 3][col - 3] = sensores.terreno[15];

			break;
		}
	}

	// Antes de girar a la izquierda o avanzar comprobamos que no hubieramos visitado ya esa posicion
	switch (brujula)
	{
		case 0:
			ya_visitada = ciclo_anterior[fil_aux - 1][col_aux - 1];
			ya_visitada_enfrente = ciclo_anterior[fil_aux - 1][col_aux];
		break;
		case 1:
			ya_visitada = ciclo_anterior[fil_aux - 1][col_aux + 1];
			ya_visitada_enfrente = ciclo_anterior[fil_aux][col_aux + 1];
		break;
		case 2:
			ya_visitada = ciclo_anterior[fil_aux + 1][col_aux + 1];
			ya_visitada_enfrente = ciclo_anterior[fil_aux + 1][col_aux];
		break;
		case 3:
			ya_visitada = ciclo_anterior[fil_aux + 1][col_aux - 1];
			ya_visitada_enfrente = ciclo_anterior[fil_aux][col_aux - 1];
		break;
	}

	// Comprobamos antes de nada si tenemos acciones pendietes en el vector
	if (cadenaAcciones.empty())
	{

		if (girar_izq) // Solo esta activado si hay que girar obligatoriamente porque nos vamos a despegar de la pared
		{
			accion = actTURN_L;
			cout << "Giro a la izq aqui" << endl;

			// Ponemos el girar_izq a false otra vez
			girar_izq = false;
		}
		else if (girar_der)
		{
			accion = actTURN_R;
			cout << "Giro a la der aqui" << endl;

			// Ponemos el girar_izq a false otra vez
			girar_der = false;
		}
		else if ((sensores.terreno[2] == 'T' || sensores.terreno[2] == 'S' || sensores.terreno[2] == 'G' || sensores.terreno[2] == 'D' || sensores.terreno[2] == 'K' || sensores.terreno[2] == 'X') && sensores.superficie[2] == '_' && !ya_visitada_enfrente) // Comprobamos si podriamos avanzar hacia delante
		{
			// Comprobamos si estamos pegados a una pared o no para fijarnos como continua esta
			if (!paredEncontrad)
			{
				accion = actFORWARD;
				cout << "Avanzo" << endl;

				// Almacenamos la posicion
				esta_pintada[fil_aux][col_aux] = true;
			}
			else // En caso de que estemos en pared antes de avanzar nos fijamos en comon continua esta
			{


				// Si es la primera vez que chocamso con una pared almacenamos la posicion para saber cuando hemos dado una vuelta
				if (primeraPared)
				{
					primeraPared = false;
					principio_fil = fil_aux;
					principio_col = col_aux;
				}
				else // Si no es la primera vez que nos chocamos con una pared comprobamos cuando damos la vuelta
				{
					if (fil_aux == principio_fil && col_aux == principio_col)
					{
						girar_der = true;
						principio_fil = fil_aux + 1;
						principio_fil = col_aux - 1;
						// final_ciclo = true;
						for (int i = 0; i < MAX_FILAS; i++)
						{
							for (int j = 0; j < MAX_COLUMNAS; j++)
							{
								ciclo_anterior[i][j] = esta_pintada[i][j];
							}
						}
					}
					else
					{
						// final_ciclo = false;
					}
				}

				// Comprobamos si el hueco [1] podria ser accesible o no ya que eso marcaria cambio en pared y habria que girar a la izquierda
				// (suponiendo que nos movemos siempre hacia la derecha)
				if ((sensores.terreno[1] == 'T' || sensores.terreno[1] == 'S' || sensores.terreno[1] == 'G' || sensores.terreno[1] == 'D' || sensores.terreno[1] == 'K' || sensores.terreno[1] == 'X') && sensores.superficie[1] == '_')
				{
					// Hay que avanzar y luego girar izq
					accion = actFORWARD;
					cout << "Avanzo" << endl;

					// Almacenamos la posicion
					esta_pintada[fil_aux][col_aux] = true;

					if (!ya_visitada) //|| !final_ciclo)
						girar_izq = true;
				}
				else // Si no es el caso avanzamos normal
				{
					accion = actFORWARD;
					cout << "Avanzo" << endl;

					// Almacenamos la posicion
					esta_pintada[fil_aux][col_aux] = true;
				}
			}
		}
		else // En caso de no poder avanzar nos habriamos chocado con un borde y habria que empezar a rodearlo
		{
			// En caso de que la pared no estuviera encontrada ya la marcamos como encontrada
			if (!paredEncontrad)
			{
				paredEncontrad = true;
				// cout<<"WTFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"<<endl;
			}

			accion = actTURN_R;
			cout << "Giro a la der" << endl;
		}
	}
	else
	{
		// Vamos accediendo en orden a las acciones pendientes y vamos eliminandolas;
		accion = cadenaAcciones[0];
		cadenaAcciones.erase(cadenaAcciones.begin());
	}

	ultimaAccion = accion;

	// Determinar el efecto de la ultima accion enviada
	return accion;
}

int ComportamientoJugador::interact(Action accion,int valor){
  return false;
}
