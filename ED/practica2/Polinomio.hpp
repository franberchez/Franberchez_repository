/*!
   \file Polinomio.hpp
   \brief Definición de la clase Polinomio
*/

#ifndef _POLINOMIO_HPP_
#define _POLINOMIO_HPP_

// Control de asertos
#include <cassert>

// Vector de STL
#include <vector>

// Para usar la función abs
#include <cmath>

#include "PolinomioInterfaz.hpp"
#include "Monomio.hpp"
#include "operadoresExternosMonomios.hpp"


// Se incluye la clase Polinomio dentro del espacio de nombre de la asigantura: ed
namespace ed {

//!  Definición de la clase Polinomio que hereda de PolinomioInterfaz
class Polinomio: public ed::PolinomioInterfaz
{

  //! \name Atributos privados de la clase Polinomio
   private:

    std::vector<ed::Monomio> polinomio_;

   //! \name Funciones o métodos públicos de la clase Polinomio
   public:

	//! \name Constructores de la clase Polinomio

	/*!
			\brief 		Constructor para crear un polinomio a partir de monomios
			\attention 	Funcion sobrecargada
			\note 		Funcion inline
			\pre 		Ninguna
			\post 		El polinomio tiene que ser nulo
			\sa 		esNulo()
	*/

  inline Polinomio() // Es posible que haya que especificar una herencia como en poo
  {
  	ed::Monomio m; // el ed:. si no queremos no tenemos por que ponerlos, pero en cuestiones de formalidad queda mas correcto ponerlo
    polinomio_.push_back(m);

  	#ifndef NDEBUG
  		assert( esNulo() == true );
  	#endif
  }


  	/*!
			\brief 		Constructor copia para crear un polinomio a partir de un polinomio
			\attention 	Funcion sobrecargada
			\note 		Funcion inline
			\param		p: polinomio que contiene el grado y el coeficiente para crear otro polinomio
			\pre 		Ninguna
			\post 		El polinomio creado es igual al otro polinomio "p"
			\sa 		esIgual()
	*/

  inline Polinomio(const Polinomio &p){ // constructor copia
      this->polinomio_ = p.polinomio_;

      #ifndef NDEBUG
        assert( esIgual(p) == true );
      #endif
  }

  //! \name Observadores: funciones de consulta de la clase Polinomio

	/*!
			\brief 		Funcion que comprueba si el Polinomio es igual al monomio de coeficiente 0.0 y grado 0
			\warning 	Se utiliza el modificador const en la definicion de la funcion para poder definir el constructor
			\note 		Funcion inline
			\return 	Retorna verdadero en caso de de que sea nulo y en caso contrario retorna falso
			\pre 		Ninguna
			\sa 		getCoeficiente(), getGrado(), getNumeroMonomios()
	*/

  inline bool esNulo() const // EN CASO DE QUE NO FUNCIONE:  if( ( (polinomio_.size()==1)||(polinomio_.size()==0) )&&(polinomio_.front().getCoeficiente()==0.0)&&(polinomio_.front().getGrado()==0) )
  {
  	// Compruebo que si el tamaño es 0 o es 1 el polinomio puede ser nulo y para asegurarme compruebo que el monomio que lo forma sea nulo
    if( ( (this->getNumeroMonomios() ==1)||(this->getNumeroMonomios()==0) )&&(polinomio_.front().getCoeficiente()==0.0)&&(polinomio_.front().getGrado()==0) )
    {
      return true;
    }

    return false;
  }


	/*!
			\brief 		Funcion que obtiene el grado del polinomio
			\note 		Funcion inline
			\return 	Retorna el grado del polinomio
			\pre 		Los monomios ordenados de mayor a menor grado
			\sa 		getGrado()
	*/

  inline int getGrado() const // Lo que obtenemos con esta funcion es el grado del polinomio ordenado teniendo en cuenta que el monomio de mayor grado es el primero
  {
    #ifndef NDEBUG
      assert( esOrdenado() == true ); //creo que sera mejor esfecificar cunaod creemos el vector que ordenemos el vector
    #endif 

    int grado = this->polinomio_.front().getGrado();

    return grado;
  }


	/*!
			\brief 		Funcion que devuelve el numero de monomios del polinomio
			\warning 	Se utiliza el modificador const para definir la funcion esNulo()
			\note 		Funcion inline
			\return 	Retorna tamaño del polinomio
			\pre 		Los monomios ordenados de mayor a menor grado
	*/

  inline int getNumeroMonomios() const
  {
  	// Como lo que tengo es un vector de monomios lo que podemos hacer este devolver el tamaño tal cual de ese vector
  	return polinomio_.size();
  }

	/*!
			\brief 		Funcion que comprueba si existe el monomio de grado indicado
			\warning 	Se utiliza el modificador const
			\note 		Funcion inline
			\return 	Retorna verdadero en caso de que si exista el monomio del grado indicado y devolvera falso en caso contrario
			\param 		grado: es una variable de tipo entero que indica el grado del polinomio que buscamos
			\pre 		El polinomio debe existir
			\sa 		getNumeroMonomios(), getGrado()
	*/

  inline bool existeMonomio(int grado) const
  {
  	#ifndef NDEBUG
  		assert( esNulo() == false );
  	#endif

  	for (int i = 0; i<this->getNumeroMonomios(); i++)
  	{
  		if( polinomio_[i].getGrado() == grado )
  		{
  			return true;
  		}
  	}

  	return false;
  }


	/*!
			\brief 		Funcion que obtiene el monomio del grado indicado
			\warning 	Se utiliza el modificador const
			\note 		Funcion inline
			\return 	Retorna un monomio
			\param 		n: es una variable de tipo entero que indica el grado del polinomio que buscamos
			\pre 		El polinomio debe existir
			\sa 		esNulo(), getNumeroMonomios(), getGrado()
	*/

  inline Monomio getMonomio(int n) const // Que pasa si no esta el monomio?
  {
  	#ifndef NDEBUG
  		assert( esNulo() == false );
  	#endif

  	ed::Monomio m; 

  	for (int i = 0; i<this->getNumeroMonomios(); i++)
  	{
  		if( polinomio_[i].getGrado() == n )
  		{
  			m = this->polinomio_[i];
  		}
  	}

  	return m;

  }

	//! \name Funciones de modificación de la clase Polinomio


 	////////////////////////////////////////////////////////////////

   //! \name Operadores de la clase Polinomio

	/*! 
			\brief     Operador de asignacion: operador que copia un polinomio en el polinomio actual
			\attention Se sobrecarga el operador de asignación "="
			\warning   Se requiere que la funcion esIgual() tenga el modificador const
			\param     p: objeto de tipo Polinomio pasado como referencia constante
			\pre 	   El polinomio "p" debe ser diferente al polinomio actual
			\post	   El polinomio actual debe ser igual al polinomio "p"
			\sa        esIgual()
	*/

	Polinomio & operator=(Polinomio const &p);


	/*! 
			\brief     Operador de asignacion: operador que copia un monomio en el polinomio actual
			\attention Se sobrecarga el operador de asignación "="
			\warning   Se requiere que la funcion compruebaMonomio() y getNumeroMonomios() tengan el modificador const
			\param     m: objeto de tipo Monomio pasado como referencia constante
			\pre 	   Ninguna
			\post	   El polinomio actual debe tener un unico monomio que sera igual al monomio "m"
			\sa        compruebaMonomio(), getNumeroMonomios()
	*/

	Polinomio & operator=(Monomio const &m);


	/*! 
			\brief     Operador de asignacion: operador que copia un numero en el polinomio actual
			\attention Se sobrecarga el operador de asignación "="
			\warning   Se requiere que la funcion compruebaMonomio() y getNumeroMonomios() tengan el modificador const
			\param     x: objeto de tipo entero pasado como referencia constante
			\pre 	   Ninguna
			\post	   el polinomio debe ser igual al numero "x"
			\sa        compruebaMonomio(), getNumeroMonomios(), setCoeficiente(), setGrado()
	*/

	Polinomio & operator=(double const &x);

  	// Operadores aritméticos y asignación

	/*! 
			\brief     Operador de suma: operador de incremento y asignacion con otro polinomio
			\attention Se sobrecarga el operador de incremento "+="
			\warning   Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\param     p: objeto del tipo Polinomio pasado como referencia constante
			\pre	   Ninguna
			\sa        getNumeroMonomios(), getGrado(), getCoeficiente(), ordenaPolinomio()
	*/

	Polinomio & operator+=(Polinomio const &p);


	/*! 
			\brief     Operador de suma: operador de incremento y asignacion con un monomio
			\attention Se sobrecarga el operador de incremento "+="
			\warning   Se requiere que la funcion getNumeroMonomios() yenga el modificador const
			\param     m: objeto del tipo Mononomio pasado como referencia constante
			\pre	   Ninguna
			\sa        getNumeroMonomios(), getGrado(), getCoeficiente(), ordenaPolinomio()
	*/

	Polinomio & operator+=(Monomio const &m);

	/*! 
			\brief     Operador de suma: operador de incremento y asignacion con numero real
			\attention Se sobrecarga el operador de incremento "+="
			\warning   Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\param     x: objeto del tipo entero pasado como referencia constante
			\pre	   Ninguna
			\sa        getNumeroMonomios(), getGrado(), getCoeficiente(), setCoeficiente() ordenaPolinomio()
	*/


	Polinomio & operator+=(double const &x);

	/*! 
			\brief     Operador de diferencia: operador de decremento y asignacion con otro polinomio
			\attention Se sobrecarga el operador de incremento "-="
			\warning   Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\param     p: objeto del tipo Polinomio pasado como referencia constante
			\pre	   Ninguna
			\sa        getNumeroMonomios(), getGrado(), getCoeficiente(), setCoeficiente() ordenaPolinomio()
	*/


	Polinomio & operator-=(Polinomio const &p);

	/*! 
			\brief     Operador de diferencia: operador de decremento y asignacion con un monomio
			\attention Se sobrecarga el operador de incremento "-="
			\warning   Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\param     m: objeto del tipo Monomio pasado como referencia constante
			\pre	   Ninguna
			\sa        getNumeroMonomios(), getGrado(), getCoeficiente(), ordenaPolinomio()
	*/


	Polinomio & operator-=(Monomio const &m);

	/*! 
			\brief     Operador de diferencia: operador de decremento y asignacion con un numero real
			\attention Se sobrecarga el operador de incremento "-="
			\warning   Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\param     x: objeto del tipo entero pasado como referencia constante
			\pre	   Ninguna
			\sa        getNumeroMonomios(), getGrado(), getCoeficiente(), setCoeficiente(), ordenaPolinomio()
	*/


	Polinomio & operator-=(double const &x);


	/*! 
			\brief     Operador de producto: operador de multiplicacion y asignacion por otro polinomio
			\attention Se sobrecarga el operador de producto "*="
			\warning   Se requiere que las funciones getNumeroMonomios(), getVector(), ordenaPolinomio() y getGrado() tengan el modificador const
			\param     p: objeto de tipo Polinomio pasado como referencia constante
			\pre 	   Ninguna
			\sa        getNumeroMonomios(), getVector(), getGrado(), ordenaPolinomio()
	*/

	Polinomio & operator*=(Polinomio const &p);


	/*! 
			\brief     Operador de producto: operador de multiplicacion y asignacion por un monomio
			\attention Se sobrecarga el operador de producto "*="
			\warning   Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\param     m: objeto de tipo Monomio pasado como referencia constante
			\pre 	   Ninguna
			\sa        getNumeroMonomios(), getGrado(), ordenaPolinomio()
	*/
	
	Polinomio & operator*=(Monomio const &m);


	/*! 
			\brief     Operador de producto: operador de multiplicacion y asignacion por un numero real
			\attention Se sobrecarga el operador de producto "*="
			\warning   Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\param     x: objeto de tipo Real pasado como referencia constante
			\pre 	   Ninguna
			\sa        getGrado(), getNumeroMonomios(), ordenaPolinomio()
	*/

	Polinomio & operator*=(double const &x);


	/*! 
			\brief     Operador de division: operador de division y asignacion por otro polinomio
			\attention Se sobrecarga el operador de division "/="
			\warning   Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\param     p: objeto de tipo Polinomio pasado como referencia constante
			\pre 	   El grado del polinomio debe ser menor o igual que el grado del polinomio actual
			\sa        getGrado(), getNumeroMonomios(), ordenaPolinomio()
	*/

	Polinomio & operator/=(Polinomio const &p);


	/*! 
			\brief     Operador de division: operador de division y asignacion por un monomio
			\attention Se sobrecarga el operador de division "/="
			\warning   Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\param     m: objeto de tipo Monomio pasado como referencia constante
			\pre 	   El grado del monomio debe ser menor o igual que el grado del polinomio actual
			\sa        getGrado(), getNumeroMonomios(), ordenaPolinomio()
	*/

	Polinomio & operator/=(Monomio const &m);


	/*! 
			\brief     Operador de division: operador de division y asignacion por un numero real
			\attention Se sobrecarga el operador de division "/="
			\warning   Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\param     x: objeto de tipo Real pasado como referencia constante
			\pre 	   Ninguna	
			\sa        getGrado(), getNumeroMonomios(), ordenaPolinomio()
	*/

	Polinomio & operator/=(double const &x);


  /////////////////////////////////////////////////////////////////////////////////////

	//! \name Funciones lectura y escritura de la clase Polinomio

	/*! 
			\brief     Lee desde el teclado un polinomio
			\pre 	   Ninguna	
			\sa        leerMonomio(), ordenaPolinomio()
	*/

	void leerPolinomio();


	/*! 
			\brief     Funcion que escribe por pantalla el polinomio donde cada monomio tiene el formato: \f$ coeficiente \hspace{1ex} X^{grado} \f$
			\warning   Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\note      Si el coeficiente es 1 entonces se escribira \f$ \hspace{1ex} X^{grado} \f$
			\note      Si el coeficiente es -1 entonces se escribirá \f$ \hspace{1ex} -X^{grado} \f$
			\note      Si el grado es 0 entonces se escribira solo el \f$ coeficiente \f$
			\note      Si el grado es 1 entonces se escribira X pero sin \f$ {grado} \f$
			\sa        getNumeroMonomios(), getCoeficiente(), escribeMonomio()
	*/

	void escribirPolinomio();


	///////////////////////////////////////////////////////////////////////

	//! \name Funciones auxiliares de la clase Polinomio

	/*!
			\brief 		Funcion comprueba si nuestro polinomio es igual a un polinomio dado
			\warning 	Se utiliza el modificador const en la definicion de la funcion para poder definir el constructor de copia y se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\return 	Retorna verdadero en caso de que ambos polinomios sean iguales y falso en caso contrario
			\param 		p: polinomio que vamos a comparar con nuestro polinomio
			\pre 		Ninguna
			\sa 		getCoeficiente(), getGrado(), getNumeroMonomios()
	*/

 	 bool esIgual(Polinomio const &p);


 	/*!
			\brief 		Funcion comprueba si nuestro polinomio esta ordenado
			\warning 	Se utiliza el modificador const en la definicion de la funcion para poder definir la funcion getGrado()
			\return 	Retorna verdadero en caso de que el polinomio este ordenado
			\pre 		Ninguna
			\sa 		getGrado()
	*/

 	 bool esOrdenado() const;


	/*!
			\brief 		Funcion que comprueba si un monomio es igual al monomio de un plinomio
			\warning 	Se utiliza el modificador const en la definicion de la funcion para poder definir el operador asignacion
			\return 	Retorna verdadero en caso de que los monomios sean iguales y falso en caso contrario
			\param 		m: monomio que vamos a comparar con el monomio de nuestro polinomio
			\pre 		Ninguna
			\sa 		getCoeficiente(), getGrado()
	*/

  	bool compruebaMonomio(Monomio const &m);


	/*!
			\brief 		Funcion que me devuelve el vector de monomios de un polinomio
			\pre 		Ninguna
	*/

  	inline std::vector<ed::Monomio> getVector() const 
  	{
  		return this->polinomio_;
  	}


	/*!
			\brief 		Funcion que utilizaremos para indicar que vamos a ordenar el vetor de mayor a menor
			\return 	Retorna el orden
			\pre 		Ninguna

	*/

  	bool friend orden(ed::Monomio const &m1, ed::Monomio const &m2);


	/*!
			\brief 		Funcion en el que vamos a utilizar la funcion sort del vector de la stl para ordenar el vector de monomios
			\warning 	Se requiere que la funcion getNumeroMonomios() tenga el modifiacdor const
			\pre 		Ninguna
			\sa 		getCoeficiente(), getNumeroMonomios()
	*/

  	void ordenaPolinomio();


	/*!
			\brief 		Funcion que calcula el valor del polinomio para un numero real "x"
			\warning 	Se requiere que la funcion getNumeroMonomios() tenga el modificador const
			\return 	Retorna el valor del polinomio para ese valor "x"
			\param 		x: objeto de tipo entero pasado como referencia constante
			\pre 		Ninguna
			\sa 		getNumeroMonomios(), calculaValor(x)
	*/

  	double calcularValor(int const &x);


	/*!
			\brief 		Funcion que inserta un monomio en un polinomio
			\param 		m: objeto de tipo Monomio pasado como referencia constante
			\pre 		Ninguna
			\sa 		ordenaPolinomio()
	*/

  	void insertaMonomio(ed::Monomio m);

	/*!
			\brief 		Funcion que le asigna a un polinomio un vector de monomios
			\param 		v: objeto de tipo vector de la stl pasado como referencia constante
			\pre 		Ninguna
			\sa 		ordenaPolinomio()
	*/

  	void asignaPolinomio(std::vector<ed::Monomio> v_aux);

}; // Fin de la definición de la clase Polinomio




} // \brief Fin de namespace ed.

//  _POLINOMIO_HPP_
#endif