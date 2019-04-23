#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>

void imprimir_uso()
{
	printf("\nUso del programa: ejercicio1 [opciones]\n");
	printf("Opciones:\n");
	printf("-u, --username\t Especifica el nombre de un usuario del sistema\n");
	printf("-i, --useruid\t Especifica el indentificador de un usuario del sistema\n");
	printf("-g, --groupname\t Especifica el nombre del grupo del sistema\n");
	printf("-d, --groupuid\t Especifica el indentificador de un grupo del sistema\n");
	printf("-s, --allgroups\t Se muestran todos los grupos del sistema\n");
	printf("-a, --allinfo\t Especifica el nombre de un usuario del sistema\n");
	printf("-b, --bactive\t Busca e imprime la informacion del grupo del usuario actual\n");
	printf("-h, --help\t e muestra el panel de ayuda\n");
}

int main(int argc, char **argv)
{
	int c;

	/* Estas variables son para referirnos al nombre de usuario y al uid en con las funciones pw */
	char *lgn;
	int uid;

	/* Estas variables son para referrir al nombre de un grupo y a su uid con las funciones gr */
	char *nombre_grupo;
	int uid_grupo;

	/* Estas son las estructuras de usuario y de grupo */
	struct passwd *pw;
	struct group *gr;

	/* Estas variables son para almacenar el resultado de procesar la línea de comandos */
	int uflag = 0;
	int iflag = 0;
	int gflag = 0;
	int dflag = 0;
	int sflag = 0;
	int aflag = 0;
	int bflag = 0;
	int hflag = 0;

	/* Estas son las variables para trabajar con el fichero de texto */
	FILE* f;
	char grupo[1024];
	char *token;

	// Las variables esternas que va gestionando son:
    //   - optind: Indice del siguiente elemento a procesar del vector argv[]
    //   - optarg: recoge el valor del argumento obligario de una opcion.
    //   - optopt: recoge el valor de la opcion cuando es desconocida (?) o INCOMPLETA respecto a las opciones indicadas.

	static struct option long_options[] =
	{

		{"username", required_argument, 0, 'u'},
		{"useruid",  required_argument, 0, 'i'},
		{"groupname", required_argument, 0, 'g'},
		{"grupouid", required_argument, 0, 'd'},
		{"allgroups", no_argument, 0, 's'},
		{"allinfo", required_argument, 0, 'a'},
		{"bactive", no_argument, 0, 'b'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};

	/* getopt_long guardará el indice de la opcion en esta variable */
	int option_index = 0;

	if( argc == 1 ){
		if ( ((lgn = getenv("USER")) == NULL) || ((pw = getpwnam(lgn)) == NULL) )
		{
			fprintf(stderr, "La información del usurario es incorrecta\n" );
			exit(-1);					
		}

		printf("\nNombre: %s\n", pw->pw_gecos);
		printf("Login: %s\n", pw->pw_name);
		printf("UID: %d\n", pw->pw_uid);
		printf("Password: %s\n", pw->pw_passwd);
		printf("Home: %s\n", pw->pw_dir);

		// Obetnemos la estructura de informacion del grupo a través del número de grupo al que pertenece el usuario
		gr = getgrgid(pw->pw_gid);

		// Imprimimos en nuestro caso el campo de la estructura que nos interesa
		printf("Nombre del grupo principal: %s\n", gr->gr_name);
		printf("Número de grupo principal: %d\n", gr->gr_gid);
	}

	while( (c = getopt_long (argc, argv, "u:i:g:d:a:bhs", long_options, &option_index))!=-1 )
	{
		if(c == -1)
		{
			break;
		}

		switch(c) // tengo que añadir la excepcion de que no puedo poner -u i72bemof -i 97381 
		{
			case 'u':
				uflag = 1;
				lgn = optarg;

				break;

			case 'i':
				iflag = 1;
				uid = atoi(optarg);

				break;

			case 'g':
				gflag = 1;
				nombre_grupo = optarg;

				break;

			case 'd':
				dflag = 1;
				uid_grupo = atoi(optarg);

				break;

			case 's':
				sflag = 1;

				break;

			case 'a':
				aflag = 1;
				lgn = optarg;

				break;

			case 'b':
				bflag = 1;

				break;

			case 'h':
				hflag = 1;
				imprimir_uso();
				break;

			case '?':
			// No hace falta hacer nada, a no ser que queramos poner nuestros propios errores
				break;


			default:
				abort();
			
		}
	}

	if( (uflag==1)&&(iflag==1) )
	{
		printf("Error las opciones -u y -i no pueden activarse a la vez\n");
		exit(-1);
	}

	if( (uflag==1)&&(aflag==1) )
	{
		printf("Error las opciones -u y -a no pueden activarse a la vez\n");
		exit(-1);
	}

	if(uflag==1)
	{
		if ( (pw = getpwnam(lgn)) == NULL )
		{
			fprintf(stderr, "El login del usuario es incorrecto\n" );
			exit(-1);
		}
			printf("\nNombre: %s\n", pw->pw_gecos);
			printf("Login: %s\n", pw->pw_name);
			printf("UID: %d\n", pw->pw_uid);
			printf("Password: %s\n", pw->pw_passwd);
			printf("Home: %s\n", pw->pw_dir);
	}

	if(iflag==1)
	{
		if ( ( pw = getpwuid(uid) ) == NULL ) // a la funcion getpwuid le puedo pasar un entero que sea el identificador del nombre de usuario que quiero consultar
		{
			fprintf(stderr, "El uid o identificador del usuario es incorrecto\n" );
			exit(-1);
		}
			printf("\nNombre: %s\n", pw->pw_gecos);
			printf("Login: %s\n", pw->pw_name);
			printf("UID: %d\n", pw->pw_uid);
			printf("Password: %s\n", pw->pw_passwd);
			printf("Home: %s\n", pw->pw_dir);
	}

	if(gflag==1)
	{

		if ( ( gr = getgrnam(nombre_grupo) ) == NULL )
		{
			fprintf(stderr, "La informacion del usuario es incorrecta\n");
			exit(-1);
		}

		printf("\nNúmero del grupo pricipal: %d\n", gr->gr_gid);
	}

	if(dflag==1)
	{

		if ( ( gr = getgrgid(uid_grupo) ) == NULL )
		{
			fprintf(stderr, "La informacion del usuario es incorrecta\n");
			exit(-1);
		}

		printf("\nNombre del grupo principal: %s\n", gr->gr_name);
	}

	if(sflag==1)
	{
		if ( ( f = fopen("/etc/group", "r") ) == NULL )
		{
			fprintf(stderr, "Error al abrir el fichero <%s>\n", "group.txt");
			exit(-1);
		}

		while(fgets(grupo, 1024, f)!=NULL)
		{
			token = strtok(grupo, ":");

			if ( (token == NULL) || ( ( gr = getgrnam(token) ) == NULL ) )
			{
				fprintf(stderr, "La informacion del usuario es incorrecta\n");
				fclose(f);
				exit(-1);		
			}

			printf("\nNombre del grupo principal: %s\n", gr->gr_name);
			printf("Número del grupo pricipal: %d\n", gr->gr_gid);

		}

		fclose(f);
	}

	if(aflag==1)
	{
		if ( (pw = getpwnam(lgn)) == NULL )
		{
			fprintf(stderr, "La información del usurario es incorrecta\n" );
			exit(-1);
		}
			printf("\nNombre: %s\n", pw->pw_gecos);
			printf("Login: %s\n", pw->pw_name);
			printf("UID: %d\n", pw->pw_uid);
			printf("Password: %s\n", pw->pw_passwd);
			printf("Home: %s\n", pw->pw_dir);

			// Obetnemos la estructura de informacion del grupo a través del número de grupo al que pertenece el usuario
			gr = getgrgid(pw->pw_gid);

			// Imprimimos en nuestro caso el campo de la estructura que nos interesa
			printf("Nombre del grupo principal: %s\n", gr->gr_name);
			printf("Número de grupo principal: %d\n", gr->gr_gid);
	}

	if(bflag==1)
	{
		bflag = 1;
		if ( ((lgn = getenv("USER")) == NULL) || ((pw = getpwnam(lgn)) == NULL) )
		{
			fprintf(stderr, "La información del usurario es incorrecta\n" );
			exit(-1);					
		}
			// Obetnemos la estructura de informacion del grupo a través del número de grupo al que pertenece el usuario
			gr = getgrgid(pw->pw_gid);

			// Imprimimos en nuestro caso el campo de la estructura que nos interesa
			printf("\nNombre del grupo principal: %s\n", gr->gr_name);
			printf("Número de grupo principal: %d\n", gr->gr_gid);
	}

	/* Imprimimos el resto de argumentos de la linea de comandos que no son opciones con "-" */
	if (optind < argc)
	{
		printf("\nArgumentos ARGV que no son opciones: ");
		while (optind < argc)
		{
			printf("%s ", argv[optind++]);
		}
		putchar('\n');
	}


	printf("\nSe han activado:\n");
	printf("\t uflag: %d\n", uflag);
	printf("\t iflag: %d\n", iflag);
	printf("\t gflag: %d\n", gflag);
	printf("\t dflag: %d\n", dflag);
	printf("\t sflag: %d\n", sflag);
	printf("\t aflag: %d\n", aflag);
	printf("\t bflag: %d\n", bflag);
	printf("\t hflag: %d\n\n", hflag);

	return 0;
}