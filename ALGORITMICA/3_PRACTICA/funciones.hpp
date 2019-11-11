#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

#ifndef FUNCIONES_
#define FUNCIONES_

	class Entero
	{
	private:
		int max_;
		string numero_;

	public:
		Entero();
		// El numero maximo de digitos que pueden tener los enteros en el producto es 4

		inline string getNumero() {return numero_;};
		inline void setNumero(string n) {numero_ = n;};
		inline int getMax() {return max_;};
		inline void setMax(int max) {max_ = max;};

		void agregarCerosFinal(int nCeros);

		void agregarCerosDelante(int nCeros);

		void quitarCerosNoSignificativos();

		void multiplicarPotencia10(int potencia);

		void partircadenas(Entero &a, Entero &b, int n);
		
	};

/* OPERADOR EXTERNO DE LA SUMA */

Entero & operator+(Entero &e1, Entero &e2);

/* OPERADOR EXTERNO DEL PRODUCTO */

Entero & operator*(Entero &e1, Entero &e2);

/* OPERADOR DE ENTRADA O LECTURA */

istream &operator>>(istream &stream, Entero &e);

/* OPERADOR DE SALIDA O ESCRITURA */

ostream &operator<<(ostream &stream, Entero &e);

/* OTRAS FUNCIONES */

void suma();

void producto();

void factorial();

#endif