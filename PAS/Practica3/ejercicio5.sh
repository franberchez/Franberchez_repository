#!/bin/bash

# Hacemos la comprobacion de que le hayamos pasado por lo menos 1 argumentos en caso de que no salimos del script
if [ $# -eq 0 ];
then
	echo "La ejecucion del programa es $0 y el o los ficheros a los que queremos hacerle una copia de seguridad"
	exit 1
fi

#Aqui comprobamos que los ficheros que tenemos dentro de la carpeta /Copia algunos de ellos no superes los 200 seg de antiguedad, en caso de superarlos lo que hacemos es borrarlos
if [ -d $PWD/Copia ]; # En caso de que exista borrar los ficcheros que superen los 200 seg de antiguedad
then
	for x in $(find $PWD/Copia -type f)
	do
		date=$(date +%s) # Segundos desde el 1 de enero de 1970
		fecha=$(stat -c %X $x) # Me devuelve la fecha de creacion del archivo

		# %W hora de nacimiento del archivo, segundos desde la época; 0 si se desconoce ///// Este puede sernos util probarlo una vez funcione todo para ver que tal va

		let "diferencia=$date-$fecha"

		if [ $diferencia -ge 200 ];
		then
			rm $x
			echo "Se ha borrado $x ya que $diferencia excede los 200 segundos"
		fi
	done
fi


#Recorremos los argumentos
cont=0

for x in $@
do
	if [ -e $x ];
	then
		fecha="$(date +%s)"
		array[$cont]=$x # En caso de fallo $x iria entre comillas
		let "cont=$cont+1"
	fi

done

# Me quedaria comprimirlos

echo "Comprimiendo archivos..."
tar -czf copia-$USER-$fecha.tar.gz ${array[*]}

# En caso de no existir la carpeta la creo
if [ ! -d $PWD/Copia ]; # Para crear la carpeta en caso de que no exista
then
	mkdir Copia
fi


# Muevo los archivos a la carpeta /Copia
echo "Moviendo archivos a la carpeta /Copia..."
mv copia-$USER-$fecha.tar.gz $PWD/Copia/ # Cojo lo que voy a mover primero y luego pongo su destino
