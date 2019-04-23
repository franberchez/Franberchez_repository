/*! 
   \file  Monomio.cpp
   \brief Fichero que contiene el código de las funciones de la clase Monomio
*/


//  Ficheros de cabecera
#include <iostream>
#include <math.h>
#include <cstdlib>

#include "Monomio.hpp"

// Operadores de asignación

ed::Monomio & ed::Monomio::operator=(ed::Monomio const &m)
{
	this->setCoeficiente(m.getCoeficiente());
	this->setGrado(m.getGrado());

	#ifndef NDEBUG
		assert(std::abs (this->getCoeficiente() - m.getCoeficiente()) < COTA_ERROR );
		assert(this->getGrado() == m.getGrado());
	#endif

	// Se devuelve el objeto actual
	return *this;
}


ed::Monomio & ed::Monomio::operator=(double const &x)
{
	this->setCoeficiente(x);
	this->setGrado(0);

	#ifndef NDEBUG
		assert(this->getGrado() == 0);
		assert(std::abs (this->getCoeficiente() - x) < COTA_ERROR );
	#endif

	// Se devuelve el objeto actual
	return *this;
}



//////////////////////////////////////////////////////////////

// Operadores aritméticos y asignación

//pongo ed:: porque la clase monomio queda definida dentro del espcacio de nombres ed y si no lo pongo no podre utilizar dicho metodo de dicha clase
ed::Monomio & ed::Monomio::operator+=(ed::Monomio const &m)
{
	#ifndef NDEBUG
		assert(this->getGrado() == m.getGrado());
	#endif

	int suma = 0;
	suma = this->getCoeficiente() + m.getCoeficiente();

	this->setCoeficiente(suma);

	#ifndef NDEBUG
		assert(std::abs (this->getCoeficiente() - suma) < COTA_ERROR);
		assert(this->getGrado() == getGrado()); //He supuesto una postcondicion que es la misma que la precondicion
	#endif

	// Se devuelve el objeto actual
	return *this;
}



ed::Monomio & ed::Monomio::operator-=(ed::Monomio const &m)// ¿No deberíamos poner el aserto o la condicion que que la diferencia de coeficiente no debe dar un numero negativo?
{
	#ifndef NDEBUG
		assert(this->getGrado() == m.getGrado());
	#endif

		int resta;
		resta = this->getCoeficiente() - m.getCoeficiente();

		this->setCoeficiente(resta);

	#ifndef NDEBUG
		assert(std::abs(this->getCoeficiente() - resta) < COTA_ERROR);
		assert(this->getGrado() == m.getGrado());
	#endif

	//Se devuelve el objeto actual
	return *this;
}


ed::Monomio & ed::Monomio::operator*=(ed::Monomio const &m)
{
	double producto;
	int suma;

	producto = this->getCoeficiente() * m.getCoeficiente();
	suma = this->getGrado() + m.getGrado();

	this->setCoeficiente(producto);
	this->setGrado(suma);
	
	#ifndef NDEBUG
		assert(std::abs(this->getCoeficiente() - producto) < COTA_ERROR);
		assert(this->getGrado() == suma);
	#endif

	//Se devuelve el objeto actual
	return *this;

}


ed::Monomio & ed::Monomio::operator*=(double const &x)
{
	int grado;
	grado = this->getGrado();

	double producto;
	producto = this->getCoeficiente() * x;

	this->setCoeficiente(producto);

	#ifndef NDEBUG
		assert(std::abs(this->getCoeficiente() - producto) < COTA_ERROR);
		assert(this->getGrado() == grado);
	#endif

	//Se devuelve el objeto actual
	return *this;
}


ed::Monomio & ed::Monomio::operator/=(ed::Monomio const &m)
{
	#ifndef NDEBUG
		assert(m.getGrado() <= this->getGrado());
	#endif

	double division;
	division = this->getCoeficiente() / m.getCoeficiente();

	int diferencia;
	diferencia = this->getGrado() - m.getGrado();

	this->setCoeficiente(division);
	this->setGrado(diferencia);

	#ifndef NDEBUG
		assert(std::abs(this->getCoeficiente() - division) < COTA_ERROR);
		assert(this->getGrado() == diferencia);
	#endif

	//Se devuelve el objeto actual
	return *this;
}


ed::Monomio & ed::Monomio::operator/=(double const &x)
{
	#ifndef NDEBUG
		assert(x != 0.0);
	#endif

	int grado;
	grado = this->getGrado();

	int division;
	division = this->getCoeficiente() / x;

	this->setCoeficiente(division);

	#ifndef NDEBUG
		assert(std::abs(this->getCoeficiente() - division) < COTA_ERROR);
		assert(this->getGrado() == grado);
	#endif

	//Se devuelve el objeto actual
	return *this;
}

///////////////////////////////////////////////////////////////////////

// Funciones lectura y escritura de la clase Monomio

void ed::Monomio::leerMonomio()
{
	double coeficiente;
	int grado;

	std::cout<<"Introduzca el coeficiente del monomio: ";
	std::cin>>coeficiente;
	std::cout<<""<<std::endl;

	std::cout<<"Introduzca el grado el monomio: ";
	std::cin>>grado;
	std::cout<<""<<std::endl;

		if(grado < 0){

			while(grado < 0){

				std::cout<<"El grado que ha introducido es menor que 0, por favor vuelva a introducirlo: ";
				std::cin>>grado;

			}
		}

	this->setCoeficiente(coeficiente);
	this->setGrado(grado);

	#ifndef NDEBUG
		assert(this->getGrado() >= 0);
	#endif
}


void ed::Monomio::escribirMonomio() // Le he quitado los std::endl para que a la hora de mostrar el polinomio no me haga salto de line por cada monomio
{

	if(this->getGrado() == 0){
		std::cout<<this->getCoeficiente();
	}

	else{

		if(this->getGrado() == 1){

			if( std::abs(this->getCoeficiente() - 1) < COTA_ERROR){//1
				std::cout<<"X";
			}

			else{

				if( std::abs(this->getCoeficiente() + 1) < COTA_ERROR){//-1
					std::cout<<"-X";
				}

				else{
					std::cout<<this->getCoeficiente()<<"X";;
				}	
			}
		}

		else{

			if( std::abs(this->getCoeficiente() - 1) < COTA_ERROR){//1
				std::cout<<"X^"<<this->getGrado();
			}

			else{

				if( std::abs(this->getCoeficiente() + 1) < COTA_ERROR){//-1
					std::cout<<"-X^"<<this->getGrado();
				}

				else{
					std::cout<<this->getCoeficiente()<<"X^"<<this->getGrado();
				}
			}
		}
	}

}

///////////////////////////////////////////////////////////////////////

// Funciones auxiliares de la clase Monomio

double ed::Monomio::calcularValor(double const &x)
{
	double valor;
	valor = this->getCoeficiente() * ( pow(x, this->getGrado()) );

	return valor;
}

ed::Monomio ed::Monomio::derivada()
{
	if(this->getGrado() < 0){
		std::cout<<"El grado del monomio que se acaba de leer es un grado negativo"<<std::endl;
		exit(-1);
	}

	ed::Monomio *nuevo = new ed::Monomio();

		if(this->getGrado() == 0){
			(*nuevo).setCoeficiente(0.0);
			(*nuevo).setGrado(0);
			return *nuevo;
		}

	(*nuevo).setCoeficiente(this->getCoeficiente()*this->getGrado());
	(*nuevo).setGrado(this->getGrado()-1);

	return *nuevo;
}

ed::Monomio ed::Monomio::integral()
{
	if(this->getGrado() < 0){
		std::cout<<"El grado del monomio que se acaba de leer es un grado negativo"<<std::endl;
		exit(-1);
	}

	ed::Monomio *nuevo = new ed::Monomio();

	(*nuevo).setGrado(this->getGrado()+1);
	(*nuevo).setCoeficiente(this->getCoeficiente()/(*nuevo).getGrado());

	return *nuevo;
}