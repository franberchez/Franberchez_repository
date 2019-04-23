/*!
 \mainpage Implementación de un monomio
 \brief		\f$ coeficiente X^{grado}\f$
 \author   
 \date     
 \version  1.0
*/

/*!

	\file principal.cpp
	\brief Programa principal de la practica 1 de ED: monomios
*/

#include <iostream>

#include "funcionesAuxiliares.hpp"

#include "macros.hpp"

/*! 
	\brief   Función principal de la práctica 1
	\return  int
*/
int main()
{
	int opcion;

	do{

		// Se elige la opción del menún
		opcion = ed::menu();		

		std::cout << CLEAR_SCREEN;
		PLACE(3,1);

		// Se ejecuta la opción del menú elegida
		switch(opcion)
		{
			case 0: 
				PLACE(3,1);
				std::cout << BIYELLOW;
				std::cout << "[0] Fin del programa" << std::endl << std::endl;
				std::cout << RESET;
				break;

			case 1: 
			   	std::cout << BIBLUE;
				std::cout << "[1] Test de la clase Monomio" << std::endl;
				std::cout << RESET;

				ed::testMonomio();
				break;

			case 2: 
			   	std::cout << BIBLUE;
				std::cout << "[2] Operadores externos de la clase Monomio " << std::endl;
				std::cout << RESET;

				ed::operadoresExternosMonomios();
				break;

			case 3:// No lo detecta
				std::cout << BIBLUE;
				std::cout << "[3] Potencia de un monomio" << std::endl;
				std::cout << RESET;

				ed::comprueba_potencia();
				break;

			case 4:
				std::cout << BIBLUE;
				std::cout << "[4] Derivada de un monomio" << std::endl;
				std::cout << RESET;

				ed::comprueba_derivada();
				break;

			case 5:
				std::cout << BIBLUE;
				std::cout << "[5] Integral de un monomio" << std::endl;
				std::cout << RESET;

				ed::comprueba_integral();
				break;


			default:
				std::cout << BIRED;
				std::cout << "Opción incorrecta ";
				std::cout << RESET;
				std::cout << "--> ";
			  	std::cout << ONIRED;
				std::cout << opcion << std::endl;
				std::cout << RESET;
     }
  
    if (opcion !=0)
    {
		std::cout << "Para mostrar el ";
		std::cout << BIGREEN ;
		std::cout << "menú, "; 
		std::cout << RESET;
		std::cout << "pulse ";
		std::cout << INVERSE ;
		std::cout << "ENTER";
		std::cout << RESET;

		// Pausa
		std::cin.ignore();

		std::cout << CLEAR_SCREEN;
    }
	  }while(opcion!=0);

	return 0;
}


