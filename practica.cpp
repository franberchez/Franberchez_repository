/***********************************
 * Autor: Francisco Berchez Moreno
 * Universidad de Córdoba (Spain)
 *
 * Asignatura: Fundaments in Intelligent Systems in Vision
 * 
 * Info:
 * 
 * 
 * 
 * ******************************************/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <vector>
#include <iostream>
using namespace std;
cv::Mat image;
cv::Mat new_image;
int counter = 0;
CvPoint p1;
CvPoint p2;

//callback function. Whenever the mouse is moved or a button pressed, this function is called
void on_mouse( int event, int x, int y, int flags, void *param)
{
	if (event==CV_EVENT_LBUTTONDOWN) 
	{

		counter++;
	 	
	 	//refresh the image window
		cv::imshow("RGB_Image",image);
		if (counter == 1)
		{
		  p1.x = x;
		  p1.y = y;
		}

		if (counter == 2)
		{
			p2.x = x;
			p2.y = y;
		  	if (p1.x > p2.x)
		  	{
		  		int aux = p1.x;
		  		p1.x = p2.x;
		  		p2.x = aux;
		  	} 

		  	if (p1.y > p2.y)
		  	{
		  		int aux = p1.y;
		  		p1.y = p2.y;
		  		p2.y = aux;
		  	} 

		  	// Creates a new window
		  	cv::namedWindow("New_Image");
		  	//saves file
		  	cv::imwrite("gray.jpg", image);
		  	//Load an image froma file
		  	new_image = cv::imread("gray.jpg");

		  	for(int y=0;y<new_image.rows;y++)
		  	{ 
		  		uchar *ptr=new_image.ptr<uchar>(y);//pointer to the y-th image row
		  		for(int x=0;x<new_image.cols;x++)
		  		{
		  			if( (x < p1.x or x > p2.x) or (y < p1.y or y > p2.y) )
		  			{
		  				float average = (ptr[0] + ptr[1] + ptr[2])/3;
		  				ptr[0] = average;
		  				ptr[1] = average;
		  				ptr[2] = average;
		  			}
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