/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 1
  \author 
  \date  
*/


#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

namespace ed
{
	/*! 
		\brief   		Muestra el menú del programa principal 
		\return  		Devuelve el número de opción elegido
	*/
	int menu();


	/*!
		\brief			Relaliza un una prueba de los ficheros monomio.cpp y monomio.hpp
		\return 		Vuelve al menu una vez ha terminado la prueba de monomio.cpp y monomio.hpp
	*/

	void testMonomio();


	/*!
		\brief			Realiza una prueba de los operadores externos del programa que se encuentran
						\n en los ficheros operadoresExternosMonomios.cpp y operadoresExternosMonomios.hpp
		\return 		Vuelve al menu una vez termina la prueba de los operadores externos
	*/

	void operadoresExternosMonomios();


	/*!
		\brief 		Realiza un prueba del operador que utilizaremos para realizar la potencia
					\n que se encuentra en los ficheros operadoresExternosMonomios.cpp y operadoresExternosMonomios.hpp
		\return		Vuelve al menu una vez termina de hacer la prueba del operador potencia 
	*/

	void comprueba_potencia();


	/*!
		\brief		Realiza una prueba de la función especifica que realiza la derivada de un monomio
					\n que se encuentra en los ficheros monomio.cpp y monomio.hpp
		\return		Vuelve al menu una vez finaliza la prueba de la derivada de la funcion
	*/

	void comprueba_derivada();


	/*!
		\brief		Realiza una prueba de la funcion especifica que realiza la integral de un monomio
					\n que se encuentra en los ficheros monomio.cpp y monomio.hpp
		\return		Vuelve al menu una vez finaliza la prueba de la integral de la funcion
	*/

	void comprueba_integral();
} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif

