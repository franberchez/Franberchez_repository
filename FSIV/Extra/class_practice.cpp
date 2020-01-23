/***********************************
 * Author: Francisco Berchez Moreno
 * Universidad de Córdoba (Spain)
 *
 * Subject: Fundaments in Intelligent Systems in Vision
 * 
 *
 * 
 * 
 * 
 * ******************************************/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <vector>
#include <iostream>
using namespace std;

cv::Mat image, image2;
vector <double> histogram;
vector <int> equilized;
int value;

int main(int argc, char **argv)
{
	try{
		
		// Loads an image from a file
		image=cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
		
		if( image.rows==0) {cerr<<"Error reading the image"<<endl;return 0;}
		
		// Creates a new window
		cv::namedWindow("RGB_Image");
		cv::namedWindow("New_Image");

		// the total of pixels is 256 because we go from 0 to 255
		histogram.resize(256);

		image2 = image.clone();

		for(int y=0;y<image.rows;y++)
		{ 
			for(int x=0;x<image.cols;x++)
			{
				// Guardo en el vector histogram el valor de la imagen en la coordenada x y + 1 CREO
				histogram[image.at<uchar>(y,x)]+=1;
			}
		}

		// Calculo el numero total de pixeles de la imagen dividiendo el numero de filas entre el numero de columnas
		double total_pixels = image.rows * image.cols;

		//Normalized histogram
		for (int i = 0; i<histogram.size(); i++)
		{
			// Para normalizar el histograma lo que hacemos es multiplicar cada elemento del vector por el tamaño de de histogram
			// que es 256 y lo divido entre el total de pixeles
			histogram[i] = (histogram[i]*histogram.size())/total_pixels;
		}

		//Accumulative
		for (int i = 1; i<histogram.size(); i++)
		{
			// Para calcular el acumulado, a cada elemento del vector histogram le sumamos
			// el valor del elemnto anterior el i-1
			histogram[i] = histogram[i]+histogram[i-1];
		}


		// Volvemos crear la imagen con el histograma
		for(int y=0;y<image2.rows;y++)
		{
			for(int x=0;x<image2.cols;x++)
			{
				// A la imagen en la coordenadas x y le asignamos el valor del vector histogram
				// cuyo indice sera el valor de la imagen en la coordenada x y
				value = image2.at<uchar>(y,x);
				image2.at<uchar>(y,x) = histogram[value];
			}
		}
		
		// Displays the image in the window
		cv::imshow("RGB_Image", image);
		cv::imshow("New_Image", image2);

		
		// Wait for a key to be pressed
		cv::waitKey(0);
		
		cv::imwrite(argv[2], image2);

	}catch(std::exception &ex)
	{

		cout<<ex.what()<<endl;
	}
}