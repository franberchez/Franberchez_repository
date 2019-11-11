
#include <stdlib.h>
#include <time.h>
#include "funciones_vector.hpp"
#include "clase_tiempo.hpp"

//void opcionVector()

// ESTA ES LA OPERACION QUE REALZIMOS CON UN VECTOR DE ELEMENTOS QUE ERA LA PARTE OBLIGATORIA

void rellenaVector(vector <int> &v)
{

	int valor_minimo;
	int valor_maximo;
	int incremento;
	int repeticiones;
	int final;

	int n_usuario = 1;

	Clock reloj;
	vector <double> tiempos;
	vector <double> n;
	double a0;
	double a1;

	cout << endl;
	cout << "Introduzca el valor minimo del numero de elementos del vector: ";
	cin >> valor_minimo;
	cout << endl;

	cout << "Introduzca el valor maximo del numero de elementos del vector: ";
	cin >> valor_maximo;
	cout << endl;

	cout << "Introduzca el incremento del valor del numero de elementos: ";
	cin >> incremento;
	cout << endl;

	cout << "Introduzca el numero de repeticiones para cada tamaño del vector: ";
	cin >> repeticiones;
	cout << endl;

	// aqui determino primero el minimo de elementos que tengo en un inicio
	v.resize(valor_minimo);

	// Aqui lo que voy a hacer es repetir este bucle hasta que el tamaño del vector sea igual al valor maximo
	while (v.size() <= valor_maximo)
	{
		int tamano = v.size();
		double media = 0.0;

		// Relle el vector de (n) empleados
		n.push_back(v.size());

		cout << "n = " << tamano << endl;

		// Repito el bucle de llenado y ordenado del vector tantas veces como haya definidas para un determinado tamaño
		for (int j = 0; j < repeticiones; j++)
		{
			// Relleno el vector, deberia de llamar a una funcion que lo hiciera, pero no se porque no me funcionaba asi que lo deje asi
			for(int i = 0; i < v.size(); i++)
			{
				v[i] = rand()%100000;
			}


			reloj.start();
			// Ordeno el vector
			final = v.size() - 1;
			quicksort(v, 0, final);		
			
			// cout << "Peta: " << endl;
			if (reloj.isStarted())
			{
				reloj.stop();
				media = media + reloj.elapsed();
				//reloj.restart(); Si le pongo el restart hace que de fallo
			}

			v.clear(); // Una vez ordeno el vector ya puedo vaciarlo para que no se me sature la memoria
		}

		// Relleno mi vector de tiempos
		media = media/repeticiones;
		tiempos.push_back(media);

		// Actualizo el tamaño del vector con el incremento definido
		tamano = tamano + incremento;
		v.resize(tamano);
	}
	
	// Almaceno en un fichero los valores de (n) empleados y los tiempos correspondientes
	rellenaFichero(n, tiempos);

	// t = a0 +a1*n*log(n)
	ajusteNlogN(n, tiempos, a0, a1);
	
	while(n_usuario != 0){
		cout << "Introduzca el ejemplar para el cual le gustaria calcularlo: ";
		cin >> n_usuario;

		if (n_usuario > 0)
		{
			cout << "El algoritmo tardaria " << calcularTiempoEstimadoNlogN(n_usuario, a0, a1) << " dias" << endl;
		}	
	}	
}

/*void rellenaVector(vector <int> &v)
{
	for(int i = 0; i < v.size(); i++)
	{
		v[i] = rand()%100000;
	}
}*/


// t = a0 + a1*n*log(n)

void ajusteNlogN(const vector <double> &n, const vector <double> &tiemposReales, double &a0, double &a1)
{
	// Reservo memoria para la matriz (como en el final de la practica)
	vector < vector < double > > A (2, vector< double >(2));
	vector < vector < double > > B (2, vector< double >(1));
	vector < vector < double > > X (2, vector< double >(1)); // Es 2x1 porque el resultado de multiplicar una matriz 2x2 por una 2x1 es una 2x1

	vector <double> tiemposEstimados;

	// Es el orden de las matrices
	int tam = 2;

	vector <double> z;

	for (int i = 0; i<n.size(); i++)  // Este ajuste es el que se realizo en la explicacion que proporciono el profesor
	{
		z.push_back( n[i]*log(n[i]) );
	}

	// Calcular los sumatorios correspondientes, rellenado cada elemento de la matriz
	// Estos sumatorios los obtenemos del sistema de ecuaciones que tenemos planteado, repasarlo no vendria mal para entenderlo mejor
	A[0][0] = n.size();
	A[0][1] = sumatorio(z);
	A[1][0] = sumatorio(z);
	A[1][1] = sumatorio_x_cuadrado(z);

	B[0][0] = sumatorio(tiemposReales);
	B[1][0] = sumatorio_x_y(z, tiemposReales);

	// Obtener la matriz A y B, esto se hace con la funcion que nos proporciono el asi que no tenemos porque preocuparnos de su funcionamiento
	resolverSistemaEcuaciones(A, B, tam, X);
	
	a0 = X[0][0];
	a1 = X[1][0];

	cout << "a0 = " << a0 << endl;
	cout << "a1 = " << a1 << endl;
	cout << endl;

	// Calculo los tiempos estimados
	// Es la tercera columna de nuestro fichero.txt que nos servira luego para hacer el grafico que determine como de eficiente ha sido el algoritmo
	calcularTiemposEstimadosNlogN(n, tiemposReales, a0, a1, tiemposEstimados);

	// Relleno el fichero con los tiempos estimados
	rellenaFichero(n, tiemposReales, tiemposEstimados);
}

// Esta funcion comprueba mediante asertos que el vector este ordenado, esta funcion nos la pide el profesor como ejercicio obligatorio
bool estaOrdenado(const vector <int> &v)
{
	for(int i = 1; i < v.size(); i++)
	{
		assert(v[i-1] <= v[i]);
	}

	return true;
}