/***********************************
 * Author: Francisco Berchez Moreno
 * Universidad de Córdoba (Spain)
 *
 * Subject: Fundaments in Intelligent Systems in Vision
 * 
 * Info: Make an interactive rectangle while the user moves the mouse
 * 
 * 
 * 
 * ******************************************/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
cv::Mat image;
cv::Mat image2;
cv::Mat image3;
bool drawing;
char c;
CvPoint p1;
CvPoint p2;

//void cv::rectangle(InputOutputArray img, point p1, point p2, const Scalar & color, int thickness, int linetype, int shift);

//callback function. Whenever the mouse is moved or a button pressed, this function is called
void on_mouse( int event, int x, int y, int flags, void *param)
{
	if (event == CV_EVENT_LBUTTONDOWN) 
	{
		drawing = true;
		p1.x = x;
		p1.y = y;
		image3 = image.clone();
	}

	if (event == CV_EVENT_MOUSEMOVE)
	{
		if (drawing == true)
		{
			p2.x = x;
			p2.y = y;
		}
	}

	if (event == CV_EVENT_LBUTTONUP)
	{
		p2.x = x;
		p2.y = y;
		drawing = false;

		cv::namedWindow("New_Image");

		cv::rectangle(image3, p1, p2, cv::Scalar(0, 0, 0), 1, 50, 0);

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

		  	for(int y=0;y<image3.rows;y++)
		  	{ 
		  		uchar *ptr=image3.ptr<uchar>(y);//pointer to the y-th image row
		  		for(int x=0;x<image3.cols;x++)
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

		cv::imshow("New_Image", image3);
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
		
		// Wait for ESC to be pressed
		while(c!=27)
		{
			c = cv::waitKey(100);

			if (drawing == true)
			{				
				image2 = image.clone();
				cv::rectangle (image2, p1, p2, cv::Scalar(0, 0, 0), 1, 50, 0);
				cv::imshow("RGB_Image", image2);
			}

			else
			{
				cv::imshow("RGB_Image", image);
			}
			
		}
		

	}catch(std::exception &ex)
	{

		cout<<ex.what()<<endl;
	}
}