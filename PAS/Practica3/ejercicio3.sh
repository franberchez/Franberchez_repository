#!/bin/bash

if [ $# -eq 0 ];
then
	echo "No se ha introducido el nombre del directorio"
	exit 1
fi

if [ $# -ge 3 ];
then
	echo "Se ha excedido el numero de argumentos del script"
	exit 1
fi

if [ $# -eq 1 ]; # En caso de que solo reciba el directorio
then
	umbral1=10000
	umbral2=100000
fi

if [ $# -eq 2 ]; # En el caso de que solo reciba el directorio y el umbral1
then
	umbral1=$2
	umbral2=100000
fi

if [ $# -eq 3 ]; # En el caso de que reciba los 3 argumentos, direcotorio, umbral1, umbral2
then
	umbral1=$2
	umbral2=$3
fi

# Para comprobar si en la ruta hay esas carpetas utilizare la variable de entorno $PWD
# El -d nos servirá para comprobar si existe un determinado directorio
# rmdir lo usaremos para borrar los directorios, pero esto da problemas al no estar vacios
# Para borrar los diractorios utilizo rm, con -d para borrar el directorio y -r para lo que haya dentro

if [ -d $PWD/pequenos ] && [ -d $PWD/medianos ] && [ -d $PWD/grandes ];
then
	rm -d -r pequenos
	rm -d -r medianos
	rm -d -r grandes
fi

echo "Creando las carpetas pequenos, medianos y grandes..."
mkdir pequenos
mkdir medianos
mkdir grandes


echo "Copiando archivos..."

for x in $(find $1 -type f)
do
	if [ $(stat -c "%s" $x) -lt $umbral1 ];
	then
		cp $x $PWD/pequenos
	fi

	if [ $(stat -c "%s" $x) -ge $umbral1 ] && [ $(stat -c "%s" $x) -le $umbral2 ];
	then
		cp $x $PWD/medianos
	fi

	if [ $(stat -c "%s" $x) -gt $umbral2 ];
	then
		cp $x $PWD/grandes
	fi

done
