#include <math.h>
#include "funciones_vector.hpp"

void calcularTiemposEstimadosNlogN(const vector <double> &n, const vector <double> &tiemposReales, const double &a0, const double a1, vector <double> &tiemposEstimados)
{
	// t = a0 + a1*n*log(n)
	double t;

	for (int i = 0; i < n.size(); i++)
	{
		t = a0 + ( a1 * n[i]*log(n[i]) );
		tiemposEstimados.push_back(t);
	}

	calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);
}

// Vi como se calculaba en internet

double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados)
{
	double media_real = 0.0;
	double media_estimada = 0.0;

	double varianza_real = 0.0;
	double varianza_estimada = 0.0;

	double coeficiente;

	// Varianza de los tiempos reales
	for (int i = 0; i<tiemposReales.size(); i++)
	{
		media_real = media_real + tiemposReales[i]; // Aqui lo que hago es el sumatorio
	}

	media_real = media_real / tiemposReales.size(); // Aqui ya calculo la media propiamente dicha

	for (int i = 0; i<tiemposReales.size(); i++)
	{
		int suma = tiemposReales[i] + media_real;
		varianza_real = varianza_real + pow(suma, 2);
	}

	varianza_real = varianza_real / (tiemposReales.size() - 1);

	// Varianza de los tiempos estimados
	for (int i = 0; i<tiemposEstimados.size(); i++)
	{
		media_estimada = media_estimada + tiemposEstimados[i];
	}

	media_estimada = media_estimada / tiemposEstimados.size();

	for (int i = 0; i<tiemposEstimados.size(); i++)
	{
		int suma = tiemposEstimados[i] + media_estimada;
		varianza_estimada = varianza_estimada + pow(suma, 2);
	}

	varianza_estimada = varianza_estimada / (tiemposEstimados.size() - 1);

	// Calculamos el coeficiente de determinacion
	coeficiente = varianza_estimada / varianza_real;

	cout << "Coeficiente de determinacion = " << coeficiente << endl;
}


double calcularTiempoEstimadoNlogN(const double &n, const double &a0, const double &a1)
{
	// Si 1 microsegundo son 1.1574074074074074×10-11 dias

	double dias;

	// Es basicamente multiplicar la ecuacion de antes por cuanto equivale un microsegundo en dias
	dias = (a0 +a1*n*log(n)) * (1.1574074074074074 * pow(10, -11));

	return dias;
}