#include "funciones_matriz.hpp"
#include "funciones_vector.hpp"
#include "funciones_strassen.hpp"
#include "clase_tiempo.hpp"
#include "strassen.hpp"
#include <math.h>

void opcionStrassen()
{
	vector < vector < double > > matriz_1;
	vector < vector < double > > matriz_2;
	vector < vector < double > > matriz_resultado;

	vector <double> tiempos;
	vector <double> n;
	vector <double> a;

	// Porque es un polinomio cubico
	a.resize(4);

	int valor_minimo;
	int valor_maximo;

	double n_usuario = 1;

	Clock reloj;

	cout << endl;
	cout << "Introduzca el orden minimo de la matriz: ";
	cin >> valor_minimo;
	cout << endl;

	cout << "Introduzca el orden maximo de la matriz: ";
	cin >> valor_maximo;
	cout << endl;

	matriz_1.resize(valor_minimo, vector<double>(valor_minimo));
	matriz_2.resize(valor_minimo, vector<double>(valor_minimo));
	matriz_resultado.resize(valor_minimo, vector<double>(valor_minimo));


	while (matriz_1.size() <= valor_maximo)
	{
		unsigned int tamano = matriz_1.size();
		double media = 0.0;

		cout << "n = " << tamano << endl;

		n.push_back(matriz_1.size());
		
		rellenarMatriz(matriz_1);
		rellenarMatriz(matriz_2);
		rellenarMatriz(matriz_resultado);

		reloj.start();
		
		strassen(matriz_1, matriz_2, matriz_resultado, tamano);

		if (reloj.isStarted())
		{
			reloj.stop();
			media = media + reloj.elapsed();
		}

		tiempos.push_back(media);

		tamano = tamano * 2;
		matriz_1.clear();
		matriz_2.clear();
		matriz_resultado.clear();

		matriz_1.resize(tamano, vector<double>(tamano));
		matriz_2.resize(tamano, vector<double>(tamano));
		matriz_resultado.resize(tamano, vector<double>(tamano));

	}

	// Almaceno en un fichero los valores de (n) empleados y los tiempos correspondientes
	rellenaFichero(n, tiempos);

	// Ahora hago el ajuste polinomico
	ajusteStrassen(n, tiempos, a);

	while(n_usuario != 0){
		cout << "Introduzca el ejemplar para el cual le gustaria calcularlo: ";
		cin >> n_usuario;

		if (n_usuario > 0)
		{
			cout << "El algoritmo tardaria " << calcularTiempoEstimadoStrassen(n_usuario, a) << " dias" << endl;
		}	
	}

}

void ajusteStrassen(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a)
{
	vector < vector < double > > A (4, vector< double >(4));
	vector < vector < double > > B (4, vector< double >(1));
	vector < vector < double > > X (4, vector< double >(1));

	// Tiempos estimados
	vector <double> tiemposEstimados;

	// TODO FUNCIONA EXATAMENTE IGUAL QUE EN EL PRODUCTO NORMAL DE MATRICES, LO UNICO QUE CAMBIAN SON LOS EXPONENTES DE LOS SUMATORIOS
	// REVISARLO LOS EXPONENTES MUY BIEN
	A[0][0] = n.size();
	A[0][1] = sumatorio_Strassen(n,1,n,0);
	A[0][2] = sumatorio_Strassen(n,2,n,0);
	A[0][3] = sumatorio_Strassen(n,2.81,n,0);
	A[1][0] = sumatorio_Strassen(n,1,n,0);
	A[1][1] = sumatorio_Strassen(n,2,n,0);
	A[1][2] = sumatorio_Strassen(n,2.81,n,0);
	A[1][3] = sumatorio_Strassen(n,2.81,n,1);
	A[2][0] = sumatorio_Strassen(n,2,n,0);
	A[2][1] = sumatorio_Strassen(n,2.81,n,0);
	A[2][2] = sumatorio_Strassen(n,2.81,n,1);
	A[2][3] = sumatorio_Strassen(n,2.81,n,2);
	A[3][0] = sumatorio_Strassen(n,2.81,n,0);
	A[3][1] = sumatorio_Strassen(n,2.81,n,1);
	A[3][2] = sumatorio_Strassen(n,2.81,n,2);
	A[3][3] = sumatorio_Strassen(n,2.81,n,2.81);

	B[0][0] = sumatorio_Strassen(n,0,tiemposReales,1);
	B[1][0] = sumatorio_Strassen(n,1,tiemposReales,1);
	B[2][0] = sumatorio_Strassen(n,2,tiemposReales,1);
	B[3][0] = sumatorio_Strassen(n,2.81,tiemposReales,1);

	// Obtener la matriz A y B
	resolverSistemaEcuaciones(A, B, 4, X);

	a[0] = X[0][0];
	a[1] = X[1][0];
	a[2] = X[2][0];
	a[3] = X[3][0];

	cout << "a0 = " << a[0] << endl;
	cout << "a1 = " << a[1] << endl;
	cout << "a2 = " << a[2] << endl;
	cout << "a3 = " << a[3] << endl;
	cout << endl;

	// Calculamos los tiempos estimados
	calcularTiemposEstimadosStrassen(n, tiemposReales, a, tiemposEstimados);

	// Rellenamos el fichero
	rellenaFichero(n, tiemposReales, tiemposEstimados);
}

double sumatorio_Strassen(const vector <double> &n, double grado_n, const vector <double> &tiemposReales, double grado_t)
{
	double suma = 0;

	for (int i = 0; i < n.size(); i++)
	{
		suma = suma + (pow(n[i], grado_n) * pow(tiemposReales[i], grado_t));
	}

	return suma;
}