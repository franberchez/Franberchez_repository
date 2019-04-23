#!/bin/bash

if [ $# -eq 0 ];
then
	echo "No se introdujo el nombre del directorio, ni ningun otro argumento como el nuemro de bytes"
	exit 1
fi

if [ $# -ge 3 ];
then
	echo "Se ha excedido el numero de argumento para que este script funcione"
	exit 1
fi

if [ $# -eq 1 ]; # Querra decir que solo hemos introducido el nombre del directorio
then # Si no se especifica el numero de bytes el script debe mostrar todos los ficheros del directorio
	tam=0
else # En caso de que si se haya pasado el numero de bytes guardo en mi variable tam el numero de bytes
	tam=$2
fi

# Mi script buscara en el directorio que hemos pasado como argumento todos aquellos ficheros que tengan un tamaño total
# en bytes sea mayor o igual que el pasado como argumento


echo "Nombre LongitudUsuario FechaModificacion FechaAcceso Tamano Bloques Permisos Ejecutable"

# Los nombres de lo que tengo puesto en el echo van separados por ";"

for x in $(find $1 -type f)
do
	if [ $(cat $x | wc -c) -ge $tam ]; # tam sera el tamaño que hemos estipulado con anterioridad
	then

		# Asi comprobamos si el fichero es un ejecutable
		if [ -x $x ];
		then
			ejecutable=1

		else
			ejecutable=0
		fi

		# vamos a utilizar el comando basename para vel el nombre de un archivo sin su carpeta
		# vamos a utilizar el comando stat y para ello vamos a hacer uso del man para poder ver que extensiones tendremos que poner para que nos muestre lo que deseamos
		echo "$(basename $x);$(stat -c "%U" $x | wc -m);$(stat -c "%y" $x);$(stat -c "%X" $x);$(stat -c "%s" $x);$(stat -c "b" $x);$(stat -c "%A" $x);$ejecutable"
	fi

done | sort -n -k5 -t ";"
