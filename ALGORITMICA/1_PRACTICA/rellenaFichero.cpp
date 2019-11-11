#include <fstream> // Libreria que necesitamos para trabajar con ficheros de texto
#include "funciones_vector.hpp"

// Esta funcion simplemente lo que hace es rellenar mi fichero de texto con los n y los tiempos que calculamos en un inicio
void rellenaFichero(const vector <double> &n, const vector <double> &tiemposReales)
{

	// Abrimos el fichero en modo escritura
	ofstream ficheroSalida;
	ficheroSalida.open("Datos.txt");
	
	// Relleno mi fichero de texto con los n, y los tiempos que hemos calculado separados por espacios para poder rellanar el fichero con dos columnas
	for (int i = 0; i<n.size(); i++)
	{
		ficheroSalida << n[i] << " " << tiemposReales[i] << "\n";
	}

	// Cerramos el fichero de texto
	ficheroSalida.close();
}

// Tengo esta funcion sobrecargada, para poder volver a llamarla y añadirle los tiempos estimados
void rellenaFichero(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &tiemposEstimados)
{
	// Abro mi fichero en modo escritura porque lo que realmente voy a hacer es volver a escribir de nuevo todo el fichero
	ofstream ficheroSalida;
	ficheroSalida.open("Datos.txt");
	
	// Relleno de nuevo mi fichero con los n, los tiempo iniciales y ahora los tiempos estamidos, separados por espacios para formar 3 columnas
	for (int i = 0; i<n.size(); i++)
	{
		ficheroSalida << n[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << "\n";
	}

	// Cerramos el fichero de texto
	ficheroSalida.close();
}