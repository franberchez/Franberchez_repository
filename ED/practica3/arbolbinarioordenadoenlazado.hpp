#ifndef __ARBOLBINARIOORDENADO_HPP__
#define __ARBOLBINARIOORDENADOENLAZADO_HPP__

#include <iostream>
#include <cassert>
#include "arbolbinarioordenado.hpp"
#include "operadornodo.hpp"

using namespace std;
/*!
\brief Espacio de nombres para la asignatura Estructura de datos.
*/
namespace ed
{
	/*!\brief Interfaz para definir un ArbolBinario ordenado.

	Define una interfaz para definir un ArbolBinarioOrdenado.

	\arg G define el campo de información a contener en el arbol.
	\pre G debe tener definidos los operadores < y ==.
	*/
	template<class G>
	class ArbolBinarioOrdenadoEnlazado:public ArbolBinarioOrdenado<G>
	{
	private:

		/*!\brief Define un nodo del arbol binario.*/
		class NodoArbolBinario
		{
		private:
			G _info;  //Valor informativo almacenado en el nodo
			NodoArbolBinario * _izquierdo;  //Puntero al hijo izquierdo
			NodoArbolBinario * _derecho;  //Puntero al hijo derecho

		public:
			// Lo que hacemos es crear un nuevo nodo con la información de árbol, por lo tanto su hijo derecho como el izquierdo son nulos
			NodoArbolBinario (const G &info)
			{
				this->_info = info;
				this->_izquierdo = NULL;
				this->_derecho = NULL;

				// Comprobamos que el nodo que acabamos de crear no tenga hijos
				#ifndef NDEGUG
					assert( (this->getDerecho() == NULL) and (this->getIzquierdo() == NULL) );
				#endif
			}

			NodoArbolBinario (const NodoArbolBinario &n)
			{
				this->_info = n.getInfo();
				this->_izquierdo = n.getIzquierdo();
				this->_derecho = n.getDerecho();

				//Comrobamos que el nodo creado sea igual al nodo n
				#ifndef NDEGUG
					assert( *this == n );
				#endif

				/*

				De esta forma lo puedo hacer una vez tengo el operador =

				*this = n;

				#ifndef NDEBUG
					assert( *this == n );
				#endif

				*/
			}

			/*!\brief Observadores.*/
			const G & getInfo() const
			{
				return this->_info;
			}

			NodoArbolBinario *getIzquierdo() const
			{
				return this->_izquierdo;
			}

			NodoArbolBinario *getDerecho() const
			{
				return this->_derecho;
			}

			bool esHoja() const
			{
				bool hoja = false;

				// Comprobamos que tanto su hijo izquierdo como el derecho sean nulos
				if ( (getIzquierdo() == NULL)&&(getDerecho() == NULL) )
				{
					hoja = true;
				}
				
				return hoja;
			}

			// Muestro, izquierda, derecha
			void recorridoPreOrden (OperadorNodo<G> &operador) const
			{
				operador.aplicar(getInfo());

				if(this->getIzquierdo() != NULL)
				{
					this->getIzquierdo()->recorridoPreOrden(operador);
				}

				if(this->getDerecho() != NULL)
				{
					this->getDerecho()->recorridoPreOrden(operador);
				}
			}

			// Izquierda, derecha, muestro
			void recorridoPostOrden (OperadorNodo<G> &operador) const
			{
				if(this->getIzquierdo() != NULL)
				{
					this->getIzquierdo()->recorridoPostOrden(operador);
				}

				if(this->getDerecho() != NULL)
				{
					this->getDerecho()->recorridoPostOrden(operador);
				}
				
				operador.aplicar(getInfo());
			}

			// Izquierda, muestro, derecha
			void recorridoInOrden (OperadorNodo<G> &operador) const
			{
				if(this->getIzquierdo() != NULL)
				{
					this->getIzquierdo()->recorridoInOrden(operador);
				}
				
				operador.aplicar(getInfo());
					
				if(this->getDerecho() != NULL)
				{
					this->getDerecho()->recorridoInOrden(operador);
				}
			}

			/*!\brief Modificadores. */
			void setInfo(const G &info)
			{
				this->_info = info;
			}

			void setIzquierdo(NodoArbolBinario *n)
			{
				this->_izquierdo = n;
			}

			void setDerecho(NodoArbolBinario *n)
			{
				this->_derecho = n;
			}

			NodoArbolBinario & operator=(const NodoArbolBinario &n)
			{
				#ifndef NDEBUG
					assert( n != *this);
				#endif

				setInfo(n.getInfo());
				setIzquierdo(n.getIzquierdo());
				setDerecho(n.getDerecho());

				#ifndef NDEBUG
					assert(*this == n);
				#endif
			}

		}; //Fin clase NodoArbolBinario

		//Implementación de la raíz
		NodoArbolBinario * _raiz; /*!<La raiz del árbol*/
		NodoArbolBinario * _actual; /*!<Cursor al nodo actual*/ // Current
		NodoArbolBinario * _padre; /*!<Cursor al nodo actual*/ // Prev

	public:

		ArbolBinarioOrdenadoEnlazado ()
		{
			this->_raiz = NULL;
			this->_actual = NULL;
			this->_padre = NULL;

			#ifndef NDEBUG
				assert(this->estaVacio());
			#endif
		}

		ArbolBinarioOrdenadoEnlazado (const ArbolBinarioOrdenadoEnlazado<G>& a)
		{
			this->_raiz = a._raiz;
			this->_actual = a._actual;
			this->_padre = a._padre;

			// *this = a; AUNQUE ESTE NO LO TENGO MUY CLARO ASI QUE PROBARLO

			#ifndef NDEBUG
				assert(*this == a);
			#endif
		}

		~ArbolBinarioOrdenadoEnlazado ()
		{
			if (not estaVacio())
			borrarArbol();
			cout << "Destructor Usado \n";
		}

		ArbolBinarioOrdenadoEnlazado &operator=(const ArbolBinarioOrdenadoEnlazado& a) // DONDE LECHES ESTA EN EL DOCUMENTO
		{
			// TODO
		}

		/*!\brief Observadores. */
		NodoArbolBinario *getRaiz() const{
			return this->_raiz;
		}

		NodoArbolBinario *getActual() const{
			return this->_actual;
		}

		NodoArbolBinario *getPadre() const{
			return this->_padre;
		}

		/*!\brief Modificadores. */
		void setRaiz(NodoArbolBinario *raiz){
			this->_raiz = raiz;
		}

		void setActual(NodoArbolBinario *actual){
			this->_actual = actual;
		}

		void setPadre(NodoArbolBinario *padre){
			this->_padre = padre;
		}	

		bool insertar(const G &x) // TENGO QUE REVISAR LAS PRECONDICIONES Y LAS POSTCONDICIONES
		{
			NodoArbolBinario *aux = NULL;
			NodoArbolBinario *auxActual;
			auxActual = _actual;
			aux->setInfo(x);

			if (this->estaVacio())
			{
				_raiz = aux;
				_actual = aux;
				return true;
			}  

			else
			{
				setActual(getRaiz());
				while(true)
				{
					if(getActual()->getInfo()>x) // En el caso de que sea mayor
					{
						if(getActual()->getIzquierdo()!=NULL)
						{
							setActual(getActual()->getIzquierdo());
						}

						else
						{
							getActual()->setIzquierdo(aux);
							setActual(auxActual);
							return true;
						}
					}

					else // Menor o igual
					{
						if(getActual()->getInfo()<x) // En el caso de que sea menor
						{				
							if(getActual()->getDerecho()!=NULL)
							{
								setActual(getActual()->getDerecho());
							}

							else // En el caso de que sea igual
							{
								getActual()->setDerecho(aux);
								setActual(auxActual);
								return true;
							}
						}

						else
						{
							setActual(auxActual);
							return false;
						}
					}
				}
			}


			return false;
		}

		void borrarArbol()
		{
			// TODO
		}

		bool borrar()
		{
			// TODO
			return false;
		}

		void recorridoPreOrden (OperadorNodo<G> &operador) const
		{
			// Lo que hacemos es aplicar el recorrido PreOrden que ya tenemos para un nodo empezando por la raiz
			this->_raiz->recorridoPreOrden(operador);
		}

		void recorridoPostOrden (OperadorNodo<G> &operador) const
		{
			// Lo que hacemos es aplicar el recorrido PostOrden que ya tenemos para un nodo empezando por la raiz
			this->_raiz->recorridoPostOrden(operador);
		}

		void recorridoInOrden (OperadorNodo<G> &operador) const
		{
			// Lo que hacemos es aplicar el recorrido InOrden que ya tenemos para un nodo empezando por la raiz
			this->_raiz->recorridoInOrden(operador);
		}

		bool buscar(const G& x) // TENGO QUE REVISAR LAS PRECONDICIONES Y LAS POSTCONDICIONES
		// Dice que como post que los punteros se tienen que quedar dinde correspondan en caso de no encontrarlos
		// Una funcion es utilizar el set para esto aunque parece que da fallo
		// La opcion 2 es que quitemos el constante
		{
			//bool found = false;
			NodoArbolBinario *auxPadre;
			NodoArbolBinario *auxActual;
			auxPadre = _padre;
			auxActual = _actual;
			setActual(getRaiz());
			setPadre(getRaiz());

			if(estaVacio())
			{
				return false;
			}

			while (true) //found == false
			{
				if(getActual()->getInfo()>x) // En en el caso de que se mayor
				{
					if(getActual()->getIzquierdo()!=NULL)
					{
						setPadre(getActual());
						setActual(getActual()->getIzquierdo());
					}

					else
					{
						setActual(auxActual);
						setPadre(auxPadre);
						return false;
					}				
				}

				else // Menor o igual
				{
					if(getActual()->getInfo()<x) // En el caso de que sea menor
					{
						if(getActual()->getDerecho()!=NULL)
						{
							setPadre(getActual());
							setActual(getActual()->getDerecho());
						}

						else // En el caso de que sea igual
						{
							setActual(auxActual);
							setPadre(auxPadre);
							return false;
						}
					}

					else return true;
				}
			}

			return false;
		}

		bool estaVacio() const
		{
			bool vacio = false;

			// Con tan solo tener la raiz a NULL ya se que esta vacio
			if(this->_raiz == NULL)
			{
				vacio = true;
			}

			return vacio;
		}

		G raiz() const
		{
			#ifndef NDEBUG
				assert(not estaVacio());
			#endif

			return this->_raiz;
		}

		bool existeActual() const
		{
			#ifndef NDEBUG
				assert(not estaVacio());
			#endif

			if(this->getActual() != NULL)
			{
				return true;
			}

			return false;
		}

		G actual() const
		{
			#ifndef NDEBUG
				assert(this->getActual() != NULL);
			#endif

			return this->getActual()->getInfo();
		}

		/*!@}*/
	};

} //namespace ed

#endif //__ARBOLORDENADO_HPP__
