#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#ifndef FUNCIONES_MATRIZ_
#define FUNCIONES_MATRIZ_


void opcionMatriz();

void rellenarMatriz(vector < vector < double > > &v);

void productoMatrices(vector < vector < double > > &matriz_1, vector < vector < double > > &matriz_2, vector < vector < double > > &matriz_resultado);

void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a);

double sumatorio(const vector <double> &n, int grado_n, const vector <double> &tiemposReales, int grado_t);

void calcularTiemposEstimadosPolinomico(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &a, vector <double> &tiemposEstimados);

double calcularTiempoEstimado(const double &n, const vector <double> &a);

#endif