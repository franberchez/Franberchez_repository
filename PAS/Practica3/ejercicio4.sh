#!/bin/bash

# No tengo muy claro porque no funciona cuando lo meto dentro de la carpeta ejemploCarpeta ya que me cuenta 4 aunque le tengo puesto que solo me cuente los archivos
# Sin embargo si lo tengo guardado dentro de la carpeta practica 3 y hago ../ejercicio4.sh cuando en terminal estoy dentro de la carpeta ejemploCarpeta si que me funciona

cont=0

# No tengo ni puta idea de porque no funciona y me cuenta 4

for x in $(ls -l)
do
	if [ -f $x ];
	then
		let "cont=$cont+1"
	fi
done 

echo "El directorio actual tiene $cont archivos"

# Mostrar una lista ordenada de los usuarios logueados elminando los repetidos o mas bien sin mostrar repeticiones de los mismos

# Vamos a usar el comando who para saber los usarios que hay conectados

# uniq sirve para filtrar duplicados

who | awk '{print $1}' | sort | uniq

# Imprimos el numero de veces que aparece un caracter que se le pide al usuario
# En la carpeta actual o supcarpeta

caracter=0
contCaracter=0

echo -n "¿Que caracter quieres contar? "
read -t5 caracter # Lo puedo poner tambien como read -t 5 caracter

if [ -z $caracter ];
then
	caracter=a
fi

for x in $(ls -R)
do
	if [ $(basename $x | grep $caracter) ];
	then
		let "contCaracter=$contCaracter+1"
	fi

done

echo "El caracter $caracter aparace $contCaracter veces en nombres de ficheros o carpetas contenidos en la carpeta actual"