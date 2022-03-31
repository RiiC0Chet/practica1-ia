#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

void ComportamientoJugador::irHasta(int filas_inicio, int columnas_inicio,int filas, int columnas)
{
	int dif_filas = filas - filas_inicio, // Si es negativo queremos subir 
		dif_columnas = columnas - columnas_inicio; // Si es negativo a la izq

	int brujula_aux = brujula; // brujula auxiliar para los while

	//Si es negativo giramos hasta estas ubicados al norte
	if(dif_filas < 0)
	{
		while(brujula_aux != 0) 
		{
			cadenaAcciones.push_back(actTURN_R);
			brujula_aux = (brujula_aux+1)%4;
		}
			

		dif_filas = dif_filas * (-1);
	}
	else //Si es positivo giramos hasta estas ubicados al sur
	{
		while(brujula_aux != 2)
		{
			cadenaAcciones.push_back(actTURN_R);
			brujula_aux = (brujula_aux+1)%4;
		}
			
	}
		
	for(int i = 0;i < dif_filas;i++)
		cadenaAcciones.push_back(actFORWARD);

	//Si es negativo giramos hasta estas ubicados al oeste
	if(dif_columnas < 0)
	{
		while(brujula_aux != 3)
		{
			cadenaAcciones.push_back(actTURN_R);
			brujula_aux = (brujula_aux+1)%4;
		}
			

		dif_columnas = dif_columnas * (-1);
	}
	else //Si es positivo giramos hasta estas ubicados al este
	{
		while(brujula_aux != 1)
		{
			cadenaAcciones.push_back(actTURN_R);
			brujula_aux = (brujula_aux+1)%4;
		}
			
	}


	for(int i = 0; i < dif_columnas ;i++)
		cadenaAcciones.push_back(actFORWARD);
}

bool ComportamientoJugador::puedoPisar(int pos , Sensores sensores)
{
	if(bikini && zapatillas)
	{
		if((sensores.terreno[pos] == 'T' || sensores.terreno[pos] == 'S' || sensores.terreno[pos] == 'G' || sensores.terreno[pos] == 'D' || sensores.terreno[pos] == 'K' || sensores.terreno[pos] == 'X' || sensores.terreno[pos] == 'A' || sensores.terreno[pos] == 'B' ) && sensores.superficie[pos] == '_')
			return true;
	}
	else if(bikini)
	{
		if((sensores.terreno[pos] == 'T' || sensores.terreno[pos] == 'S' || sensores.terreno[pos] == 'G' || sensores.terreno[pos] == 'D' || sensores.terreno[pos] == 'K' || sensores.terreno[pos] == 'X' || sensores.terreno[pos] == 'A' ) && sensores.superficie[pos] == '_')
			return true;
	}
	else if (zapatillas)
	{
		if((sensores.terreno[pos] == 'T' || sensores.terreno[pos] == 'S' || sensores.terreno[pos] == 'G' || sensores.terreno[pos] == 'D' || sensores.terreno[pos] == 'K' || sensores.terreno[pos] == 'X' || sensores.terreno[pos] == 'B' ) && sensores.superficie[pos] == '_')
			return true;
	}
	else
	{
		if((sensores.terreno[pos] == 'T' || sensores.terreno[pos] == 'S' || sensores.terreno[pos] == 'G' || sensores.terreno[pos] == 'D' || sensores.terreno[pos] == 'K' || sensores.terreno[pos] == 'X' ) && sensores.superficie[pos] == '_')
			return true;
	}

	// Cuando nos chocamos con algo reseteamos el ciclo
	//if(sensores.superficie[pos] != '_')
	//{
	//	paredEncontrad = false;
	//	ha_chocado = true;
	//}

	return false;
}

bool ComportamientoJugador::estaEnBucle()
{
	int filas_coincidentes = 0,
		columnas_coincidentes = 0;
	
	for(int i=0;i<ultimasCuatro.size();++i)
	{
		for(int j=0;j<ultimasCuatro.size();++j)
		{
			if(ultimasCuatro[i].first == ultimasCuatro[j].first)
				filas_coincidentes++;
			if(ultimasCuatro[i].second == ultimasCuatro[j].second)
				columnas_coincidentes++;
		}
	}

	// tienen que coincidir cada uno 8 veces para qued este en bucle
	if( filas_coincidentes == 8 && columnas_coincidentes == 8)
		return true;
	else
		return false;

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

			// avanzamos modulo 4 en el vectoir de las ultimas 4
			posicion_vector = (posicion_vector+1)%4;

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
		//paredEncontrad = false;
	}

	if(sensores.terreno[0] == 'D' && !zapatillas)
	{
		zapatillas = true;
		paredEncontrad = false;
		primeraPared = true;
	}

	if(sensores.terreno[0] == 'K' && !bikini)
	{
		bikini = true;
		paredEncontrad = false;
		primeraPared = true;
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


	//cout<<"Hay zapatillas? "<<zapatillas<<z_visto<<endl;
	
// Comprobammos con los sensores si estamos viendo alguna de estas casillas
		if (!bikini || !zapatillas || !bien_situados)
		{
			// Definimos las dos variables locales que nos serviran para representar las posiciones del cada casilla del sensor en el mapa
			int fila_aux,columna_aux;

			for (int i = 0; i < 16; ++i)
			{
				switch (brujula)
				{
				case 0:
					if( i == 0)
					{
						fila_aux = fil;
						columna_aux = col;
					}
					else if( i == 1)
					{
						fila_aux = fil -1;
						columna_aux = col-1;
					}
					else if( i == 2)
					{
						fila_aux = fil-1;
						columna_aux = col;
					}
					else if( i == 3)
					{
						fila_aux = fil-1;
						columna_aux = col+1;
					}
					else if( i == 4)
					{
						fila_aux = fil-2;
						columna_aux = col-2;
					}
					else if( i == 5)
					{
						fila_aux = fil-2;
						columna_aux = col-1;
					}
					else if( i == 6)
					{
						fila_aux = fil-2;
						columna_aux = col;
					}
					else if( i == 7)
					{
						fila_aux = fil-2;
						columna_aux = col+1;
					}
					else if( i == 8)
					{
						fila_aux = fil-2;
						columna_aux = col+2;
					}
					else if( i == 9)
					{
						fila_aux = fil-3;
						columna_aux = col-3;
					}
					else if( i == 10)
					{
						fila_aux = fil-3;
						columna_aux = col-2;
					}
					else if( i == 11)
					{
						fila_aux = fil-3;
						columna_aux = col-1;
					}
					else if( i == 12)
					{
						fila_aux = fil-3;
						columna_aux = col;
					}
					else if( i == 13)
					{
						fila_aux = fil-3;
						columna_aux = col+1;
					}
					else if( i == 14)
					{
						fila_aux = fil-3;
						columna_aux = col+2;
					}
					else if( i == 15)
					{
						fila_aux = fil-3;
						columna_aux = col+3;
					}

					break;

				case 1:
					if( i == 0)
					{
						fila_aux = fil;
						columna_aux = col;
					}
					else if( i == 1)
					{
						fila_aux = fil-1;
						columna_aux = col+1;
					}
					else if( i == 2)
					{
						fila_aux = fil;
						columna_aux = col+1;
					}
					else if( i == 3)
					{
						fila_aux = fil+1;
						columna_aux = col+1;
					}
					else if( i == 4)
					{
						fila_aux = fil-2;
						columna_aux = col+2;
					}
					else if( i == 5)
					{
						fila_aux = fil-1;
						columna_aux = col+2;
					}
					else if( i == 6)
					{
						fila_aux = fil;
						columna_aux = col+2;
					}
					else if( i == 7)
					{
						fila_aux = fil+1;
						columna_aux = col+2;
					}
					else if( i == 8)
					{
						fila_aux = fil+2;
						columna_aux = col+2;
					}
					else if( i == 9)
					{
						fila_aux = fil-3;
						columna_aux = col+3;
					}
					else if( i == 10)
					{
						fila_aux = fil-2;
						columna_aux = col+3;
					}
					else if( i == 11)
					{
						fila_aux = fil-1;
						columna_aux = col+3;
					}
					else if( i == 12)
					{
						fila_aux = fil;
						columna_aux = col+3;
					}
					else if( i == 13)
					{
						fila_aux = fil+1;
						columna_aux = col+3;
					}
					else if( i == 14)
					{
						fila_aux = fil+2;
						columna_aux = col+3;
					}
					else if( i == 15)
					{
						fila_aux = fil+3;
						columna_aux = col+3;
					}
					break;

				case 2:
					if( i == 0)
					{
						fila_aux = fil;
						columna_aux = col;
					}
					else if( i == 1)
					{
						fila_aux = fil+1;
						columna_aux = col+1;
					}
					else if( i == 2)
					{
						fila_aux = fil+1;
						columna_aux = col;
					}
					else if( i == 3)
					{
						fila_aux = fil+1;
						columna_aux = col-1;
					}
					else if( i == 4)
					{
						fila_aux = fil+2;
						columna_aux = col+2;
					}
					else if( i == 5)
					{
						fila_aux = fil+2;
						columna_aux = col+1;
					}
					else if( i == 6)
					{
						fila_aux = fil+2;
						columna_aux = col;
					}
					else if( i == 7)
					{
						fila_aux = fil+2;
						columna_aux = col-1;
					}
					else if( i == 8)
					{
						fila_aux = fil+2;
						columna_aux = col-2;
					}
					else if( i == 9)
					{
						fila_aux = fil+3;
						columna_aux = col+3;
					}
					else if( i == 10)
					{
						fila_aux = fil+3;
						columna_aux = col+2;
					}
					else if( i == 11)
					{
						fila_aux = fil+3;
						columna_aux = col+1;
					}
					else if( i == 12)
					{
						fila_aux = fil+3;
						columna_aux = col;
					}
					else if( i == 13)
					{
						fila_aux = fil+3;
						columna_aux = col-1;
					}
					else if( i == 14)
					{
						fila_aux = fil+3;
						columna_aux = col-2;
					}
					else if( i == 15)
					{
						fila_aux = fil+3;
						columna_aux = col-3;
					}
					break;
				case 3:
					if( i == 0)
					{
						fila_aux = fil;
						columna_aux = col;
					}
					else if( i == 1)
					{
						fila_aux = fil+1;
						columna_aux = col-1;
					}
					else if( i == 2)
					{
						fila_aux = fil;
						columna_aux = col-1;
					}
					else if( i == 3)
					{
						fila_aux = fil-1;
						columna_aux = col-1;
					}
					else if( i == 4)
					{
						fila_aux = fil+2;
						columna_aux = col-2;
					}
					else if( i == 5)
					{
						fila_aux = fil+1;
						columna_aux = col-2;
					}
					else if( i == 6)
					{
						fila_aux = fil;
						columna_aux = col-2;
					}
					else if( i == 7)
					{
						fila_aux = fil-1;
						columna_aux = col-2;
					}
					else if( i == 8)
					{
						fila_aux = fil-2;
						columna_aux = col-2;
					}
					else if( i == 9)
					{
						fila_aux = fil+3;
						columna_aux = col-3;
					}
					else if( i == 10)
					{
						fila_aux = fil+2;
						columna_aux = col-3;
					}
					else if( i == 11)
					{
						fila_aux = fil+1;
						columna_aux = col-3;
					}
					else if( i == 12)
					{
						fila_aux = fil;
						columna_aux = col-3;
					}
					else if( i == 13)
					{
						fila_aux = fil-1;
						columna_aux = col-3;
					}
					else if( i == 14)
					{
						fila_aux = fil-2;
						columna_aux = col-3;
					}
					else if( i == 15)
					{
						fila_aux = fil-3;
						columna_aux = col-3;
					}
					break;
				}

				if (sensores.terreno[i] == 'G' && !bien_situados && !g_visto)
				{
					//cout<<"      .............           "<<i<<" "<<fila_aux<<" "<<columna_aux<<endl;
					irHasta(fil,col,fila_aux,columna_aux);
					irHasta(fila_aux,columna_aux,fil,col);
					g_visto = true;
				}
				else if (sensores.terreno[i] == 'K' && !bikini && !b_visto)
				{
					irHasta(fil,col,fila_aux,columna_aux);
					irHasta(fila_aux,columna_aux,fil,col);
					b_visto = true;
				}
				else if (sensores.terreno[i] == 'D' && !zapatillas && !z_visto)
				{
					//cout<<"EOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"<<endl;
					irHasta(fil,col,fila_aux,columna_aux);
					irHasta(fila_aux,columna_aux,fil,col);
					z_visto = true;
				}
			}
		}







	// si esta en bucle y no esta en frente de una pared que avance para salir del bucle
	if(estaEnBucle() && puedoPisar(2,sensores))
		paredEncontrad = false;


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
		else if (puedoPisar(2,sensores) && !ya_visitada_enfrente) // Comprobamos si podriamos avanzar hacia delante
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
						// Si esta rodeando por dentro (mirar que no gire a la derecha si esta rodeando por fuera)
						if(ya_visitada)
							girar_der = true;
						else
							girar_izq = true;
						
						
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
				if (puedoPisar(1,sensores))
				{
					// Hay que avanzar y luego girar izq
					accion = actFORWARD;
					cout << "Avanzo" << endl;

					// Almacenamos la posicion
					esta_pintada[fil_aux][col_aux] = true;

					if (!ya_visitada) //|| !final_ciclo)
						girar_izq = true;
					//else if (!ya_visitada && //estyo rodeando por fuera)	// intentamos rodear por fuera cuando rodeamos por fuera
						//girar_der = true; // pfff esto lo quitas luego. NO OLVIDAR!
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

			// si ha chocado y esta dando vueltas por una pared o algo que gire izq en vez de der
			//if(ha_chocado && !puedoPisar(2,sensores))
			//{
			//	accion = actTURN_L;
			//	ha_chocado = false;
			//}
				
		}
	}
	else
	{
		// Vamos accediendo en orden a las acciones pendientes y vamos eliminandolas;
		accion = cadenaAcciones[0];
		cadenaAcciones.erase(cadenaAcciones.begin());

		cout<<"La proxima accion del vector es: "<<accion<<endl;

		if(accion == actFORWARD && !puedoPisar(2,sensores))
		{
			accion = actIDLE;
			cadenaAcciones.clear();
		}

		// Si hemos vuelto a donde estamos buscamos una pared y volvemos a poder ir a or u bikini o zapatillas o lo que sea si no hemos pasado
		if(cadenaAcciones.empty())
		{
			paredEncontrad = false;
			g_visto = false;
			z_visto = false;
			b_visto = false;
		}
			
		
	}

	// si la ultima accion es avanzar almacenamos la posicion desde donde nos movemos en el vectopr de ultimasCuatro posiciones
	if(ultimaAccion == actFORWARD)
	{
		ultimasCuatro[posicion_vector].first = fil_aux;
		ultimasCuatro[posicion_vector].second = col_aux;

		cout<<"Las posiciones almacenadas en el vec pos "<<posicion_vector<<" son : "<<fil_aux<<" "<<col_aux<<endl;
	}
	


	ultimaAccion = accion;

	// Determinar el efecto de la ultima accion enviada
	return accion;
}

int ComportamientoJugador::interact(Action accion,int valor){
  return false;
}
