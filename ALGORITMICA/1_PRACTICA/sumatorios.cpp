#include <math.h>
#include "funciones_vector.hpp"

// Aunque lo que debiria haber hecho es un sumatorio general, aqui lo que tenemos son los tres sumatorios disitintos que tenemos para opcion obligatoria del vector

double sumatorio(vector <double> v)
{
	double suma = 0;

	for (int i = 0; i<v.size(); i++)
	{
		suma = suma + v[i];
	}

	return suma;
}

double sumatorio_x_cuadrado(vector <double> z)
{
	double suma = 0;

	for (int i = 0; i<z.size(); i++)
	{
		suma = suma + pow(z[i], 2);
	}

	return suma;
}

double sumatorio_x_y(vector <double> z, vector <double> tiempos)
{
	double suma = 0;

	for (int i = 0; i<z.size(); i++)
	{
		suma = suma + (z[i] * tiempos[i]);
	}

	return suma;
}

/* La funcion general de sumatorio seria la siguiente */

/*
	double sumatorio(vector <double> n, int grado_n, vector <double> tiempos, int grado_t)
	{
		double suma = 0.0;

		for (int i = 0; i < n.size(); i++)
		{
			suma = suma + (pow(n[i],grado_n)) * (pow(tiempos[i], grado_t));
		}

		return suma;
	}
*/