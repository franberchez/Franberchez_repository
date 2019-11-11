#include "funciones.hpp"

void opcion_uno()
{
	int resultado;
	int col;
	char tecla;

	// Vector de la estructura casilla
	vector <casilla> v;

	// Vector de vectores de tipo casilla
	vector < vector < casilla > > caminos;

	cout << "Introduzca una columna entre 1 y 8: ";
	cin >> col;

	// Llamo a calcula_camino siempre emepezando desde la fila 8
	resultado = calcula_camino(8, col, v, caminos);

	cout << endl;
	cout << "Numero de caminos = " << resultado << endl;
	cout << endl;

	cin.ignore();

	for(int i = 0; i < caminos.size(); i++)
	{
		cout << "Camino " << i+1 << ": ";
		muestra_camino(caminos[i]);
		muestra_tablero(caminos[i]);
		cout << endl;

		do
		{
			cout << "Pulse ENTER para ver el siguiente camino" << endl;
			tecla = getchar();
		}while(tecla!=13 and tecla!=10 and tecla!=141);
	}
}


void opcion_dos()
{
	int resultado;
	int col = 2;
	char tecla;

	// Vector de la estructura casilla
	vector <casilla> v;

	// Vector de vectores de tipo casilla
	vector < vector < casilla > > caminos;

	resultado = calcula_camino_inverso(1, 2, v, caminos);

	cout << endl;
	cout << "Numero de caminos = " << resultado << endl;
	cout << endl;

	cin.ignore();

	for(int i = 0; i < caminos.size(); i++)
	{
		cout << "Camino " << i+1 << ": ";
		muestra_camino(caminos[i]);
		muestra_tablero(caminos[i]);
		cout << endl;

		do
		{
			cout << "Pulse ENTER para ver el siguiente camino" << endl;
			tecla = getchar();
		}while(tecla!=13 and tecla!=10 and tecla!=141);
	}
}


void opcion_tres()
{
	int resultado;
	int col = 2;
	char tecla;

	// Vector de la estructura casilla
	vector <casilla> v;

	// Vector de vectores de tipo casilla
	vector < vector < casilla > > caminos;

	resultado = calcula_camino_inverso(1, 7, v, caminos);

	cout << endl;
	cout << "Numero de caminos = " << resultado << endl;
	cout << endl;

	cin.ignore();

	for(int i = 0; i < caminos.size(); i++)
	{
		cout << "Camino " << i+1 << ": ";
		muestra_camino(caminos[i]);
		muestra_tablero(caminos[i]);
		cout << endl;

		do
		{
			cout << "Pulse ENTER para ver el siguiente camino" << endl;
			tecla = getchar();
		}while(tecla!=13 and tecla!=10 and tecla!=141);
	}
}