/***********************************
 * Author: Francisco Berchez Moreno
 * Universidad de Córdoba (Spain)
 *
 * Subject: Fundaments in Intelligent Systems in Vision
 * 
 * Info: 
 * 
 * 
 * ******************************************/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;


// ./mandatory -f 0 -g 0 rgb.png output.png




// Class to manage command line arguments
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


// Return a matrix, that is the mask
cv::Mat create_sharp_filter(int type, float g)
{
	// This image is goint to be the mask that im goin to return
	cv::Mat image;
	image.create(3,3,CV_32FC1);

	if (type == 0) // Create a sharp filter of 5 points
	{
		// Estos valores se especifican en un funcion de la ma triz proporcionada
		// en el ejercicio
		image.at<float>(0,0) = 0.;
		image.at<float>(0,1) = -1.;
		image.at<float>(0,2) = 0.;
		image.at<float>(1,0) = -1.;
		image.at<float>(1,1) = g+4.;
		image.at<float>(1,2) = -1.;
		image.at<float>(2,0) = 0.;
		image.at<float>(2,1) = -1.;
		image.at<float>(2,2) = 0.;
	}

	else // type = 1 Create a sharp filter of 9 points
	{
		// Ocurre exactamente lo mismo que arriba
		image.at<float>(0,0) = -1.;
		image.at<float>(0,1) = -1.;
		image.at<float>(0,2) = -1.;
		image.at<float>(1,0) = -1.;
		image.at<float>(1,1) = g+8.;
		image.at<float>(1,2) = -1.;
		image.at<float>(2,0) = -1.;
		image.at<float>(2,1) = -1.;
		image.at<float>(2,2) = -1.;
	}
	
	return image;
}


// Intentar entender como funciona esta funcion convolution
/*
* in: va a ser la imagen de original normalizada y en esacala de grises
* filter: es la mascara o filtro que le vamos a aplicar a la imagen in
* out: es la imagen resultante de aplicarle la mascara o el filtro a la imagen in
* border_type: es valor que tomaran los pixeles del borde de la imagen
*/
void convolve(const cv::Mat& in, const cv::Mat& filter, cv::Mat& out, int border_type=0)
{
	// Tecnicamente no haria falta hacer el clone porque tengo el Mat::zeros abajo
	out = in.clone();

	int filter_rows = (filter.rows-1)/2;

	for (int x = 0; x < in.rows; x++)
	{
		for (int y = 0; y < in.cols; y++)
		{
			// INTENTAR ENTENDER QUE ES LO QUE HACEMOS AQUI
			// Si no me equivoco sirve para evitar que nos salgamos de la imagen y que los bordes los pongamos a 0
			if (x < filter_rows || y < filter_rows || (y + filter_rows)>=in.cols || (x+filter_rows)>=in.rows)
			{
				out.at<float>(x,y)=0.0;
			}

			else
			{			
				float sum = 0.0;
				// Lo que hemos hecho ha sido crear una convolution general para todas las imagenes
				for (int k = 0; k < filter.rows; k++)
				{
					for (int l = 0; l < filter.cols; l++)
					{
						sum += in.at<float>(x - filter_rows + k, y - filter_rows + l) * filter.at<float>(k,l);
					}
				}
				out.at<float>(x,y) = cv::saturate_cast<float>(sum);
			}

		}
	}
}


int main(int argc,char **argv){
	try{
		if(argc!=7) {cerr<<"Usage:image"<<endl;return 0;} 
		
		int f; // Controlls the type
		float g; // Give us the gain
		int border_type = 0;

		cv::Mat image;
		cv::Mat filter;
		cv::Mat out;

		//loads the image from file
		image=cv::imread(argv[argc-2]);
		
		if( image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}

		CmdLineParser cml(argc, argv);

		// El paramatro f me sirve para decidir que laplacioan hago en el sharp
		if(cml["-f"])
		{
			f = stoi(cml("-f"));
		}

		f = stoi(cml("-f", "1"));
		cout << "The values of -f is = " << f << endl;

		// Es el factor de ganacia que especificamos en la operacion
		if(cml["-g"])
		{
			g = stof(cml("-g"));
		}

		g = stof(cml("-g", "1"));

		// Nos sirve para indicar que la ganancia que establezcamos
		// ni 0 ni menor que 0
		if (g < 0)
		{
			cout << "Error, the gain must be bigger than 0" << endl;
			return 0;
		}

		else cout << "The values of -g is = " << g << endl;


		//creates a window and show an image
		cv::namedWindow("RGB_image");
		cv::imshow("RGB_image",image);

		// Normalizamos la imagen en un solo canal para luego poder transformarla a gris
		image.convertTo(image, CV_32FC1, 1./255.);

		// Hacemos una copia de la imagen, es como el clone, pero aqui especificamos
		// tamaño y tipo
		out = cv::Mat::zeros(image.size(),image.type());

		// Transformamos las imagenes a escala de grises
		// ya que para aplicar los filtros tenemos que pasar las imagenes a escala de
		// grises si no, no podremos hacerlo
		cv::cvtColor(image, image, CV_RGB2GRAY);
		cv::cvtColor(out, out, CV_RGB2GRAY);

		// filter is going to be the mask
		// Este create sirve para crear el filtro del laplacian de 3x3
		filter.create(3,3,CV_32FC1);
		filter = create_sharp_filter(f, g).clone();

		// Aplicamos convolution para aplicarle la marcas a la imagen que sera el filtro
		convolve(image, filter, out, border_type);

		out = image + out*g;

		cv::namedWindow("Mask_image");
		cv::imshow("Mask_image", out);

		//wait for a key to be pressed
		cv::waitKey(0);

		// Desnormalizamos la imagen para poder guardarla correctamente
		out.convertTo(out, CV_32FC1, 255.);
		cv::imwrite(argv[argc-1], out);

	}catch(std::exception &ex)
	{
		cout<<ex.what()<<endl;
	}

}
