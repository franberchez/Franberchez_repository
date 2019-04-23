/*!
   \file PolinomioInterfaz.hpp
   \brief Definición de la interfaz de la clase Polinomio
*/

#ifndef _POLINOMIOINTERFAZ_HPP_
#define _POLINOMIOINTERFAZ_HPP_

#include "Monomio.hpp"

// Se incluye la clase PolinomioInterfaz dentro del espacio de nombre de la asigantura: ed
namespace ed {

//!  Definición de la clase PolinomioInterfaz
class PolinomioInterfaz
{

   //! \name Funciones o métodos públicos de la clase
   public:

	//! \name Observadores: funciones de consulta

  /*!
      \brief    Funcion que comprueba si el Polinomio es igual al monomio de coeficiente 0.0 y grado 0
      \warning  Se utiliza el modificador const en la definicion de la funcion para poder definir el constructor
      \note     Funcion inline
      \return   Retorna verdadero en caso de de que sea nulo y en caso contrario retorna falso
      \pre    Ninguna
      \sa     getCoeficiente(), getGrado(), getNumeroMonomios()
  */

	virtual bool esNulo() const = 0;

  /*!
      \brief    Funcion que obtiene el grado del polinomio
      \note     Funcion inline
      \return   Retorna el grado del polinomio
      \pre    Los monomios ordenados de mayor a menor grado
      \sa     getGrado()
  */

	virtual int getGrado()const = 0;

  /*!
      \brief    Funcion que devuelve el numero de monomios del polinomio
      \warning  Se utiliza el modificador const para definir la funcion esNulo()
      \note     Funcion inline
      \return   Retorna tamaño del polinomio
      \pre    Los monomios ordenados de mayor a menor grado
  */

	virtual int getNumeroMonomios()const = 0;


  /*!
      \brief    Funcion que comprueba si existe el monomio de grado indicado
      \warning  Se utiliza el modificador const
      \note     Funcion inline
      \return   Retorna verdadero en caso de que si exista el monomio del grado indicado y devolvera falso en caso contrario
      \param    n: es una variable de tipo entero que indica el grado del polinomio que buscamos
      \pre    El polinomio debe existir
      \sa     getNumeroMonomios(), getGrado()
  */

	virtual bool existeMonomio(int n)const = 0;


  // COMPLETAR LOS COMENTARIOS DE DOXYGEN
  //Descomentar
	//virtual ed::Monomio & getMonomio(int n) = 0;



}; // Fin de la definición de la clase PolinomioInterfaz


} // \brief Fin de namespace ed.

//  _POLINOMIOINTERFAZ_HPP_
#endif
