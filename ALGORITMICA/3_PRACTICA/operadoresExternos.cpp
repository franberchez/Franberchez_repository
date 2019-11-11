#include "funciones.hpp"

Entero & operator+(Entero &e1, Entero &e2)
{
	Entero *nuevo = new Entero();
	bool acarreo = false;
	int aux, x, y;
	string suma;

	e1.quitarCerosNoSignificativos();
	e2.quitarCerosNoSignificativos();

	if (e1.getNumero().size() > e2.getNumero().size())
	{
		e2.agregarCerosDelante(e1.getNumero().size() - e2.getNumero().size());
	}

	else
	{
		if(e2.getNumero().size() > e1.getNumero().size())
		{
			e1.agregarCerosDelante(e2.getNumero().size() - e1.getNumero().size());
		}
	}

	(*nuevo).agregarCerosDelante(e1.getNumero().size()-1);
	suma = suma + (*nuevo).getNumero();

	for (int i = e1.getNumero().size()-1; i >= 0; i--)
	{
		x = e1.getNumero()[i] - '0';
		y = e2.getNumero()[i] - '0';
		
		aux = x + y;

		if(acarreo == true)
		{
			aux++;
			acarreo = false;
		}

		if(aux < 10)
		{
			suma[i] = '0' + aux;
		}

		else
		{
			suma[i] = '0' + aux % 10;
			acarreo = true;
		}
	}

	if(acarreo == true) suma = "1" + suma;

	(*nuevo).setNumero(suma);

	return *nuevo;
}


Entero & operator*(Entero &e1, Entero &e2)
{
	Entero *nuevo = new Entero();
	int n, s;
	string aux;

	Entero w, y, x, z, wy, wz, xy, xz;

	e1.quitarCerosNoSignificativos();
	e2.quitarCerosNoSignificativos();

	if (e1.getNumero().size() > e2.getNumero().size())
	{
		n = e1.getNumero().size();
		e2.agregarCerosDelante(e1.getNumero().size() - e2.getNumero().size());
	}

	else
	{
		if(e2.getNumero().size() > e1.getNumero().size())
		{
			n = e2.getNumero().size();
			e1.agregarCerosDelante(e2.getNumero().size() - e1.getNumero().size());
		}

		if (e1.getNumero().size() == e2.getNumero().size())
		{
			n = e1.getNumero().size();
		}
	}

	if (n%2!=0)
	{
		e1.agregarCerosDelante(1);
		e2.agregarCerosDelante(1);
		n++;
	}

	if (n <= 4)
	{
		if(e1.getNumero().empty())
		{
			e1.setNumero("0");
		}

		if(e2.getNumero().empty())
		{
			e2.setNumero("0");
		}

		int a = stoi(e1.getNumero());
		int b = stoi(e2.getNumero());
		a = a * b;

		aux = to_string(a);
		(*nuevo).setNumero(aux);

		return *nuevo;
	}

	else
	{
		s = n / 2;

		e1.partircadenas(w, x, n);
		e2.partircadenas(y, z, n);

		wy = w * y;
		wz = w * z;
		xy = x * y;
		xz = x * z;

		wy.multiplicarPotencia10(2*s);
		wz.multiplicarPotencia10(s);
		xy.multiplicarPotencia10(s);

		wz = wz + xy;
		wy = wy + wz;
		wy = wy + xz;

		(*nuevo).setNumero(wy.getNumero());

		return (*nuevo);
	}
}


istream &operator>>(istream &stream, Entero &e)
{
	string numero;

	stream >> numero;
	e.setNumero(numero);

	return stream;
}


ostream &operator<<(ostream &stream, Entero &e) 
{
	string numero = e.getNumero();
	stream << numero;

	return stream;
}