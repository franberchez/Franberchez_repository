#include <iostream>

#include <string>

#include "Monomio.hpp"

int main(){
	ed::Monomio m0(1,0);
	ed::Monomio m1(1,1);
	ed::Monomio m2(1,2);
	ed::Monomio m3(-1,0);
	ed::Monomio m4(-1,1);
	ed::Monomio m5(-1,2);
	ed::Monomio m6(2,0);
	ed::Monomio m7(2,1);
	ed::Monomio m8(2,2);


	m0.escribirMonomio();
	std::cout << std::endl << std::endl;

	m1.escribirMonomio();
	std::cout << std::endl << std::endl;
	m2.escribirMonomio();
	std::cout << std::endl << std::endl;
		m3.escribirMonomio();
	std::cout << std::endl << std::endl;
		m4.escribirMonomio();
	std::cout << std::endl << std::endl;
		m5.escribirMonomio();
	std::cout << std::endl << std::endl;
		m6.escribirMonomio();
	std::cout << std::endl << std::endl;
		m7.escribirMonomio();
	std::cout << std::endl << std::endl;
		m8.escribirMonomio();
	std::cout << std::endl << std::endl;

	

}