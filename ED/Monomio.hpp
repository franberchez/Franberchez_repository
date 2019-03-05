/*! 
	\file Monomio.hpp
	\brief Definición de la clase Monomio
*/

#ifndef _MONOMIO_HPP_
#define _MONOMIO_HPP_

// Para usar la funciones pow y std::abs
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>

#define COTA_ERROR 1.0e-6  //!< Cota de error para la comparación números reales

// Se incluye la clase Monomio dentro del espacio de nombre de la asigantura: ed
namespace ed
{
//!  Definición de la clase Monomio:  \f$ coeficiente \hspace{1ex} X^{grado} \f$ 
class Monomio
{
	//! \name Atributos privados de la clase Monomio
	private:

	double coeficiente_;
	int  grado_;


	//! \name Funciones o métodos públicos de la clase Monomio
	public:

	//! \name Constructores de la clase Monomio
	/*!
			\brief 		Constructor crea un monomio a partir de su coeficiente y su grado
			\attention 	Funcion sobrecargada
			\note 		Funcion inline
			\warning 	Los parametros tienen valores por defecto
			\param 		coeficiente: coeficiente del monomio. Valor por defecto 0.0
			\param 		grado: grado del monomio. Valor por defecto 0
			\pre 		El grado es mayor o igual que 0
			\post 		El coeficiente del monomio es igual al valor del parametro "coeficiente"
			\post 		El grado del monomio es igual al valor del parametro "grado"
			\sa 		setCoeficiente(coeficiente), setGrado(grado), getCoeficiente(), getGrado()
	*/

	inline Monomio(double coeficiente=0.0, int grado=0){

		#ifndef NDEBUG
			assert(grado >= 0);
		#endif //NDEBUG

		this->setCoeficiente(coeficiente);
		this->setGrado(grado);

		#ifndef NDEBUG
			assert(std::abs(this->getCoeficiente() - coeficiente) < COTA_ERROR);
			assert(this->getGrado() == grado);
		#endif

	}

	/*!
			\brief 		Constructor copia que crea un monomio a partir de otro monomio
			\attention 	Funcion sobrecargada
			\note 		Funcion inline
			\warning 	Es necesario que tanto la funcion getCoeficiente como getGrado sean const
			\param 		m: monomio que contiene que contiene el coeficiente y el grado para crear otro monomio
			\pre 		Ninguna
			\post 		El coeficiente del monomio es igual al valor del parametro "coeficiente"
			\post 		El grado del monomio es igual al valor del parametro "grado"
			\sa 		setCoeficiente(m.getCoeficiente()), setGrado(m.getGrado()), getCoeficiente(), getGrado()
	*/

	inline Monomio(const Monomio &m){

		this->setCoeficiente(m.getCoeficiente());
		this->setGrado(m.getGrado());

		#ifndef NDEBUG
			assert(std::abs(this->getCoeficiente() - m.getCoeficiente()) < COTA_ERROR);
			assert(this->getGrado() == m.getGrado());
		#endif

	}



	//! \name Observadores: funciones de consulta de la clase Monomio

	/*!
			\brief 		Funcion que devuelve el grado del monomio
			\warning 	Se utiliza el modificador const en la definicion de la funcion para poder definir el constructor de copia y el operador asignacion
			\note 		Funcion inline
			\return 	Grado "grado_" del monomio (tipo natural)
			\pre 		Ninguna
			\post 		El grado del monomio debe ser igual al valor devuelto
			\sa 		getCoeficiente()
	*/

	inline int getGrado() const{
		return grado_;
	}

	/*!
			\brief 		Funcion que devuelve el coeficiente del monomio
			\warning 	Se utiliza el modificador const en la definicion de la funcion para poder definir el constructor de copia y el operador asignacion
			\note 		Funcion inline
			\return 	Coeficiente "coeficiente_" del monomio (tipo real)
			\pre 		Ninguna
			\post 		El coeficiente del monomio debe ser igual al valor devuelto
			\sa 		getGrado()
	*/

	inline double getCoeficiente() const{
		return coeficiente_;
	}



	//! \name Funciones de modificación de la clase Monomio

	/*!
			\brief 		Funcion que asigna un valor "x" a la variable coeficiente del monomio
			\note 		Funcion inline
			\param 		x: nuevo valor del coeficiente del monomio (tipo double)
			\pre 		Ninguna
			\post 		El coeficiente del monomio es igual al numero real "x"
			\note 		Se debe utilizar COTA_ERROR para controlar la precision de los numeros reales
			\sa 		setGrado(n)
	*/

	inline void setCoeficiente(double x){
		coeficiente_ = x;

		#ifndef NDEBUG
			assert(std::abs(coeficiente_ - x) < COTA_ERROR);
		#endif

	}

	/*!
			\brief 		Funcion que asigna un valor "n" a la variable grado del monomio
			\note 		Funcion inline
			\param 		n: nuevo valor del grado del monomio (tipo entero)
			\pre 		El numero entero "n" es mayor o igual que 0
			\post 		El grado del monomio es igual al numero entero "n"
			\sa 		setCoeficiente(x)
	*/

	inline void setGrado(int n){
		#ifndef NDEBUG
			assert(n >= 0);
		#endif

		grado_ = n;

		#ifndef NDEBUG
			assert(grado_ == n);
		#endif
	}



	/////////////////////////////////////////////////

	//! \name Operadores de la clase Monomio

	// Operadores de asignación

	/*! 
			\brief     Operador de asignacion: operador que "copia" un monomio en otro monomio
			\attention Se sobrecarga el operador de asignación "="
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\param     m: objeto de tipo Monomio pasado como referencia constante
			\pre 	   Ninguna
			\post	   El coeficiente del monomio es igual al coeficiente del monomio “m”
			\post	   El grado del monomio es igual al grado del monomio “m”
			\note	   Se debe utilizar COTA_ERROR para controlar la precision de los numeros reales
			\sa        getCoeficiente(), getGrado(), setCoeficiente(coeficiente), setGrado(grado)
	*/
		Monomio & operator=(Monomio const &m);


	/*! 
			\brief     Operador de asignacion: operador que hace que el grado del monomio modificado sea 0 y su coeficiente sea el numero real "x"
			\attention Se sobrecarga el operador de asignación "="
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\param     x: nuevo valor del coeficiente del monomio (tipo real)
			\pre 	   Ninguna
			\post	   El grado del monomio es igual 0
			\post	   El coeficiente del monomio es igual al número real “x”
			\note	   Se debe utilizar COTA_ERROR para controlar la precision de los numeros reales
			\sa        getCoeficiente(), getGrado(), setCoeficiente(coeficiente), setGrado(grado)
	*/
		Monomio & operator=(double const &x);


	// Operadores aritméticos y asignación

	/*! 
			\brief     Operador de suma: operador que modifica el monomio sumandole otro monomio de igual grado
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\param     m: objeto del tipo Mononomio pasado como referencia constante
			\pre	   El monomio "m" tiene el mismo grado que el monomio actual
			\post	   El coeficiente del monomio actual se ha incrementado con el coeficiente del monomio "m"
			\post	   El grado del monomio actual no ha sido modificado
			\note	   Se debe utilizar COTA_ERROR para controlar la precision de los numeros reales
			\sa        getCoeficiente(), getGrado(), setCoeficiente(coeficiente), setGrado(grado)
	*/
		Monomio & operator+=(Monomio const &m);

	/*! 
			\brief     Operador de diferencia: operador que modifica el monomio restandole otro monomio de igual grado
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\param     m: objeto del tipo Mononomio pasado como referencia constante
			\pre	   El monomio "m" tiene el mismo grado que el monomio actual
			\post	   El coeficiente del monomio actual se ha decrementado con el coeficiente del monomio "m"
			\post	   El grado del monomio actual no ha sido modificado
			\note	   Se debe utilizar COTA_ERROR para controlar la precision de los numeros reales
			\sa        getCoeficiente(), getGrado(), setCoeficiente(coeficiente), setGrado(grado)
	*/

		Monomio & operator-=(Monomio const &m);


	/*! 
			\brief     Operador de producto: operador que modifica el monomio multiplicando por otro monomio
			\attention Se sobrecarga el operador de producto "*="
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\param     m: objeto del tipo Mononomio pasado como referencia constante
			\pre 	   Ninguna
			\post	   El coeficiente del monomio actual se ha multiplicado por el coeficiente del monomio “m”
			\post	   El grado del monomio actual se ha incrementado con el grado del monomio “m”
			\note	   Se debe utilizar COTA_ERROR para controlar la precision de los numeros reales
			\sa        getCoeficiente(), getGrado(), setCoeficiente(coeficiente), setGrado(grado)
	*/
	
		Monomio & operator*=(Monomio const &m);

	/*! 
			\brief     Operador de producto: operador que modifica el monomio multiplicando por un numero real
			\attention Se sobrecarga el operador de producto "*="
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\param     x: objeto de tipo Real pasado como referencia constante
			\pre 	   Ninguna
			\post	   El coeficiente del monomio actual se ha multiplicado por el número real “x”
			\post	   El grado del monomio actual no ha sido midificado
			\note	   Se debe utilizar COTA_ERROR para controlar la precision de los numeros reales
			\sa        getCoeficiente(), getGrado(), setCoeficiente(coeficiente)
	*/

		Monomio & operator*=(double const &x);

	/*! 
			\brief     Operador de division: operador que modifica el monomio dividiendolo por otro monomio
			\attention Se sobrecarga el operador de producto "/="
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\param     m: objeto del tipo Monomio pasado como referencia constante
			\pre	   El grado del monomio "m" es igual o inferior al grado del monomio actual
			\pre	   El coeficiente del monomio "m" no es 0.0
			\post	   El coeficiente del monomio actual se ha dividido por el coeficiente del moonomio "m"
			\post	   El grado del monomio actual se ha decrementado con el grado del monomio "m"
			\note	   Se debe utilizar COTA_ERROR para controlar la precision de los numeros reales
			\sa        getCoeficiente(), getGrado(), setCoeficiente(coeficiente), setGrado(grado)
	*/

		Monomio & operator/=(Monomio const &m);

	/*! 
			\brief     Operador de division: operador que modifica el monomio dividiendolo por un numero real
			\attention Se sobrecarga el operador de producto "/="
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\param     x: objeto de tipo Real pasado como referencia constante
			\pre	   El numero real "x" no es 0.0
			\post	   El coeficiente del monomio actual se ha dividido por el numero real "x"
			\post	   El grado del monomio actual no ha sido modificado
			\note	   Se debe utilizar COTA_ERROR para controlar la precision de los numeros reales
			\sa        getCoeficiente(), getGrado(), setCoeficiente(coeficiente)
	*/

		Monomio & operator/=(double const &x);


	/////////////////////////////////////////////////////////////////////////////////////

	//! \name Funciones lectura y escritura de la clase Monomio

	/*! 
			\brief     Funcion que lee desde teclado los atributos del monomio
			\warning   Se requiere que la funcion getGrado tenga el modificador const
			\pre 	   Ninguna
			\post	   El grado del monomio es mayor o igual que 0
			\sa        getGrado(), setCoeficiente(coeficiente), setGrado(grado)
	*/

	void leerMonomio();

	/*! 
			\brief     Funcion que escribe por pantalla los atributos del monomio con el formato: \f$ coeficiente \hspace{1ex} X^{grado} \f$
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\note      Si el coeficiente es 1 entonces se escribira \f$ \hspace{1ex} X^{grado} \f$
			\note      Si el coeficiente es -1 entonces se escribirá \f$ \hspace{1ex} -X^{grado} \f$
			\note      Si el grado es 0 entonces se escribira solo el \f$ coeficiente \f$
			\note      Si el grado es 1 entonces se escribira X pero sin \f$ {grado} \f$
			\sa        getGrado(), getCoeficiente(), setCoeficiente(coeficiente), setGrado(grado)
	*/

	void escribirMonomio();


	///////////////////////////////////////////////////////////////////////

	//! \name Funciones auxiliares de la clase Monomio

	/*! 
			\brief     Funcion que calcula el valor de un monomio para un numero real "x": \f$ coeficiente \hspace{1ex} X^{grado} \f$
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\param     x: objeto de tipo real pasado como referencia constante
			\sa        getGrado(), getCoeficiente(), setCoeficiente(coeficiente), setGrado(grado)
	*/

	double calcularValor(double const &x);


	/*! 
			\brief     Funcion que calcula la derivada de un monomio
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\return	   Devuelve un nuevo objeto de tipo Monomio que sera el monomio con la derivada aplicada
			\sa        getGrado(), getCoeficiente(), setCoeficiente(coeficiente), setGrado(grado)
	*/

	ed::Monomio derivada();


	/*! 
			\brief     Funcion que calcula la integral de un monomio
			\warning   Se requiere que las funciones de acceso getCoeficiente y getGrado tengan el modificador const
			\return	   Devuelve un objeto de tipo Monomio que sera el monomio pero con la integral aplicada
			\sa        getGrado(), getCoeficiente(), setCoeficiente(coeficiente), setGrado(grado)
	*/

	ed::Monomio integral();



};  // Fin de la definición de la clase Monomio

}  //  Fin de namespace ed.

// _MONOMIO_HPP_
#endif
