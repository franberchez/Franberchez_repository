/*!
   \file operadoresExternosPolinomios.cpp
   \brief Fichero que contiene el código de las funciones de la clase Polinomio
*/


// Ficheros de cabecera
#include <iostream>
#include <cstdlib>

#include "operadoresExternosPolinomios.hpp"

#include "operadoresExternosMonomios.hpp"

// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed
{

bool operator==(ed::Polinomio const & p1, ed::Polinomio const & p2)
{
	bool valor_devuelto = true;

	if ( p1.getNumeroMonomios() != p2.getNumeroMonomios() )
	{
		valor_devuelto = false;
	}

	else
	{
		for(int i = 0; i<p1.getNumeroMonomios(); i++)
		{
			if(p1.getVector() != p2.getVector())
			{
				valor_devuelto = false;
			}
		}
	}

	return valor_devuelto;
}

bool operator==(ed::Polinomio const & p, ed::Monomio const & m)
{
	bool valor_devuelto = true;

	if(p.getNumeroMonomios() > 1)
	{
		valor_devuelto = false;
	}

	else
	{
		if( (p.getVector())[0] != m) // No puedo utilizar variables privadas de la clase por eso necesito el getVector
		{
			valor_devuelto = false;
		}
	}

	return valor_devuelto;
}

bool operator==(ed::Monomio const & m, ed::Polinomio const & p)
{
	bool valor_devuelto = true;

	if(p.getNumeroMonomios() > 1)
	{
		valor_devuelto = false;
	}

	else
	{
		if((p.getVector())[0] != m) // No puedo utilizar variables privadas de la clase por eso necesito el getVector
		{
			valor_devuelto = false;
		}
	}

	return valor_devuelto;
}

bool operator==(ed::Polinomio const & p, double const & x)
{
	ed::Monomio m;
	bool valor_devuelto = true;
	m = x;

	if(p.getNumeroMonomios() > 1)
	{
		valor_devuelto = false;
	}

	else
	{
		if((p.getVector())[0] != m) // No puedo utilizar variables privadas de la clase por eso necesito el getVector
		{
			valor_devuelto = false;
		}
	}

	return valor_devuelto;
}


bool operator==(double const & x, ed::Polinomio const & p)
{
	ed::Monomio m;
	bool valor_devuelto = true;
	m = x;

	if(p.getNumeroMonomios() > 1)
	{
		valor_devuelto = false;
	}

	else
	{
		if((p.getVector())[0] != m) // No puedo utilizar variables privadas de la clase por eso necesito el getVector
		{
			valor_devuelto = false;
		}
	}

	return valor_devuelto;	
}

////////////////////////////////////////////////////////////////////////////////////
// Operadores de desigualdad
bool operator!=(ed::Polinomio const & p1, ed::Polinomio const & p2)
{
	bool valor_devuelto = true;

	if( p1.getNumeroMonomios() != p2.getNumeroMonomios() ) // En caso de que tengan distinto numero de monomios quiere decir que son iguales
	{
		valor_devuelto = true;
	}

	else
	{
		for (int i = 0; i<p1.getNumeroMonomios(); i++)
		{
	   		if((p1.getVector()[i])==(p2.getVector()[i])){
	   			valor_devuelto=false;
	   		}
		}
	}

	return valor_devuelto;
}


bool operator!=(ed::Polinomio const & p, ed::Monomio const & m)
{
	bool valor_devuelto = true;

	if( p.getNumeroMonomios() > 1)
	{
		valor_devuelto = true;
	}

	else
	{
		if( (p.getVector())[0] == m )
		{
			valor_devuelto = false;
		}
	}

	return valor_devuelto;
}

bool operator!=(ed::Monomio const & m, ed::Polinomio const & p)
{
	bool valor_devuelto = true;

	if( p.getNumeroMonomios() > 1)
	{
		valor_devuelto = true;
	}

	else
	{
		if( (p.getVector())[0] == m )
		{
			valor_devuelto = false;
		}
	}

	return valor_devuelto;
}

bool operator!=(ed::Polinomio const & p, double const & x)
{
	bool valor_devuelto = true;
	ed::Monomio m;
	m = x;

	if( p.getNumeroMonomios() > 1)
	{
		valor_devuelto = true;
	}

	else
	{
		if( (p.getVector())[0] == m )
		{
			valor_devuelto = false;
		}
	}

	return valor_devuelto;
}

bool operator!=(double const & x, ed::Polinomio const & p)
{
	bool valor_devuelto = true;
	ed::Monomio m;
	m = x;

	if( p.getNumeroMonomios() > 1)
	{
		valor_devuelto = true;
	}

	else
	{
		if( (p.getVector())[0] == m )
		{
			valor_devuelto = false;
		}
	}

	return valor_devuelto;
}


//////////////////////////////////////////////////////////////////////////////////////

// Operadores unarios

// COMPLETAR
ed::Polinomio & operator+(ed::Polinomio const & p)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(p);
	ed::Monomio aux;

	for(int i = 0; i<p.getNumeroMonomios(); i++)
	{
		aux.setCoeficiente(aux.getCoeficiente()+(p.getVector())[i].getCoeficiente());
		aux.setGrado((p.getVector())[i].getGrado());
		nuevo->getVector().push_back(aux);		
	}

	// Se devuelve el resultado
	nuevo->ordenaPolinomio();
	return *nuevo;
}

ed::Polinomio & operator-(ed::Polinomio const & p)
{
	ed::Polinomio *nuevo = new ed::Polinomio(p);
	std::vector<ed::Monomio> v_aux;
	ed::Monomio aux;

	for(int i = 0; i<p.getNumeroMonomios(); i++)
	{
		aux.setCoeficiente((-1)*(p.getVector())[i].getCoeficiente());
		aux.setGrado((p.getVector())[i].getGrado());
		v_aux.push_back(aux);
	}	

	nuevo->asignaPolinomio(v_aux);
	nuevo->ordenaPolinomio();
	return *nuevo;
}


//////////////////////////////////////////////////////////////////////////////////////

// Operadores binarios de la suma
ed::Polinomio & operator+(ed::Polinomio const &p1, ed::Polinomio const &p2)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p1;
	*nuevo += p2;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator+(ed::Polinomio const &p, ed::Monomio const &m)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p;
	*nuevo += m;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator+(ed::Monomio const &m, ed::Polinomio const &p)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = m;
	*nuevo += p;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator+(ed::Polinomio const &p, double const &x)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p;
	*nuevo += x;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator+(double const &x, ed::Polinomio const &p)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = x;
	*nuevo += p;

	// Se devuelve el resultado
	return *nuevo;
}


////////////////////////////////////////////////////////////////////////////////////////////
	// Resta

ed::Polinomio & operator-(ed::Polinomio const &p1, ed::Polinomio const &p2)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p1;
	*nuevo -= p2;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator-(ed::Polinomio const &p, ed::Monomio const &m)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p;
	*nuevo -= m;	

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator-(ed::Monomio const &m, ed::Polinomio const &p)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = m;
	*nuevo -= p;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator-(ed::Polinomio const &p, double const &x)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p;
	*nuevo -= x;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator-(double const &x, ed::Polinomio const &p)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = x;
	*nuevo -= p;

	// Se devuelve el resultado
	return *nuevo;
}


////////////////////////////////////////////////////////////////////////////////////////////
	// Multiplicación

ed::Polinomio & operator*(ed::Polinomio const &p1, ed::Polinomio const &p2)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p1;
	*nuevo *= p2;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator*(ed::Polinomio const &p, ed::Monomio const &m)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p;
	*nuevo *= m;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator*(ed::Monomio const &m, ed::Polinomio const &p)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = m;
	*nuevo *= p;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator*(ed::Polinomio const &p, double const &x)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p;
	*nuevo *= x;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator*(double const &x, ed::Polinomio const &p)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = x;
	*nuevo *= p;

	// Se devuelve el resultado
	return *nuevo;
}

////////////////////////////////////////////////////////////////////////////////////////////
	// División

ed::Polinomio & operator/(ed::Polinomio const &p1, ed::Polinomio const &p2)
{
	#ifndef NDEBUG
		assert(p2.getGrado()<=p1.getGrado());
	#endif	

	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p1;
	*nuevo /= p2;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator/(ed::Polinomio const &p, ed::Monomio const &m)
{
	#ifndef NDEBUG
		assert(m.getGrado()<=p.getGrado());
	#endif

	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p;
	*nuevo /= m;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator/(ed::Monomio const &m, ed::Polinomio const &p)
{
	#ifndef NDEBUG
		assert(m.getGrado()<=p.getGrado());
	#endif

	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = m;
	*nuevo /= p;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator/(ed::Polinomio const &p, double const &x)
{
	#ifndef NDEBUG
		assert(std::abs(x)>COTA_ERROR);
	#endif

	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = p;
	*nuevo /= x;

	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator/(double const &x, ed::Polinomio const &p)
{
	#ifndef NDEBUG
		assert(p.getGrado()==0 and (std::abs((p.getVector())[0].getCoeficiente())>COTA_ERROR));
	#endif

	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	*nuevo = x;
	*nuevo /= p;

	// Se devuelve el resultado
	return *nuevo;
}


////////////////////////////////////////////////////////////////////////////

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, Polinomio &p)
{
	ed::Monomio m;
	double coeficiente;
	int grado;
	int n;

	std::cout<<"Cuantos monomios desea crear: ";
	std::cin>>n;
	std::cout<<""<<std::endl;
	std::cout<<"Introduzca su monomio separando el coeficiente del grado con un espacio"<<std::endl;

	for (int i = 0; i<n; i++)
	{	
		std::cout<<"Introduzca el monomio: ";
		stream>>coeficiente;
		stream>>grado;

		if(grado<0)
		{
			std::cout<<"ERROR EL GRADO ES NEGATIVO"<<std::endl;
			exit(-1);
		}

		m.setCoeficiente(coeficiente);
		m.setGrado(grado);

		p.insertaMonomio(m);
	}

	std::cout<<""<<std::endl;

	// Se devuelve el flujo de entrada
  return stream;
}



// Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, Polinomio const &p)
{
	for(int i = 0; i<p.getNumeroMonomios(); i++)
	{
		stream<<( (p.getVector())[i].getCoeficiente() );
		stream<<" ";
		stream<<( (p.getVector())[i].getGrado() );
		stream<<"  ";
	}

	// Se devuelve el flujo de salida
  return stream;
}


} // Fin del espacio de nombres ed
