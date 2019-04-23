#!/bin/bash

# Esta funcion lo que hace es recorrer un directorio es ir escribriendo en FicheroHtml los ficheros que hay dentro de un directorio

function Directorio()
{
	for x in $(find $1 -maxdepth 1)
	do

		if [ ! -d $x ]; # Quiere decir que si no es un directorio es un fichero de esa carpeta
		then
			echo -n "<ul>" >> $FicheroHtml
			echo -n "<li>$x</li>" >> $FicheroHtml
			echo "</ul>" >> $FicheroHtml
		
		else
			if [ "$1" != "$x" ];
			then
				echo -n "<ul>" >> $FicheroHtml
				echo "<li><strong>$x</strong></li>" >> $FicheroHtml
				Directorio "$x"
				echo "</ul>" >> $FicheroHtml
			fi
		fi

	done
}


if [ $# -eq 0 ];
then
	echo "No se ha pasado el nombre del directorio para crear el archivo .html"
	exit 1
fi

if [ ! -d $1 ];
then
	echo "El directorio /$1 no existe"
	exit 1
fi

echo "Generando el listado de la carpeta $PWD/$1 sobre el fichero $1.html..."

Fichero=$(readlink -f $1)
FicheroHtml=$(basename $1).html

cat > $FicheroHtml << EOF
<html>
<head>
<title>Listado del directorio $1</title>
</head>
<body>
<style type="text/css">
	body { font-family: sans-serif;}
</style>
<h1>Listado del directorio $1</h1>
EOF

Directorio "$Fichero"

cat >> $FicheroHtml << EOF
</body>
</html>
EOF

echo "¡Terminado!"