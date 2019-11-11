#include "funciones_vector.hpp"
#include "funciones_matriz.hpp"
#include "funciones_strassen.hpp"

int main()
{
	srand(time(NULL));
	int opcion;

	do
	{		
		cout << "Elija una opcion:" << endl;
		cout << "\t1. Metodo de ordenacion quicksort" << endl;
		cout << "\t2. Producto de matrices" << endl;
		cout << "\t3. Producto de matrices por Strassen" << endl;
		cout << "\t4. Salir" << endl;
		cout << "Introduzca su opcion: ";
		cin >> opcion;

		vector <int> v;
		switch(opcion)
		{
			case 1:
				rellenaVector(v);
			break;

			case 2:
				opcionMatriz();
			break;

			case 3:
				opcionStrassen();
			break;

			default:
				cout << "Fin del programa" << endl;
		}
	}while(opcion != 4);

	return 0;
}