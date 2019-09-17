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
int contador = 0;

//callback function. Whenever the mouse is moved or a button pressed, this function is called
void on_mouse( int event, int x, int y, int flags, void *param)
{
	if (event==CV_EVENT_LBUTTONDOWN) 
	{
	  cout<<"x,y="<<x<<" "<<y<<endl;
	  //set as red a small window around
	  int xleft=x-3;
	  if( xleft<0) xleft=0;//check not out of image
	  int yleft=y-3;
	  if( yleft<0) yleft=0;//check not out of image
	  int xright=x+3;
	  if( xright> image.cols) xright=image.cols-1;//check not out of image
	  int yright=y+3;
	  if( yright> image.rows) yright=image.rows-1;//check not out of image
	  
	  for( int x=xleft;x<=xright;x++)
		for( int y=yleft;y<=yright;y++){
		uchar *ptr=image.ptr<uchar>(y)+3*x;
		ptr[0]=0;
		ptr[1]=0;
		ptr[2]=255;
		}

		contador++;
		
	  //refresh the image window
	  cv::imshow("RGB_Image",image);

	  if (contador > 2)
	  {
	  	contador = 0;
	  }

	  if (contador == 2)
	  {
	  	for(int y=0;y<image.rows;y++)
	  	{ 
	  		uchar *ptr=image.ptr<uchar>(y);//pointer to the y-th image row
	  		for(int x=0;x<image.cols;x++)
	  		{
	  			float average = (ptr[0] + ptr[1] + ptr[2])/3;
	  			ptr[0] = average;
	  			ptr[1] = average;
	  			ptr[2] = average;
	  			ptr+=3;
	  		}
	  	}


	  	// Creates a new window
	  	cv::namedWindow("New_Image");
	  	//saves file
	  	cv::imwrite("gray.jpg", image);
	  	//Load an image froma file
	  	new_image = cv::imread("gray.jpg");
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

		/*for(int y=0;y<image.rows;y++)
		{ 
			uchar *ptr=image.ptr<uchar>(y);//pointer to the y-th image row
			for(int x=0;x<image.cols;x++)
			{
				float average = (ptr[0] + ptr[1] + ptr[2])/3;
				ptr[0] = average;
				ptr[1] = average;
				ptr[2] = average;
				ptr+=3;
			}
		}

		// Creates a new window
		cv::namedWindow("New_Image");
		//saves file
		cv::imwrite("gray.jpg", image);
		//Load an image froma file
		new_image = cv::imread("gray.jpg");
		// Displays the image in the window
		cv::imshow("New_Image", new_image);**/


		// Wait for a key to be pressed
		cv::waitKey(0);
	}catch(std::exception &ex)
	{

		cout<<ex.what()<<endl;
	}
}