/*! 
	\file operadoresExternosMonomios.hpp
	\brief Ficheros con los prototipos de los operadores externos de la clase Monomio
*/

#ifndef _OperadoresExternosMonomios_HPP_
#define _OperadoresExternosMonomios_HPP_

// Facilita la entrada y salida
#include <iostream>

#include "Monomio.hpp"

// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

// Espacio de nombre de la asigantura: ed
namespace ed
{
//////////////////////////////////////////////////////////////////////////////////////
	// Operadores externos que no pertenecen a la clase Monomio

	//! \name Operadores de igualdad

	/*! 
		\brief     Operador de igualdad: es un operador que comprueba si dos monomios son iguales (m1 == m2)
		\attention Función sobrecargada
		\param     m1: objeto de tipo Monomio pasado como referencia constante
		\param     m2: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
		\post	   Los dos monomios tienen el mismo grado y el mismo coeficiente
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los nuemros reales
		\sa        getCoeficiente(), getGrado()
	*/

	bool operator==(ed::Monomio const & m1, ed::Monomio const & m2);


	/*! 
		\brief     Operador de igualdad: es un operador que comprueba si un monomio es igual a un numero real (m == x)
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\param     x: objeto de tipo real pasado como referencia constante
		\pre       Ninguna
		\post	   El monomio tiene grado 0 y su coeficiente es igual al numero "x"
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado()
	*/

	bool operator==(ed::Monomio const & m, double const &x);


	/*! 
		\brief     Operador de igualdad: es un operador que comprueba si un monomio es igual a un numero real (x == m)
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\param     x: objeto de tipo real pasado como referencia constante
		\pre       Ninguna
		\post	   El monomio tiene grado 0 y su coeficiente es igual al numero "x"
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado()
	*/

	bool operator==(double const &x, ed::Monomio const & m);


	//! \name Operadores de desigualdad 

	/*! 
		\brief     Operador de desigualdad: es un operador que comprueba si dos monomios no son iguales (m1 != m2)
		\attention Función sobrecargada
		\param     m1: objeto de tipo Monomio pasado como referencia constante
		\param     m2: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
		\post	   Los dos monomios no tienen el mismo grado o no tienen el mismo coeficiente
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado()
	*/

	bool operator!=(ed::Monomio const & m1, ed::Monomio const & m2);


	/*! 
		\brief     Operador de desigualdad: es un operador que comprueba un monomio no es igual a un numero real (m == x)
		\attention Función sobrecargada
		\param     x: objeto de tipo real pasado como referencia constante
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
		\post	   El monomio no tiene grado 0 o su coeficiente no es igual al numero "x"
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado()
	*/

	bool operator!=(double const &x, ed::Monomio const & m);


	/*! 
		\brief     Operador de desigualdad: es un operador que comprueba un monomio no es igual a un numero real (x == m)
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\param     x: objeto de tipo real pasado como referencia constante
		\pre       Ninguna
		\post	   El monomio no tiene grado 0 o su coeficiente no es igual al numero "x"
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado()
	*/

	bool operator!=(ed::Monomio const & m, double const &x);


	///////////////////////////////////////////////////

	//! \name Operadores unarios prefijos

	/*! 
		\brief     Operador unario prefijo suma: es un operador que devuelve una copia del monomio ( "m" = +m )
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
		\post	   El monomio devuelto es igual al monomio "m", es decir, tiene el mismo grado y el mismo coeficiente
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado(), setCoeficiente(m.getCoeficiente()), setGrado(m.getGrado())
	*/


	ed::Monomio & operator+(ed::Monomio const & m);

	/*! 
		\brief     Operador unario prefijo resta: es un operador que devuelve el opuesto del Monomio ( "m" == -m )
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
		\post	   El monimio devuelto tiene el mismo grado que el monomio "m" pero su coeficiente es el opuesto
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado(), setCoeficiente(m.getCoeficiente()), setGrado(m.getGrado())
	*/

	ed::Monomio & operator-(ed::Monomio const & m);


	//////////////////////////////////////////////////////////

	//! \name Operador binario de la suma 

	/*! 
		\brief     Operador binario suma: es un operador que devuelve otro monomio que es la suma de los dos monomios ( m = m1 + m2 )
		\attention Función sobrecargada
		\param     m1: objeto de tipo Monomio pasado como referencia constante
		\param     m2: objeto de tipo Monomio pasado como referencia constante
		\pre       Los dos monomios m1 y m2 tienen el mismo grado
		\post	   El monomio devuelto tiene el mismo grado que los monomios m1 y m2
		\post	   El coeficiente del monomio devuelto es la suma de los coeficientes de los monomios
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado(), setCoeficiente(m.getCoeficiente()), setGrado(m.getGrado())
	*/

	 ed::Monomio & operator+(ed::Monomio const &m1, ed::Monomio const &m2);


	//////////////////////////////////////////////////////////

	//! \name Operador binario de la resta 

	/*! 
		\brief     Operador binario resta: es un operador que devuelve otro monomio que es la resta de dos monomios ( m = m1 -m2)
		\attention Función sobrecargada
		\param     m1: objeto de tipo Monomio pasado como referencia constante
		\param     m2: objeto de tipo Monomio pasado como referencia constante
		\pre       Los dos monomios m1 y m2 tienen el mismo grado
		\post	   El monomio devuelto tiene el mismo grado que los monomios m1 y m2
		\post	   El coeficiente del monomio devuelto es la resta de los coeficientes de los monomios m1 y m2
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado(), setCoeficiente(m.getCoeficiente()), setGrado(m.getGrado())
	*/

	 ed::Monomio & operator-(ed::Monomio const & m1, ed::Monomio const & m2);


	///////////////////////////////////////////////////////////////////////////

	//! \name Operadores binarios de la multiplicación 

	/*! 
		\brief     Operador binario multiplicacion: es un operador que devuelve otro monomio que es el producto de dos monomios ( m = m1 * m2 )
		\attention Función sobrecargada		
		\param     m1: objeto de tipo Monomio pasado como referencia constante
		\param     m2: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
		\post	   El monomio devuelto tiene un grado que es la suma de los grados de los monomios m1 y m2
		\post	   El coeficiente del monomio devuelto es el producto de los coeficientes de los monomios m1 y m2
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado(), setCoeficiente(m.getCoeficiente()), setGrado(m.getGrado())
	*/

	 ed::Monomio & operator*(ed::Monomio const & m1, ed::Monomio const & m2);


	/*! 
		\brief     Operador binario multiplicacion: es un operador que devuelve otro monomio que es el producto de un monomio por un numero real ( m = x * m )
		\attention Función sobrecargada
		\param     x: objeto de tipo real pasado como referencia constante
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\pre       Ninguna
		\post	   El monomio devuelto tiene el mismo grado que el monomio "m"
		\post	   El coeficiente del monomio devuelto es el producto del monomio "m" por el numero "x"
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado(), setCoeficiente(m.getCoeficiente()), setGrado(m.getGrado())
	*/

	 ed::Monomio & operator*(double const &x, ed::Monomio const & m);

	///////////////////////////////////////////////////////////////////////////

	//! \name Operadores binarios de la división 

	/*! 
		\brief     Operador binario division: es un operador que devuelve otro monomio que es la division de los dos monomios ( m = m1 / m2 )
		\attention Función sobrecargada
		\param     m1: objeto de tipo Monomio pasado como referencia constante
		\param     m2: objeto de tipo Monomio pasado como referencia constante
		\pre       El grado del monomio m2 es menor o igual que el grado del monomio m1
		\pre       El coeficiente del monomio m2 no es 0.0
		\post	   El monomio devuelto tiene un grado que es la resta de los grados de los monomios m1 y m2
		\post	   El coeficiente del monomio devuelto es la division de los coeficientes de los monomios m1 y m2
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado(), setCoeficiente(m.getCoeficiente()), setGrado(m.getGrado())
	*/

	 ed::Monomio & operator/(ed::Monomio const & m1, ed::Monomio const & m2);


	/*! 
		\brief     Operador binario division: es un operador que devuelve otro monomio que es la division del monomio "m" por el numero real "x" ( m = m / x )
		\attention Función sobrecargada
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\param     x: objeto de tipo real pasado como referencia constante
		\pre       El numero "x" no es 0.0
		\post	   El monomio devuelto tiene el mismo grado que el monomio "m"
		\post	   El coeficiente del monomio devuelto es la division del coeficiente del monomio "m" por el numero "x"
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado(), setCoeficiente(m.getCoeficiente()), setGrado(m.getGrado())
	*/

	 ed::Monomio & operator/(ed::Monomio const & m, double const &x);


	/*! 
		\brief     Operador binario division: es un operador que devuelve otro monomio que es la division del numero "x" entre el monomio "m" ( m = x / m )
		\attention Función sobrecargada
		\param     x: objeto de tipo real pasado como referencia constante
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\pre       El grado del monomio es 0 y su coeficente es distinto de 0.0
		\post	   El monomio devuelto tiene el grado igual a 0
		\post	   El coeficiente del monomio devuelto es la división del número “x” por el coeficiente del monomio “m”
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado(), setCoeficiente(m.getCoeficiente()), setGrado(m.getGrado())
	*/

	 ed::Monomio & operator/(double const &x, ed::Monomio const & m);


	/////////////////////////////////////////////////////////////////////////////

	//! \name Operador potencia de un monomio

	/*!
		\brief     Operador de potencia: es un operador que calcula la potencia de un monomio
		\param     m: objeto de tipo Monomio pasado como referencia constante
		\param     x: objeto de tipo real pasado como referencia constante
		\pre       El grado de la potencia "x" debe ser mayor o igual que 0
		\post	   El coeficiente del monomio devuelto tiene que ser igual al coeficiente del monomio original elevado al grado pasado como parametro "x"
		\post	   El monomio devuelto tiene un grado igual al grado del monomio orginal por el grado al que elevamos el monomio "x"
		\note	   Se debe utilizar COTA_ERROR para controlar la precisión de los numeros reales
		\sa        getCoeficiente(), getGrado(), setCoeficiente(coeficiente), setGrado(grado)		
	*/

	 ed::Monomio & operator^(ed::Monomio const &m, int const &x);


	////////////////////////////////////////////////////////////////////////////////

	//! \name Sobrecarga de los operadores de entrada y salida 

	/*!
  		\brief  Sobrecarga del operador de flujo de entrada o lectura ">>"
				\n Lee desde le flujo de entrada los atributos de un monomio separados por espacios
		\param   stream: flujo de entrada
 		\param   m: objeto de tipo Monomio pasado como referencia 
		\pre     Ninguna
		\post    Ninguna
		\sa      operator<<
    */

	 istream &operator>>(istream &stream, ed::Monomio &m);


    /*!
  		\brief  Sobrecarga del operador de flujo de salida o escritura "<<"
				\n Escribe en el flujo de salida los atributos del monomio separados por espacios ( coeficiente grado )
		\param  stream: flujo de salida
		\param  m: objeto de tipo Monomio pasado como referencia constante
		\pre    Ninguna
		\post   Ninguna
		\sa     operator>>
    */

	 ostream &operator<<(ostream &stream, ed::Monomio const &m);



}  // Fin de namespace ed.

#endif // _OperadoresExternosMonomios_HPP_


