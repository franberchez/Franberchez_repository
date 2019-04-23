#!/bin/bash

# Lo primero que voy a realizar es un control de errores, en cuanto a que le tengo que pasar un argumento a este script

if [ $# -ne 1 ];
then
	echo "No se introdujo el directorio en el cual quiero buscar"
	exit 1
fi

cant1=$(find $1 -name "*.c" | wc -l) # Me cuenta el numero de archivos .c
cant2=$(find $1 -name "*.h" | wc -l) # Me cuenta el numero de archivos .h

echo "Tenemos $cant1 ficheros con extension .c y $cant2 ficheros con extension .h"


for x in $(find $1 -type f -name "*.c" -o -type f -name "*.h")
do
	echo "El fichero $x tiene $(cat $x | wc -l) lineas y $(cat $x | wc -m) caracteres"
done | sort -nr -k8 

# Lo que he hecho ha sido ordearlos en orden numerico inverso segun el numero de caracteres que se encuentran en la octava columna de ahi el 8