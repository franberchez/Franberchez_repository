#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

#ifndef FUNCIONES_
#define FUNCIONES_

typedef struct{
	int fila;
	int col;
}casilla;


void opcion_uno();

void opcion_dos();

void opcion_tres();

int calcula_camino(int fila, int col, vector <casilla> v, vector < vector < casilla > > &caminos);

int calcula_camino_inverso(int fila, int col, vector <casilla> v, vector < vector < casilla > > &caminos);

void muestra_camino(vector <casilla> v);

void muestra_tablero(vector <casilla> v);

#endif