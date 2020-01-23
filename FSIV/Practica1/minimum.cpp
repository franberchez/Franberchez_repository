/***********************************
 * Author: Francisco Berchez Moreno
 * Universidad de Córdoba (Spain)
 *
 * Subject: Fundaments in Intelligent Systems in Vision
 * 
 * Info: Make a rectangle with two points
 * 
 * 
 * 
 * ******************************************/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
using namespace std;
cv::Mat image;
cv::Mat new_image;

// Por que con dos clicks ya formo el rectangulo
int counter = 0;

// Estos son los puntos que usamos para coordenadas de cada uno de los clicks en total 2
CvPoint p1;
CvPoint p2;

//callback function. Whenever the mouse is moved or a button pressed, this function is called
/*
* event: es el evento que registramos
* x: es la coordenada x
* y: es la coordenada y
* flags son banderas
* *param: parametro por defecto que lo ponemos asi y ya esta
*/
void on_mouse( int event, int x, int y, int flags, void *param)
{
	// Comprobamos si pulsamos el boton derecho del raton
	if (event==CV_EVENT_LBUTTONDOWN) 
	{
		counter++;
	 	
	 	//refresh the image window
		cv::imshow("RGB_Image",image);

		// Si es el primer click guardo sus coordenadas
		if (counter == 1)
		{
		  p1.x = x;
		  p1.y = y;
		}

		// Si es el segundo click guardo sus coordenadas
		if (counter == 2)
		{
			p2.x = x;
			p2.y = y;

			// Hacemos el ajuste de la coordenada x para que la del punto 2 siempre sea mayor que la del punto 1
		  	if (p1.x > p2.x)
		  	{
		  		int aux = p1.x;
		  		p1.x = p2.x;
		  		p2.x = aux;
		  	} 

		  	// Hacemos el ajuste de la coordenada y para que la del punto 2 siempre sea mayor que la del punto 1
		  	if (p1.y > p2.y)
		  	{
		  		int aux = p1.y;
		  		p1.y = p2.y;
		  		p2.y = aux;
		  	} 

		  	// Creates a new window
		  	cv::namedWindow("New_Image");
		  	new_image = image.clone();

		  	for(int y=0;y<new_image.rows;y++)
		  	{ 
		  		uchar *ptr=new_image.ptr<uchar>(y);//pointer to the y-th image row
		  		for(int x=0;x<new_image.cols;x++)
		  		{
		  			if( (x < p1.x or x > p2.x) or (y < p1.y or y > p2.y) )
		  			{
		  				// Esta es la transformacion de cada pixel que hay alrededor del rectangulo que se genera a gris
		  				float average = (ptr[0] + ptr[1] + ptr[2])/3;
		  				ptr[0] = average;
		  				ptr[1] = average;
		  				ptr[2] = average;
		  			}
		  				// Por que vamos de 3 en 3 y asi no nos comemos el gap este de se decia en teoria
		  				ptr+=3;
		  		}
		  	}

		  	counter = 0;
		  	// Displays the image in the window
		  	cv::imshow("New_Image", new_image);
		}

	}
}

int main(int argc, char **argv)
{
	try{
		if(argc!=2) {cerr<<"Usage:image"<<endl; return 0;}
		// Loads an image from a file
		image=cv::imread(argv[1]);
		if( image.rows==0) {cerr<<"Error reading the image"<<endl;return 0;}
		// Creates a new window
		cv::namedWindow("RGB_Image");
		// Indicates that the on_mouse function should be called in case of mouse moved or pressed over window
		
		// Es basicamente un manejador de eventos para el uso del raton del pc
		/*
		* Le paso el nombre de la centana en la que voy a mostrar la imagen
		* El nombre de la funcion on_mouse que va a ser la que gestione el evento
		* y 0 por defecto
		*/
		cvSetMouseCallback( "RGB_Image", on_mouse, 0 );

		// Displays the image in the window
		cv::imshow("RGB_Image", image);
		// Wait for a key to be pressed
		cv::waitKey(0);
	}catch(std::exception &ex)
	{

		cout<<ex.what()<<endl;
	}
}