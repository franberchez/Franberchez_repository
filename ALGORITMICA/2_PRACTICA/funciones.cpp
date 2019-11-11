#include "funciones.hpp"


/*

	No paso el vector de casillas por referencia para tener multiples copias de el con los distintos caminos
	y despues guardar cada copia como un elemento de la matriz de caminos que lo que contiene son elementos
	vector de tipo casilla

*/

// El camino normal de las llamadas recursivas empieza desde las ultimas hasta la primera por eso aunque aqui vamos de la 1 a la 8
// la ultima que visitamos es la uno porque empezamos las llamadas por la 8
int calcula_camino(int fila, int col, vector <casilla> v, vector < vector < casilla > > &caminos)
{
	// Las llamadas recursivas solo puedes ir hacia atras

	casilla c;
	c.fila = fila;
	c.col = col;

	// Caso base 1 o caso absurdo que es en el caso de que me pueda salir fuera del tablero en el que devuelvo 0 caminos ya que no hay evidentemente
	if (col < 1 or col > 8 or fila < 1 or fila > 8)
	{
		return 0;
	}

	// Caso base 2
	v.push_back(c);

	if (fila == 1)
	{
		caminos.push_back(v);

		return 1;
	}

	// Retorno la suma de los distintos movimientos que puede realizar el caballo
	return calcula_camino(fila-1, col-2, v, caminos) + calcula_camino(fila-2, col-1, v, caminos) + calcula_camino(fila-2, col+1, v, caminos) + calcula_camino(fila-1, col+2, v, caminos);
}


int calcula_camino_inverso(int fila, int col, vector <casilla> v, vector < vector < casilla > > &caminos)
{
	casilla c;
	c.fila = fila;
	c.col = col;

	// Caso base 1 o caso absurdo que es en el caso de que me pueda salir fuera del tablero en el que devuelvo 0 caminos ya que no hay evidentemente
	if (col < 1 or col > 8 or fila < 1 or fila > 8)
	{
		return 0;
	}

	// Caso base 2
	v.push_back(c);

	if (fila == 8)
	{
		caminos.push_back(v);

		return 1;
	}

	return calcula_camino_inverso(fila+1, col-2, v, caminos) + calcula_camino_inverso(fila+2, col-1, v, caminos) + calcula_camino_inverso(fila+2, col+1, v, caminos) + calcula_camino_inverso(fila+1, col+2, v, caminos);
}


void muestra_camino(vector <casilla> v)
{
	for (int i = 0; i<v.size(); i++)
	{
		cout << "(" << v[i].fila << ", " << v[i].col << ")";
	}
}


void muestra_tablero(vector <casilla> v)
{
	string tablero[8][8];

	for (int i = 0; i<8; i++)
	{
		for(int j = 0; j<8; j++)
		{
			tablero[i][j] = " ";
		}
	}

	for(int i = 0; i<v.size(); i++)
	{
		tablero[v[i].fila-1][v[i].col-1]="x";
	}

	cout << endl;
	cout << endl;

	for (int i = 7; i>=0; i--) // Para que el tablero me salga derecho, si no sale al reves
	{
		cout << "      ";

		for (int j = 0; j<=7; j++)
		{
			cout << "[" << tablero[i][j] << "]"; // Para que el tablero me salga derecho, si no sale al reves
		}
		cout << endl;
	}

	cout << endl;
	cout << endl;
}