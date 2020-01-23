/***********************************
 * Author: Francisco Berchez Moreno
 * Universidad de Córdoba (Spain)
 *
 * Subject: Fundaments in Intelligent Systems in Vision
 * 
 * Info: That program change the contrast, gamma and brightness of an image,
 * that could be mochrome or in color
 * 
 * 
 * ******************************************/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <math.h>
using namespace std;

cv::Mat image, image2, image3;

// Estas variable sirven para poder cambiar los valores decimales de
// constraste, brillo y gamma
float c;
float b;
float g;

// Las variables que me permiten ir por la barra que son enteras porque el value que recibe
// el createTrackbar que un int*
int contrast_slider;
int brightness_slider;
int gamma_slider;

// Esta bandera no sirve para identificar si la imagen que le pasamos es gris
int flag_grey = 0;

// ./mandatory -i -c 1 -b 0 -g 1 rgb.png output.jpg


// Class to manage command line arguments
// Basicamente sirve para detectar parametros que pasamos por linea de comandos
class CmdLineParser{
   int argc;
   char **argv;
public:
   CmdLineParser(int _argc,char **_argv):argc(_argc),argv(_argv){} 
   bool operator[] ( string param ) {int idx=-1;  for ( int i=0; i<argc &&
    idx==-1; i++ ) if ( string ( argv[i] ) ==param ) idx=i;    return ( idx!=-1 ) ;    
	}
   
   string operator()(string param,string defvalue="-1"){int idx=-1;    for ( int 
   	i=0; i<argc && idx==-1; i++ ) if ( string ( argv[i] ) ==param ) idx=i; if ( 
   	idx==-1 ) return defvalue;   else  return ( argv[  idx+1] ); }
};

// Aunque se llame contrast trackbar esta funcion detecta que valor de las tres variables es el que se ha modificado
static void contrast_trackbar( int, void* )
{
   c = (float) contrast_slider;
   g = (float) gamma_slider;
   b = (float) brightness_slider;

   image3 = image2.clone();

   	// En caso de la imagen tenga un solo canal, es decir, que sea gris
	if (flag_grey == 1)
	{
		for(int y=0;y<image2.rows;y++)
		{
			float *ptr1=image2.ptr<float>(y);//pointer to the y-th image row
			float *ptr2=image3.ptr<float>(y);//pointer to the y-th image row
			for(int x=0;x<image2.cols;x++)
			{
				// b = 150 Cuando lo hemos pasado 0.5
				ptr2[0] = cv::saturate_cast<float>( c/100. * pow(ptr1[0], g/100.) + (b-100.)/100.);
				ptr2[1] = cv::saturate_cast<float>( c/100. * pow(ptr1[1], g/100.) + (b-100.)/100.);
				ptr2[2] = cv::saturate_cast<float>( c/100. * pow(ptr1[2], g/100.) + (b-100.)/100.);
				
				// ptr2[0] = cv::saturate_cast<float>(c/100. * pow(ptr[1], g/100.) + ((b/100.)-1)))
				
				//Esto porque la imagen tiene un solo canal por ser gris
				ptr2+=1;
				ptr1+=1;
			}
		}
	}

	// En caso de que la imagen sea RGB
	else
	{
		for(int y=0;y<image2.rows;y++)
		{
			float *ptr1=image2.ptr<float>(y);//pointer to the y-th image row
			float *ptr2=image3.ptr<float>(y);//pointer to the y-th image row
			for(int x=0;x<image2.cols;x++)
			{
				// b = 150 Cuando lo hemos pasado 0.5
				ptr2[0] = cv::saturate_cast<float>( c/100. * pow(ptr1[0], g/100.) + (b-100.)/100.);
				ptr2[1] = cv::saturate_cast<float>( c/100. * pow(ptr1[1], g/100.) + (b-100.)/100.);
				ptr2[2] = cv::saturate_cast<float>( c/100. * pow(ptr1[2], g/100.) + (b-100.)/100.);
				ptr2+=3;//moves the pointer 3 elements
				ptr1+=3;
			}
		}
	}		

   cv::imshow("RGB_Image", image3);
}


int main(int argc, char **argv)
{
	try{
		// if(argc < 9) {cerr<<"Usage:image"<<endl; return 0;}
		// Loads an image from a file
		image=cv::imread(argv[argc-2]);
		if( image.rows==0) {cerr<<"Error reading the image"<<endl;return 0;}
		
		// UNA IMAGEN ES GRIS SI TIENE UN SOLO CANAL
		if (image.channels() == 1)
		{
			flag_grey = 1;
		}

		// Before apply the operation, the image must be normalized
		// Como dice el enunciado para poder aplicar la operacion antres debemos normalizar la imagen
		image.convertTo(image2, CV_32F, 1./255.);

		/*
			I' = c * I^g + b

			I' is the normalized image (image2)
			c is the contrast
			I is the orginal image (image)
			g is the gamma
			b is the brightness

		*/

		/*

			-c is in the range [0,2]
			-b is in the range [-1,1]
			-g is in the range [0,2]
			-i if i put it I enable the interactive mode

		*/
		
		// processImg [-i] [-c <float=1.0>] [-b <float=0.0>] [-g <float=1.0>] <input image> <output image>

		// Creates a new window
		cv::namedWindow("RGB_Image");

		// Lo tenemos que poner para detectar los parametros
		CmdLineParser cml(argc, argv);


		// If in command line I detect the option -c go inside that if
		if (cml["-c"])
		{
			//cout << "-c in the comand line" << endl;
			c = stof(cml("-c"));
			//contrast_slider = (int) c * 100.;
		}

		// If the option -c isn't in command line the programm will do that
		c = stof(cml("-c", "1")); // if -c is not, then return 1
		cout << "The value of -c is = " << c << endl;

		if (cml["-b"])
		{
			//cout << "-b in the command line" << endl;
			b = stof(cml("-b"));
		}

		b = stof(cml("-b", "1"));
		cout << "The value of -b is = " << b << endl;

		if (cml["-g"])
		{
			g = stof(cml("-g"));
		}


		g = stof(cml("-g", "1"));
		cout << "The value of -g is = " << g << endl;

		// Aqui entramos en caso de que queramos usar el modo interactivo con el comando -i
		if (cml["-i"])
		{
			cout << "Interactive mode: ON" << endl;

			contrast_slider = (int) c * 100.;
			cv::createTrackbar("Contrast", "RGB_Image", &contrast_slider, 200, contrast_trackbar);

			// b = 0.5
			brightness_slider = (int) (b+1) * 100.;
			cv::createTrackbar("Brightness", "RGB_Image", &brightness_slider, 200, contrast_trackbar);


			gamma_slider = (int) g * 100.;
			cv::createTrackbar("Gamma", "RGB_Image", &gamma_slider, 200, contrast_trackbar);
		}

		// if option -i is not active we do that
		// Entramos aqui en caso de que no este activo el modo interactivo
		else
		{
			// if the contrast is 0 the image is black
			// if the gamma is 2 the image is white
			// if the bright is -1 the image is black
			image3 = image2.clone();

			for(int y=0;y<image2.rows;y++)
			{
				float *ptr=image2.ptr<float>(y);//pointer to the y-th image row
				for(int x=0;x<image2.cols;x++)
				{
					// Aplicamos la operacion a cada pixel
					ptr[0] = (c * pow(ptr[0], g)) + b;
					ptr[1] = (c * pow(ptr[1], g)) + b;
					ptr[2] = (c * pow(ptr[2], g)) + b;
					ptr+=3;//moves the pointer 3 elements
				}
			}
		}
		
		// Displays the image in the window
		cv::imshow("RGB_Image", image2);
		
		// Here we desnormalized an image

		// Wait for a key to be pressed
		cv::waitKey(0);

		image3.convertTo(image3, CV_8U, 255.);
		cv::imwrite(argv[argc-1], image3);
		
	}catch(std::exception &ex)
	{

		cout<<ex.what()<<endl;
	}
}

// set(CMAKE_CXX_STANDARD 11) # C+11...