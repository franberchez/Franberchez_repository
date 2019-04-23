/*!
	\file operadoresExternosPolinomios.hpp
	\brief Ficheros con operadores de monomios y polinomios
*/

#ifndef _OperadoresPolinomios_HPP_
#define _OperadoresPolinomios_HPP_

// Facilita la entrada y salida
#include <iostream>

#include "Polinomio.hpp"

using std::istream;
using std::ostream;

// Espacio de nombre de la asigantura: ed
namespace ed
{

////////////////////////////////////////////////////////////////////////////
	// Funciones y operadores que no pertenecen a la clase Polinomio


	////////////////////////////////////////////////////////////
	//! \name Operadores de igualdad

	/*! 
		\brief     Operador de igualdad: Comprueba si dos polinomios son iguales: p1 == p2. Si tienen los mismos monomios
		\attention Función sobrecargada
		\param     p1: objeto de tipo Polinomio pasado como referencia constante
		\param     p2: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
		\post	   El valor devuelto es verdadero si los dos polinomios tienen los mismos monomios
		\sa        getNumeroMonomios(), getVector()
	*/

	bool operator==(ed::Polinomio const & p1, ed::Polinomio const & p2);


	/*! 
		\brief     Operador de igualdad: Comprueba si el polinomio "p" es igual al monomio "m", es decir, si el polinomio "p" tiene un unico monomio que es igual a "m"
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
		\post	   El valor devuelto es verdadero si el polinomio tiene un unico monomio que es igual a “m”
		\sa        getNumeroMonomios(), getVector()
	*/

	bool operator==(ed::Polinomio const & p, ed::Monomio const & m);


	/*! 
		\brief     Operador de igualdad: Comprueba si el polinomio "p" es igual al monomio "m", es decir, si el polinomio "p" tiene un unico monomio que es igual a "m"
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
		\post	   El valor devuelto es verdadero si el polinomio tiene un unico monomio que es igual a “m”
		\sa        getNumeroMonomios(), getVector()
	*/

	bool operator==(ed::Monomio const & m, ed::Polinomio const & p);


	/*! 
		\brief     Operador de igualdad: Comprueba si el polinomio “p” es igual al número “x”, es decir, si el polinomio “p” tiene un unico monomio que es igual a “x”
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     x: objeto de tipo Real pasado como referencia constante
		\pre       Ninguna
		\post	   El valor devuelto es verdadero si el polinomio tiene un unico monomio que es igual a “x”
		\sa        getNumeroMonomios(), getVector()
	*/

	bool operator==(ed::Polinomio const & p, double const & x);


	/*! 
		\brief     Operador de igualdad: Comprueba si el polinomio “p” es igual al número “x”, es decir, si el polinomio “p” tiene un unico monomio que es igual a “x”
		\attention Función sobrecargada
		\param     x: objeto de tipo Real pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
		\post	   El valor devuelto es verdadero si el polinomio tiene un unico monomio que es igual a “x”
		\sa        getNumeroMonomios(), getVector()
	*/

	bool operator==(double const & x, ed::Polinomio const & p);

	////////////////////////////////////////////////////////////////////////////////////
	//! \name Operadores de desigualdad


	/*! 
		\brief     Operador de desigualdad: Comprueba si dos polinomios no son iguales: p1 != p2. Si no tienen los mismos monomios
		\attention Función sobrecargada
		\param     p1: objeto de tipo Polinomio pasado como referencia constante
		\param     p2: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
		\post	   El valor devuelto es verdadero si los dos polinomios no tienen los mismos monomios
		\sa        getNumeroMonomios(), getVector()
	*/

	bool operator!=(ed::Polinomio const & p1, ed::Polinomio const & p2);


	/*! 
		\brief     Operador de igualdad: Comprueba si el polinomio "p" no es igual al monomio "m", es decir, si el polinomio "p" no tiene un unico monomio que es igual a "m"
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
		\post	   El valor devuelto es verdadero si el polinomio no tiene un unico monomio que es igual a “m”
		\sa        getNumeroMonomios(), getVector()
	*/

	bool operator!=(ed::Polinomio const & p, ed::Monomio const & m);


	/*! 
		\brief     Operador de igualdad: Comprueba si el polinomio "p" no es igual al monomio "m", es decir, si el polinomio "p" no tiene un unico monomio que es igual a "m"
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
		\post	   El valor devuelto es verdadero si el polinomio no tiene un unico monomio que es igual a “m”
		\sa        getNumeroMonomios(), getVector()
	*/

	bool operator!=(ed::Monomio const & m, ed::Polinomio const & p);


	/*! 
		\brief     Operador de igualdad: Comprueba si el polinomio “p” no es igual al número “x”, es decir, si el polinomio “p” no tiene un unico monomio que es igual a “x”
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     x: objeto de tipo Real pasado como referencia constante
		\pre       Ninguna
		\post	   El valor devuelto es verdadero si el polinomio no tiene un unico monomio que es igual a “x”
		\sa        getNumeroMonomios(), getVector()
	*/

	bool operator!=(ed::Polinomio const & p, double const & x);


	/*! 
		\brief     Operador de igualdad: Comprueba si el polinomio “p” no es igual al número “x”, es decir, si el polinomio “p” no tiene un unico monomio que es igual a “x”
		\attention Función sobrecargada
		\param     x: objeto de tipo Real pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
		\post	   El valor devuelto es verdadero si el polinomio no tiene un unico monomio que es igual a “x”
		\sa        getNumeroMonomios(), getVector()
	*/

	bool operator!=(double const & x, ed::Polinomio const & p);


//////////////////////////////////////////////////////////////////////////////////////

	//! \name Operadores unarios


	/*! 
		\brief     Operador de unario suma: Devuelve una copia de del Polinomio "p": +p
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
		\post	   El polinomio devuelto es igual al polinomio "p", es decir, tiene los mismos monomios
		\sa        getNumeroMonomios(), getVector(), setCoeficiente(), getCoeficiente(), setGrado(), getGrado()
	*/

	ed::Polinomio & operator+(ed::Polinomio const & p);


	/*! 
		\brief     Operador de unario diferencia: Devuelve el opuesto del polinomio "p": -p
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
		\post	   El polinomio devuelto tiene todos sus monomios opuestos, es decir, el mismo grado pero su coeficiente opuesto
		\sa        getNumeroMonomios(), getVector(), setCoeficiente(), getCoeficiente(), setGrado(), getGrado()
	*/

	ed::Polinomio & operator-(ed::Polinomio const & p);


//////////////////////////////////////////////////////////////////////////////////////

	//! \name Operadores binarios de la suma


	/*! 
		\brief     Operador binario suma: Devuelve otro polinomio que es la suma de dos polinomios: p1 + p2
		\attention Función sobrecargada
		\param     p1: objeto de tipo Polinomio pasado como referencia constante
		\param     p2: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator+(ed::Polinomio const &p1, ed::Polinomio const &p2);


	/*! 
		\brief     Operador binario suma: Devuelve otro polinomio que es la suma de un polinomio y un monomio
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator+(ed::Polinomio const &p, ed::Monomio const & m);


	/*! 
		\brief     Operador binario suma: Devuelve otro polinomio que es la suma de un polinomio y un monomio
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator+(ed::Monomio const & m, ed::Polinomio const & p);


	/*! 
		\brief     Operador binario suma: Devuelve otro polinomio que es la suma de un polinomio y un numero real
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     x: objeto de tipo Real pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator+(ed::Polinomio const & p, double const & x);


	/*! 
		\brief     Operador binario suma: Devuelve otro polinomio que es la suma de un polinomio y un numero real
		\attention Función sobrecargada
		\param     x: objeto de tipo Real pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator+(double const & x, ed::Polinomio const & p);


		//////////////////////////////////////////////////////////
		//! \name Operador binario de la resta


	/*! 
		\brief     Operador binario diferencia: Devuelve otro polinomio que es la resta de dos polinomios: p1 - p2
		\attention Función sobrecargada
		\param     p1: objeto de tipo Polinomio pasado como referencia constante
		\param     p2: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator-(ed::Polinomio const &p1, ed::Polinomio const &p2);


	/*! 
		\brief     Operador binario diferencia: Devuelve otro polinomio que es la resta de un polinomio y un monomio
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator-(ed::Polinomio const &p, ed::Monomio const & m);


	/*! 
		\brief     Operador binario diferencia: Devuelve otro polinomio que es la resta de un polinomio y un monomio
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator-(ed::Monomio const & m, ed::Polinomio const & p);


	/*! 
		\brief     Operador binario diferencia: Devuelve otro polinomio que es la resta de un polinomio y un numero real
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     x: objeto de tipo Real pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator-(ed::Polinomio const & p, double const & x);


	/*! 
		\brief     Operador binario diferencia: Devuelve otro polinomio que es la resta de un polinomio y un numero real
		\attention Función sobrecargada
		\param     x: objeto de tipo Real pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator-(double const & x, ed::Polinomio const & p);


		///////////////////////////////////////////////////////////////////////////
		//! \name Operadores binarios de la multiplicación


	/*! 
		\brief     Operador binario producto: Devuelve otro polinomio que es la multiplicacion de dos polinomios: p1 * p2
		\attention Función sobrecargada
		\param     p1: objeto de tipo Polinomio pasado como referencia constante
		\param     p2: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator*(ed::Polinomio const &p1, ed::Polinomio const &p2);


	/*! 
		\brief     Operador binario producto: Devuelve otro polinomio que es la multiplicacion de un polinomio y un monomio
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator*(ed::Polinomio const &p, ed::Monomio const & m);


	/*! 
		\brief     Operador binario producto: Devuelve otro polinomio que es la multiplicacion de un polinomio y un monomio
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator*(ed::Monomio const & m, ed::Polinomio const & p);


	/*! 
		\brief     Operador binario diferencia: Devuelve otro polinomio que es la multiplicacion de un polinomio y un numero real
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     x: objeto de tipo Real pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator*(ed::Polinomio const & p, double const & x);


	/*! 
		\brief     Operador binario diferencia: Devuelve otro polinomio que es la multiplicacion de un polinomio y un numero real
		\attention Función sobrecargada
		\param     x: objeto de tipo Real pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       Ninguna
	*/

	ed::Polinomio & operator*(double const & x, ed::Polinomio const & p);

		///////////////////////////////////////////////////////////////////////////

		//! \name Operadores binarios de la división


	/*! 
		\brief     Operador binario producto: Devuelve otro polinomio que es la division de dos polinomios: p1 / p2
		\attention Función sobrecargada
		\param     p1: objeto de tipo Polinomio pasado como referencia constante
		\param     p2: objeto de tipo Polinomio pasado como referencia constante
		\pre  	   El grado de p2 debe ser menor o igual que el grado de p1
	*/

	ed::Polinomio & operator/(ed::Polinomio const &p1, ed::Polinomio const &p2);


	/*! 
		\brief     Operador binario producto: Devuelve otro polinomio que es la division de un polinomio y un monomio
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\pre       El grado del monomio es menor o igual que el grado del polinomio
	*/

	ed::Polinomio & operator/(ed::Polinomio const &p, ed::Monomio const & m);


	/*! 
		\brief     Operador binario producto: Devuelve otro polinomio que es la division de un polinomio y un monomio
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       El grado del polinomio es menor o igual que el grado del monomio
	*/

	ed::Polinomio & operator/(ed::Monomio const & m, ed::Polinomio const & p);


	/*! 
		\brief     Operador binario diferencia: Devuelve otro polinomio que es la division de un polinomio y un numero real
		\attention Función sobrecargada
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\param     x: objeto de tipo Real pasado como referencia constante
		\pre       El numero x no es 0.0
	*/

	ed::Polinomio & operator/(ed::Polinomio const & p, double const & x);


	/*! 
		\brief     Operador binario diferencia: Devuelve otro polinomio que es la division de un polinomio y un numero real
		\attention Función sobrecargada
		\param     x: objeto de tipo Real pasado como referencia constante
		\param     p: objeto de tipo Polinomio pasado como referencia constante
		\pre       El polinomio no tiene grado 0 y su coeficiente no es 0.0
	*/

	ed::Polinomio & operator/(double const & x, ed::Polinomio const & p);

	/////////////////////////////////////////////////////////////////////////////

   //! \name Sobrecarga de los operadores de flujo de la clase Polinomio.
	

    /*!
  		\brief  Sobrecarga del operador de flujo de salida o escritura "<<"
				\n Escribe en el flujo de salida el polinomio
		\param  stream: flujo de salida
		\param  p: objeto de tipo Polinomio pasado como referencia constante
		\pre    Ninguna
		\sa     operator>>
    */

    ostream &operator<<(ostream &stream, ed::Polinomio const &p);


	/*!
  		\brief  Sobrecarga del operador de flujo de entrada o lectura ">>"
				\n Lee desde le flujo de entrada un polinomio
		\param   stream: flujo de entrada
 		\param   p: objeto de tipo Polinomio pasado como referencia 
		\pre     Ninguna
		\sa      operator<<
    */

    istream &operator>>(istream &stream, ed::Polinomio &p);

}  // Fin de namespace ed.

#endif // _OperadoresPolinomios_HPP_
