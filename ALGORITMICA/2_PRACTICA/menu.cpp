#include "funciones.hpp"

int main()
{
	int opcion = 0;

	do
	{
		cout << endl;
		cout << "1. Calculo de los caminos posibles para llegar a una casilla de la fila 8" << endl;
		cout << "2. Calculo de los caminos posibles para llegar a la fila 8 desde la casilla (1,2)" << endl;
		cout << "3. Calculo de los caminos posibles para llegar a la fila 8 desde la casilla (1,7)" << endl;
		cout << "4. Salir" << endl;
		cout << endl;

		cout << "Introduzca la opcion: ";
		cin >> opcion;

		switch(opcion)
		{
			case 1:
				opcion_uno();
			break;

			case 2:
				opcion_dos();
			break;

			case 3:
				opcion_tres();
			break;

			default:
				cout << "Fin del programa" << endl;
		}

	}while(opcion != 4);

	return 0;
}