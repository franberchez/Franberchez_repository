#include "funciones.hpp"

int main()
{
	int opcion = 0;

	do
	{
		cout << endl;
		cout << "---------------- OPCIONES DEL MENU ----------------" << endl;
		cout << endl;
		cout << "\t1. Suma" << endl;
		cout << "\t2. Producto" << endl;
		cout << "\t3. Factorial" << endl;
		cout << "\t4. Salir" << endl;
		cout << endl;

		cout << "Introduzca la opcion: ";
		cin >> opcion;

		switch(opcion)
		{
			case 1:
				suma();
			break;

			case 2:
				producto();
			break;

			case 3:
				factorial();
			break;

			default:
				cout << endl;
				cout << "Fin del programa" << endl;
				cout << endl;
		}

	}while(opcion != 4);
}