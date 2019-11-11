#include <vector>
#include <iostream>
#include "sistemaEcuaciones.hpp"

using namespace std;

#ifndef FUNCIONES_VECTOR_
#define FUNCIONES_VECTOR_

void rellenaVector(vector <int> &v);

int divide(vector <int> &array, int start, int end);

void quicksort(vector <int> &array, int start, int end);

bool estaOrdenado(const vector <int> &v);

void rellenaFichero(const vector <double> &n, const vector <double> &tiemposReales);

void rellenaFichero(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &tiemposEstimados);

void ajusteNlogN(const vector <double> &v, const vector <double> &tiemposReales, double &a0, double &a1);

double sumatorio(vector <double> v);

double sumatorio_x_cuadrado(vector <double> z);

double sumatorio_x_y(vector <double> z, vector <double> tiempos);

void calcularTiemposEstimadosNlogN(const vector <double> &n, const vector <double> &tiemposReales, const double &a0, const double a1, vector <double> &tiemposEstimados);

double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados);

double calcularTiempoEstimadoNlogN(const double &n, const double &a0, const double &a1);

#endif