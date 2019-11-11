#include <math.h>
#include "funciones_matriz.hpp"
#include "funciones_vector.hpp"

void calcularTiemposEstimadosPolinomico(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &a, vector <double> &tiemposEstimados)
{
	double t;

	// t = a3*x^3 + a2*x^2 + a1*x + a0

	// Es simplemente aplicar la ecuacion, pero he de tener claro que el ultimo elemento que relleno de a el [3] es el que se eleva a 3 y de ahi voy reduciendo
	// ESTO ES PARA QUE NO ME EQUIVOQUE COMO LA PRIMERA VEZ
	for (int i = 0; i < n.size(); i++)
	{
		t = (a[3]*pow(n[i], 3)) + (a[2]*pow(n[i], 2)) + (a[1]*n[i]) + a[0];

		tiemposEstimados.push_back(t);
	}

	calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);
}

double calcularTiempoEstimado(const double &n, const vector <double> &a)
{
	// Si 1 microsegundo son 1.1574074074074074×10-11 dias
	// t = a3*x^3 + a2*x^2 + a1*x + a0

	double dias;

	// Es multiplicar la misma equuacion de arriba por el nuemero al que equivale un microsegundo en dias
	dias = ((a[3]*pow(n, 3)) + (a[2]*pow(n, 2)) + (a[1]*n) + a[0]) * (1.1574074074074074 * pow(10, -11));

	return dias;
}