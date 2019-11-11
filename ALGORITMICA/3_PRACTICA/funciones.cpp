#include "funciones.hpp"


Entero::Entero()
{
	this->max_ = 4;
	this->setNumero("0");
}


void suma()
{
	Entero e1;
	Entero e2;
	Entero e3;

	cout << endl;
	cout << "Introduzca el primer numero: ";
	cin >> e1;

	cout << "Introduzca el segundo numero: ";
	cin >> e2;

	e3 = e1 + e2;

	cout << endl;
	cout << "El resultado es = " << e3 << endl;
}


void producto()
{
	Entero e1;
	Entero e2;
	Entero e3;

	cout << endl;
	cout << "Introduzca el primer numero: ";
	cin >> e1;

	cout << "Introduzca el segundo numero: ";
	cin >> e2;

	e3 = e1 * e2;

	cout << endl;
	cout << "El resultado es = " << e3 << endl;
}


void factorial()
{
	Entero fact, e;
	fact.setNumero("1");

	cout << endl;
	cout << "Introduzca el numero: ";
	cin >> e;

	int n = stoi(e.getNumero());

	if(n>1)
	{
		for (int i = 2; i<=n; i++)
		{
			e.setNumero(to_string(i));
			fact = fact * e;
		}
	}

	cout << endl;
	cout << "El resultado es = " << fact << endl;
}


void Entero::agregarCerosFinal(int nCeros)
{	
	for(int i = 0; i < nCeros; i++)
	{
		numero_ = numero_ + "0";
	}	
}

void Entero::agregarCerosDelante(int nCeros)
{
	for(int i = 0; i < nCeros; i++)
	{
		numero_ = "0" + numero_;
	}	
}

void Entero::quitarCerosNoSignificativos()
{
	while(numero_[0] == '0')
	{
		numero_.erase(0, 1); // De la posicion 0 va a quitar 1 caracter
	}
}

void Entero::multiplicarPotencia10(int potencia)
{
	agregarCerosFinal(potencia);
}

void Entero::partircadenas(Entero &a, Entero &b, int n)
{
	string aux;
	int s = n / 2;

	aux = this->getNumero().substr(0, s);
	a.setNumero(aux);

	aux = this->getNumero().substr(s, n);
	b.setNumero(aux);
}