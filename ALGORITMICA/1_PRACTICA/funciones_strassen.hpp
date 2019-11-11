#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#ifndef FUNCIONES_STRASSEN_
#define FUNCIONES_STRASSEN_

void opcionStrassen();

void ajusteStrassen(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a);

void calcularTiemposEstimadosStrassen(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &a, vector <double> &tiemposEstimados);

double sumatorio_Strassen(const vector <double> &n, double grado_n, const vector <double> &tiemposReales, double grado_t);

double calcularTiempoEstimadoStrassen(const double &n, const vector <double> &a);

#endif