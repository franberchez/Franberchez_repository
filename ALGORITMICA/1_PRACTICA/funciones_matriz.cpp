#include "funciones_matriz.hpp"
#include "funciones_vector.hpp"
#include "clase_tiempo.hpp"
#include <math.h>


void opcionMatriz()
{
	// Tengo matriz 1 y 2 porque son las que voy a multiplicar y el resultado de su producto es el que voy a guardar en la matriz resultado
	vector < vector < double > > matriz_1;
	vector < vector < double > > matriz_2;
	vector < vector < double > > matriz_resultado;

	vector <double> tiempos;
	vector <double> n;
	vector <double> a;

	// Porque es un polinomio cubico ---> x³ + x² + x + termino_independiente
	a.resize(4);

	int valor_minimo;
	int valor_maximo;
	int incremento;

	double n_usuario = 1;

	Clock reloj;

	cout << endl;
	cout << "Introduzca el orden minimo de la matriz: ";
	cin >> valor_minimo;
	cout << endl;

	cout << "Introduzca el orden maximo de la matriz: ";
	cin >> valor_maximo;
	cout << endl;

	cout << "Introduzca el incremento del valor del numero de elementos: ";
	cin >> incremento;
	cout << endl;

	matriz_1.resize(valor_minimo, vector<double>(valor_minimo));
	matriz_2.resize(valor_minimo, vector<double>(valor_minimo));
	matriz_resultado.resize(valor_minimo, vector<double>(valor_minimo));
	

	while (matriz_1.size() <= valor_maximo)
	{
		int tamano = matriz_1.size();
		double media = 0.0;

		cout << "n = " << tamano << endl;

		n.push_back(matriz_1.size());
		
		// Relleno cada matriz con valores aleatorios
		rellenarMatriz(matriz_1);
		rellenarMatriz(matriz_2);
		rellenarMatriz(matriz_resultado);

		reloj.start();
		
		productoMatrices(matriz_1, matriz_2, matriz_resultado);

		// Calculo los tiempos y los relleno posteriormente
		if (reloj.isStarted())
		{
			reloj.stop();
			media = media + reloj.elapsed();

		}

		tiempos.push_back(media);

		tamano = tamano + incremento;

		// Limpio las matrices para evitar problemas de memoria
		matriz_1.clear();
		matriz_2.clear();
		matriz_resultado.clear();

		// Reajusto su tamaño
		matriz_1.resize(tamano, vector<double>(tamano));
		matriz_2.resize(tamano, vector<double>(tamano));
		matriz_resultado.resize(tamano, vector<double>(tamano));

	}

	// Almaceno en un fichero los valores de (n) empleados y los tiempos correspondientes
	rellenaFichero(n, tiempos);

	// Ahora hago el ajuste polinomico
	ajustePolinomico(n, tiempos, a);

	while(n_usuario != 0){
		cout << "Introduzca el ejemplar para el cual le gustaria calcularlo: ";
		cin >> n_usuario;

		if (n_usuario > 0)
		{
			cout << "El algoritmo tardaria " << calcularTiempoEstimado(n_usuario, a) << " dias" << endl;
		}	
	}

}

void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a)
{
	// La ecuacion es una ecuacion polinomica de grado 3
	// t = a0*x^3 + a1*x^2 + a2*x + a3

	// Voy a crear tres matrices
	vector < vector < double > > A (4, vector< double >(4));
	vector < vector < double > > B (4, vector< double >(1));
	vector < vector < double > > X (4, vector< double >(1)); // Es resultado de multiplicar una matriz 4x4 por una 4x1 es otra matriz 4x1

	// Tiempos estimados
	vector <double> tiemposEstimados;

	// Relleno los elementos de A
	A[0][0] = n.size();
	A[0][1] = sumatorio(n,1,n,0);
	A[0][2] = sumatorio(n,2,n,0);
	A[0][3] = sumatorio(n,3,n,0);
	A[1][0] = sumatorio(n,1,n,0);
	A[1][1] = sumatorio(n,2,n,0);
	A[1][2] = sumatorio(n,3,n,0);
	A[1][3] = sumatorio(n,4,n,0);
	A[2][0] = sumatorio(n,2,n,0);
	A[2][1] = sumatorio(n,3,n,0);
	A[2][2] = sumatorio(n,4,n,0);
	A[2][3] = sumatorio(n,5,n,0);
	A[3][0] = sumatorio(n,3,n,0);
	A[3][1] = sumatorio(n,4,n,0);
	A[3][2] = sumatorio(n,5,n,0);
	A[3][3] = sumatorio(n,6,n,0);

	// Relleno los elementos de B
	B[0][0] = sumatorio(n,0,tiemposReales,1);
	B[1][0] = sumatorio(n,1,tiemposReales,1);
	B[2][0] = sumatorio(n,2,tiemposReales,1);
	B[3][0] = sumatorio(n,3,tiemposReales,1);

	// Obtener la matriz A y B, con la propia funcion que nos proporciono el profesor
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
	calcularTiemposEstimadosPolinomico(n, tiemposReales, a, tiemposEstimados);

	// Rellenamos el fichero
	rellenaFichero(n, tiemposReales, tiemposEstimados);
}

// Esto es un sumatorio de caracter general para la matriz
double sumatorio(const vector <double> &n, int grado_n, const vector <double> &tiemposReales, int grado_t)
{
	double suma = 0;

	for (int i = 0; i < n.size(); i++) // Tiene sentido porque en caso de que no tengamos timepos su grado va a ser 0 y por lo tanto estaremos multiplicando por 1
	{
		suma = suma + (pow(n[i], grado_n) * pow(tiemposReales[i], grado_t));
	}

	return suma;
}

void productoMatrices(vector < vector < double > > &matriz_1, vector < vector < double > > &matriz_2, vector < vector < double > > &matriz_resultado)
{
	// Siempre vamos a tener que hacer 3 bucles para el producto de matrices
	for (int i = 0; i < matriz_1.size(); i++)
	{
		for (int j = 0; j < matriz_1.size(); j++)
		{
			for (int k = 0; k < matriz_1.size(); k++)
			{
				// Para que resulte facil de recordar es como hacer un sumatorio con suma donde suma es igual a matriz_resultado[i][j] y le sumamos esto matriz_1[i][k] * matriz_2[k][j]
				matriz_resultado[i][j] = matriz_resultado[i][j] + (matriz_1[i][k] * matriz_2[k][j]);
			}
		}
	}
}


// Funcion que sirve para rellanar mi matriz de valores aleatorios
void rellenarMatriz(vector < vector < double > > &v)
{
	float valor;

	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v.size(); j++)
		{
			valor = rand()%11;
			valor = (valor/100)+0.95;
			v[i][j] = valor;
		}
	}

}