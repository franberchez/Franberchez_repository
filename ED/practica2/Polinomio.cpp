/*!
   \file Polinomio.cpp
   \brief Fichero que contiene el código de las funciones de la clase Polinomio
*/


// Ficheros de cabecera
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "Polinomio.hpp"


// Operadores de asignación

// COMPLETAR


/////////////////////////////////////////////////////////////

ed::Polinomio & ed::Polinomio::operator=(ed::Polinomio const &p)
{
	#ifndef NDEBUG
		assert( esIgual(p) == false );
	#endif

	this->polinomio_ = p.polinomio_;

	#ifndef NDEBUG
		assert( esIgual(p) == true );
	#endif

	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator=(ed::Monomio const &m)
{
	this->polinomio_.clear();

	this->polinomio_.push_back(m);

	#ifndef NDEBUG
		assert( compruebaMonomio(m) == true );
	#endif

	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator=(double const &x)
{
	this->polinomio_.clear();

	ed::Monomio nuevo;
	nuevo = x;

	this->polinomio_.push_back(nuevo);

	#ifndef NDEBUG
		assert( compruebaMonomio(nuevo) == true );
	#endif

	// Se devuelve el objeto actual
	return *this;
}

//////////////////////////////////////////////////////////////

ed::Polinomio & ed::Polinomio::operator+=(ed::Polinomio const &p)
{

	int encontrado = 0;

	for (int i = 0; i<p.getNumeroMonomios(); i++)
	{
		encontrado = 0;

		for(int j = 0; j<this->getNumeroMonomios(); j++)
		{
			if ( this->polinomio_[j].getGrado() == p.polinomio_[i].getGrado() )
			{
				this->polinomio_[j] += p.polinomio_[i];
				encontrado = 1;
			}
		}

		if(encontrado == 0)
		{
			if( (p.polinomio_[i].getCoeficiente() == 0.0) && (p.polinomio_[i].getGrado() == 0) ) // En caso de que el monomio sea 0 no lo meto
			{
				continue;
			}

			else
			{
				this->polinomio_.push_back(p.polinomio_[i]);
			}
		}
	}

	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator+=(ed::Monomio const &m)
{
	int encontrado = 0;

	for (int i = 0; i<this->getNumeroMonomios(); i++)
	{
		encontrado = 0;

		if(this->polinomio_[i].getGrado() == m.getGrado())
		{
			this->polinomio_[i] += m;
			//this->polinomio_[i].setCoeficiente(suma);
			encontrado = 1;
		}
	}

	if (encontrado == 0)
	{
		if( (m.getCoeficiente() == 0.0) && (m.getGrado() == 0) ) // En caso de que el monomio sea 0 no lo meto
		{
			return *this;
		}

		else
		{
			this->polinomio_.push_back(m);
		}
	}

	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator+=(double const &x)
{
	int encontrado = 0;
	ed::Monomio nuevo;

	nuevo = x;

	for (int i = 0; i<this->getNumeroMonomios(); i++)
	{
		encontrado = 0;

		if(this->polinomio_[i].getGrado() == 0)
		{
			this->polinomio_[i] += nuevo;
			encontrado = 1;
		}
	}

	if (encontrado == 0)
	{
		if( (nuevo.getCoeficiente() == 0.0) && (nuevo.getGrado() == 0) ) // En caso de que el monomio sea 0 no lo meto
		{
			return *this;
		}

		else
		{
			this->polinomio_.push_back(nuevo);
		}
	}

	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator-=(ed::Polinomio const &p)
{

	int encontrado = 0;

	for (int i = 0; i<p.getNumeroMonomios(); i++)
	{	
		encontrado = 0;

		for(int j = 0; j<this->getNumeroMonomios(); j++)
		{
			if ( this->polinomio_[j].getGrado() == p.polinomio_[i].getGrado() )
			{
				this->polinomio_[j] -= p.polinomio_[i];
				encontrado = 1;
			}
		}

		if (encontrado == 0)
		{
			if( (p.polinomio_[i].getCoeficiente() == 0.0) && (p.polinomio_[i].getGrado() == 0) ) // En caso de que el monomio sea 0 no lo meto
			{
				return *this;
			}

			else
			{
				this->polinomio_.push_back(-p.polinomio_[i]);
			}
		}
	}

	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator-=(ed::Monomio const &m)
{
	int encontrado = 0;

	for (int i = 0; i<this->getNumeroMonomios(); i++)
	{
		encontrado = 0;

		if(this->polinomio_[i].getGrado() == m.getGrado())
		{
			this->polinomio_[i] -= m;
			encontrado = 1;
		}
	}

	if (encontrado == 0)
	{
		if( (m.getCoeficiente() == 0.0) && (m.getGrado() == 0) ) // En caso de que el monomio sea 0 no lo meto
		{
			return *this;
		}

		else
		{
			this->polinomio_.push_back(-m);
		}
	}

	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator-=(double const &x)
{

	int encontrado = 0;
	ed::Monomio nuevo;
	nuevo = x;

	for (int i = 0; i<this->getNumeroMonomios(); i++)
	{
		encontrado = 0;

		if(this->polinomio_[i].getGrado() == 0)
		{
			this->polinomio_[i] -= nuevo;
			encontrado = 1;
		}
	}

	if(encontrado == 0)
	{
		if( (nuevo.getCoeficiente() == 0.0) && (nuevo.getGrado() == 0) ) // En caso de que el monomio sea 0 no lo meto
		{
			return *this;
		}

		else
		{
			this->polinomio_.push_back(-nuevo);
		}
	}

	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator*=(ed::Polinomio const &p)
{

	std::vector<ed::Monomio> aux;
	ed::Monomio nuevo;
	int actualizado = 0;

	for (int i = 0; i<p.getNumeroMonomios(); i++)
	{
		for (int j = 0; j<this->getNumeroMonomios(); j++)
		{
			actualizado = 0;
			nuevo = p.getVector()[i] * this->polinomio_[j];

			for (unsigned int k = 0; k<aux.size(); k++)
			{
				if(aux[k].getGrado() == nuevo.getGrado())
				{
					aux[k] += nuevo;
					actualizado = 1;
				}
			}

			if(actualizado == 0)
			{
				aux.push_back(nuevo);
			}
		}

	}

	this->polinomio_ = aux;

	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator*=(ed::Monomio const &m)
{

	std::vector<ed::Monomio> aux;
	ed::Monomio nuevo;
	int actualizado = 0;

	for(int i = 0; i<this->getNumeroMonomios(); i++)
	{
		nuevo = m * this->polinomio_[i];
		actualizado = 0;

		for (unsigned int j = 0; j<aux.size(); j++)
		{
			if(aux[j].getGrado() == nuevo.getGrado())
			{
				aux[j] += nuevo;
				actualizado = 1;
			}
		}
		
		if(actualizado == 0)
		{
			aux.push_back(nuevo);
		}
	}

	this->polinomio_ = aux;

	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator*=(double const &x)
{

	std::vector<ed::Monomio> aux;
	ed::Monomio m;
	ed::Monomio nuevo;
	int actualizado = 0;
	m = x;

	for(int i = 0; i<this->getNumeroMonomios(); i++)
	{
		nuevo = m * this->polinomio_[i];
		actualizado = 0;

		for (unsigned int j = 0; j<aux.size(); j++)
		{
			if(aux[j].getGrado() == nuevo.getGrado())
			{
				aux[j] += nuevo;
				actualizado = 1;
			}
		}
		
		if (actualizado == 0)
		{
			aux.push_back(nuevo);
		}
	}

	this->polinomio_ = aux;

	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator/=(ed::Polinomio const &p) // REVISAR LOS DEL FOR DEL <= DE TOMAS PROBARLO SIN ESO
{

	#ifndef NDEBUG
		assert(this->getGrado() >= p.getGrado());
		assert(this->esNulo() == false);
	#endif

	//this->ordenaPolinomio();
	ed::Polinomio dividendo = *this;
	ed::Polinomio divisor;
	ed::Polinomio cociente;
	ed::Monomio m;
	bool divide = 0;

	cociente.polinomio_.clear();

	for (int i = 0; i<=dividendo.getNumeroMonomios(); i++)
	{
		if ( dividendo.getGrado() >= p.getGrado() )
		{
			m = p.polinomio_[0];

			// Aqui puedo ir restando siempre por la posicion 0 del dividendo porque lo voy actualizando cada vez que resto con el ordena polinomio ya que le quito aquellos monomios que tengan de coeficiente 0
			m = dividendo.polinomio_[0] / m;
			cociente.polinomio_.push_back(m);
			divide = 1;
		}

		if(divide == 1)
		{
			divisor = p;
			divisor *= m;
			dividendo -= divisor;
		}
	}

	*this = cociente;
	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator/=(ed::Monomio const &m) // Me falta poner las precondiciones
{
	#ifndef NDEBUG
		assert(this->getGrado() >= m.getGrado());
		assert(this->esNulo() == false);
	#endif

	for (int i = 0; i<this->getNumeroMonomios(); i++)
	{
		this->polinomio_[i] /= m;
	}

	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator/=(double const &x) // Me falta poner las precondiciones
{
	ed::Monomio aux;
	aux = x;

	for(int i = 0; i<this->getNumeroMonomios(); i++)
	{
		this->polinomio_[i] /= aux;
	}

	this->ordenaPolinomio();

	// Se devuelve el objeto actual
	return *this;
}

///////////////////////////////////////////////////////////////////////

// Funciones lectura y escritura de la clase Polinomio

void ed::Polinomio::leerPolinomio() // Compribar que no pueda introducir dos monomios iguales y en caso de que se introduzca pedirle al usuario que vuelva aintroducirlo
{
	this->polinomio_.clear();
	ed::Monomio m;

	int n = 0;
	std::cout<<"Cuantos monomios quiere crear: ";
	std::cin>>n;
	std::cout<<""<<std::endl;

	for (int i = 0; i<n; i++)
	{
		m.leerMonomio();
		this->polinomio_.push_back(m);	
	}

	this->ordenaPolinomio();
}

void ed::Polinomio::escribirPolinomio()
{
	fflush(stdout);
	for(int i = 0; i<getNumeroMonomios(); i++)
	{
		if( ( (this->polinomio_[i].getCoeficiente()==0) || (this->polinomio_[i].getCoeficiente()>0) ) && (i!=0) )
		{
			std::cout<<" + ";
		}

		if(i!=0)
		{
			std::cout<<" ";
		}

		this->polinomio_[i].escribirMonomio();
		std::cout<<" ";
	}
}


///////////////////////////////////////////////////////////////////////

// Funciones auxiliares de la clase Polinomio


bool ed::Polinomio::esIgual(Polinomio const &p)
{
	for(int i = 0; i<this->getNumeroMonomios(); i++ )
    {
      if( (this->polinomio_[i].getCoeficiente() != p.polinomio_[i].getCoeficiente())||(this->polinomio_[i].getGrado() != p.polinomio_[i].getGrado()) )
      {
        return false;
      }
    }

   return true;
}


bool ed::Polinomio::esOrdenado() const
{
	int j = 0;

	for(int i=1; i<this->getNumeroMonomios(); i++){
		if( this->polinomio_[j].getGrado() < this->polinomio_[i].getGrado() ) // No se si funciona cuando llega al final del bucle
		{
			return false;
		}

		j++;
	}

	return true;
}


bool ed::Polinomio::compruebaMonomio(Monomio const &m)
{
	if ( (this->polinomio_.front().getCoeficiente() == m.getCoeficiente()) && (this->polinomio_.front().getGrado() == m.getGrado()) )
	{
		return true;
	}

	return false;
}


bool orden(ed::Monomio const &m1, ed::Monomio const &m2)
{
	return m1.getGrado() > m2.getGrado();
}

void ed::Polinomio::ordenaPolinomio()
{
	std::vector<ed::Monomio> aux;

	for(int i = 0; i<this->getNumeroMonomios(); i++)
	{
		if(this->polinomio_[i].getCoeficiente() != 0)
		{
			aux.push_back(polinomio_[i]);
		}
	}

	if(aux.empty())
	{
		ed::Monomio m;
		aux.push_back(m);
	}

	this->polinomio_.clear();
	this->polinomio_ = aux;

	std::sort(this->polinomio_.begin(), this->polinomio_.end(), orden);
}

double ed::Polinomio::calcularValor(int const &x)
{
	double valor = 0.0;

	for(int i = 0; i<this->getNumeroMonomios(); i++)
	{
		valor = valor + this->polinomio_[i].calcularValor(x);
	}

	return valor;
}

void ed::Polinomio::insertaMonomio(ed::Monomio m){
	this->polinomio_.push_back(m);
	this->ordenaPolinomio();
}

void ed::Polinomio::asignaPolinomio(std::vector<ed::Monomio> v_aux)
{
	this->polinomio_.clear();
	this->polinomio_ = v_aux;
	this->ordenaPolinomio();
}