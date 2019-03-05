/*! 
   \file  operadoresExternosMonomios.cpp
	\brief Ficheros con el código de los operadores externos de la clase Monomio
*/


//  Ficheros de cabecera
#include <iostream>
#include <cstdlib>

#include "operadoresExternosMonomios.hpp"


//  Se incluyen los operadores sobrecargados dentro del espacio de nombres ed
namespace ed 
{
	// Operadores de igualdad
	
	// COMPLETAR

	bool operator==(ed::Monomio const & m1, ed::Monomio const & m2)
	{
		bool b = (std::abs( m1.getCoeficiente() - m2.getCoeficiente() ) < COTA_ERROR ) and (m1.getGrado() == m2.getGrado());

		#ifndef NDEBUG
			assert( b == ( (std::abs( m1.getCoeficiente() - m2.getCoeficiente() ) < COTA_ERROR ) and ( m1.getGrado() == m2.getGrado() ) ) );
		#endif

		return b;
	}


	bool operator==(ed::Monomio const & m, double const &x)
	{
		bool b = (std::abs(m.getCoeficiente() - x) < COTA_ERROR) and (m.getGrado() == 0);

		#ifndef NDEBUG
			assert( b == ( (std::abs(m.getCoeficiente() - x) < COTA_ERROR) and (m.getGrado() == 0) ) );
		#endif

		return b;
	}


	bool operator==(double const &x, ed::Monomio const & m)
	{
		bool b = (std::abs(x - m.getCoeficiente()) < COTA_ERROR) and (m.getGrado() == 0);

		#ifndef NDEBUG
			assert( b == ( (std::abs(x - m.getCoeficiente()) < COTA_ERROR) and (m.getGrado() == 0) ) );
		#endif

		return b;
	}



	// Operadores de desigualdad


	bool operator!=(ed::Monomio const & m1, ed::Monomio const & m2)
	{
		bool b = (std::abs(m1.getCoeficiente() - m2.getCoeficiente()) > COTA_ERROR) and (m1.getGrado() != m2.getGrado() );

		#ifndef NDEBUG
			assert ( b == ( (std::abs(m1.getCoeficiente() - m2.getCoeficiente()) > COTA_ERROR) and (m1.getGrado() != m2.getGrado() ) ) );
		#endif

		return b;
	}


	bool operator!=(double const &x, ed::Monomio const & m)
	{
		bool b = (std::abs(x - m.getCoeficiente()) > COTA_ERROR) and (m.getGrado() != 0);

		#ifndef NDEBUG
			assert( b == ( (std::abs(x - m.getCoeficiente()) > COTA_ERROR) and (m.getGrado() != 0) ) );
		#endif

		return b;
	}


	bool operator!=(ed::Monomio const &m, double const &x)
	{
		bool b = (std::abs(m.getCoeficiente() - x) > COTA_ERROR) and (m.getGrado() != 0);

		#ifndef NDEBUG
			assert( b == ( (std::abs(m.getCoeficiente() - x) > COTA_ERROR) and (m.getGrado() != 0) ) );
		#endif

		return b;
	}
	

	////////////////////////////////////////////////////////////

	// Operadores unarios prefijos 

	// COMPLETAR
	ed::Monomio & operator+(ed::Monomio const & m)
	{
		// Se crea un nuevo objeto
		ed::Monomio *nuevo = new ed::Monomio();
		(*nuevo).setCoeficiente(m.getCoeficiente());
		(*nuevo).setGrado(m.getGrado());

		#ifndef NDEBUG
			assert( (std::abs((*nuevo).getCoeficiente() - m.getCoeficiente()) < COTA_ERROR) and ( (*nuevo).getGrado() == m.getGrado() ) );
		#endif

		// Se devuelve el resultado
		return *nuevo;
	}

	ed::Monomio & operator-(ed::Monomio const & m)
	{
		ed::Monomio *nuevo = new ed::Monomio();
		double coeficiente = (-1) * m.getCoeficiente();

		(*nuevo).setCoeficiente(coeficiente);
		(*nuevo).setGrado(m.getGrado());

		#ifndef NDEBUG
			assert( (std::abs( (*nuevo).getCoeficiente() - m.getCoeficiente() ) > COTA_ERROR) and ( (*nuevo).getGrado() == m.getGrado() ) );
		#endif

		// Se devuelve el resultado
		return *nuevo;			
	}


	////////////////////////////////////////////////////////////
	// Operadores aritméticos binarios
	//Suma

	ed::Monomio & operator+ (ed::Monomio const &m1, ed::Monomio const &m2)
	{

		#ifndef NDEBUG
			assert( m1.getGrado() == m2.getGrado() );
		#endif

		// Se crea un nuevo objeto
		ed::Monomio *nuevo = new ed::Monomio();
		double suma = m1.getCoeficiente() + m2.getCoeficiente();

		(*nuevo).setCoeficiente(suma);
		(*nuevo).setGrado(m1.getGrado());


		#ifndef NDEBUG
			assert( (std::abs( (*nuevo).getCoeficiente() - suma ) < COTA_ERROR) );
			assert( ( (*nuevo).getGrado() == m1.getGrado() ) and ( (*nuevo).getGrado() == m2.getGrado() ) );
		#endif

		// Se devuelve el resultado
		return *nuevo;
	}


	////////////
	// Resta

	 ed::Monomio & operator-(ed::Monomio const & m1, ed::Monomio const & m2)
	 {
	 	#ifndef NDEBUG
	 		assert( m1.getGrado() == m2.getGrado() );
	 	#endif

	 	ed::Monomio *nuevo = new ed::Monomio();
	 	double resta = m1.getCoeficiente() - m2.getCoeficiente();

	 	(*nuevo).setCoeficiente(resta);
	 	(*nuevo).setGrado(m1.getGrado());

	 	#ifndef NDEBUG
			assert( (std::abs( (*nuevo).getCoeficiente() - resta ) < COTA_ERROR) );
			assert( ( (*nuevo).getGrado() == m1.getGrado() ) and ( (*nuevo).getGrado() == m2.getGrado() ) );
		#endif

		// Se devuelve el resultado
		return *nuevo;
	 }


	//////////////////
	// Multiplicación

	ed::Monomio & operator*(ed::Monomio const & m1, ed::Monomio const & m2)
	{
		ed::Monomio *nuevo = new ed::Monomio();
		double producto = m1.getCoeficiente() * m2.getCoeficiente();
		int suma = m1.getGrado() + m2.getGrado();

		(*nuevo).setCoeficiente(producto);
		(*nuevo).setGrado(suma);

		#ifndef NDEBUG
			assert( (std::abs( (*nuevo).getCoeficiente() - producto ) < COTA_ERROR) );
			assert ( (*nuevo).getGrado() == suma );
		#endif

		// Se devuelve el resultado
		return *nuevo;
	}

	 ed::Monomio & operator*(double const &x, ed::Monomio const & m)
	 {
	 	ed::Monomio *nuevo = new ed::Monomio();
	 	double producto = x * m.getCoeficiente();

	 	(*nuevo).setCoeficiente(producto);
	 	(*nuevo).setGrado(m.getGrado());

	 	#ifndef NDEBUG
	 		assert( (std::abs( (*nuevo).getCoeficiente() - producto ) < COTA_ERROR) );
	 		assert( (*nuevo).getGrado() == m.getGrado() );
	 	#endif

	 	// Se decuelve el resultado
	 	return *nuevo;
	 }


	////////////
	// División

	 ed::Monomio & operator/(ed::Monomio const & m1, ed::Monomio const & m2)
	 {
	 	#ifndef NDEBUG
	 		assert(m2.getGrado() <= m1.getGrado());
	 		assert(m2.getCoeficiente() != 0.0);
	 	#endif

	 	ed::Monomio *nuevo = new ed::Monomio();
	 	double division = m1.getCoeficiente() / m2.getCoeficiente();
	 	int resta = m1.getGrado() - m2.getGrado();

	 	(*nuevo).setCoeficiente(division);
	 	(*nuevo).setGrado(resta);

	 	#ifndef NDEBUG
	 		assert( std::abs( (*nuevo).getCoeficiente() - division ) < COTA_ERROR ); // SALTA ESTE
	 		assert( (*nuevo).getGrado() == resta );
	 	#endif

	 	// Se devuelve el resultado
	 	return *nuevo;
	 }


	 ed::Monomio & operator/(ed::Monomio const & m, double const &x)
	 {
	 	#ifndef NDEBUG
	 		assert( x != 0.0 );
	 	#endif

	 	ed::Monomio *nuevo = new ed::Monomio();
	 	double division = m.getCoeficiente() / x;

	 	(*nuevo).setCoeficiente(division);
	 	(*nuevo).setGrado(m.getGrado());

	 	#ifndef NDEBUG
	 		assert( (*nuevo).getGrado() == m.getGrado() );
	 		assert( std::abs( (*nuevo).getCoeficiente() - division ) < COTA_ERROR );
	 	#endif

	 	// Se devuelve el resultado
	 	return *nuevo;
	 }


	 ed::Monomio & operator/(double const &x, ed::Monomio const & m)
	 {
	 	#ifndef NDEBUG
	 		assert( (m.getGrado() == 0) and (m.getCoeficiente() != 0.0) );
	 	#endif

	 	ed::Monomio *nuevo = new ed::Monomio();
	 	double division = x / m.getCoeficiente();

	 	(*nuevo).setCoeficiente(division);
	 	(*nuevo).setGrado(0);

	 	#ifndef NDEBUG
	 		assert( m.getGrado() == 0 );
	 		assert( std::abs( (*nuevo).getCoeficiente() - division ) < COTA_ERROR );
	 	#endif

	 	// Se devuelve el resultado
	 	return *nuevo;
	 }


	/////////////////////////////////////////////////////////////////////////////

	//  Sobrecarga del operador de entrada
	istream &operator>>(istream &stream, ed::Monomio &m) 
	{
		double coeficiente;
		int grado;

		stream >> coeficiente;
		m.setCoeficiente(coeficiente);

		stream >> grado;

		if(grado < 0){
			std::cout<<"FIN DEL PROGRAMA, GRADO NEGATIVO";
			exit(-1);
		}

		m.setGrado(grado);

   		// Se devuelve el flujo de entrada
		return stream;
	}


	//  Sobrecarga del operador de salida
	ostream &operator<<(ostream &stream, ed::Monomio const &m) 
	{
		stream << m.getCoeficiente();
		stream << " ";
		stream << m.getGrado();

		// Se devuelve el flujo de salida
		return stream;
	}


	// Operador potencia

	ed::Monomio & operator^(ed::Monomio const & m ,int const &x)
	{

		#ifndef NDEBUG
			assert(x >= 0);
		#endif

		ed::Monomio *nuevo = new ed::Monomio();
		double coeficiente = std::pow(m.getCoeficiente(), x);
		int grado = m.getGrado() * x;

		(*nuevo).setCoeficiente(coeficiente);
		(*nuevo).setGrado(grado);


		#ifndef NDEBUG
			assert( std::abs( (*nuevo).getCoeficiente() - coeficiente ) < COTA_ERROR );
			assert( (*nuevo).getGrado() == grado );
		#endif

		return *nuevo;
	}



}  // namespace ed
