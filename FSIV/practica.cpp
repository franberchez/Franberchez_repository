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
vector <int> v1;
vector <int> v2;
int value_x_large;
int value_x_small;
int value_y_large;
int value_y_small;


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

		counter++;
		
	  //refresh the image window
	  cv::imshow("RGB_Image",image);
	  if (counter == 1)
	  {
	  	v1.resize(2);
	  	v1[0] = x;
	  	v1[1] = y;
	  }

	  if (counter > 2)
	  {
	  	counter = 1;
	  }

	  if (counter == 2)
	  {
	  	v2.resize(2);
	  	v2[0] = x;
	  	v2[1] = y;

	  	if (v2[0] > v1[0])
	  	{
	  		value_x_large = v2[0];
	  		value_x_small = v1[0];
	  	} 

	  	else
	  	{
	  		value_x_large = v1[0];
	  		value_x_small = v2[0];
	  	} 

	  	if (v2[1] > v1[1])
	  	{
	  		value_y_large = v2[1];
	  		value_y_small = v1[1];
	  	}

	  	else
	  	{
	  		value_y_large = v1[1];
	  		value_y_small = v2[1];
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
	  			/*if( ((x > value_x_large) or (x < value_x_small)) and ((y > value_y_large) or (y < value_y_small)) )
	  			{  				
		  			float average = (ptr[0] + ptr[1] + ptr[2])/3;
		  			ptr[0] = average;
		  			ptr[1] = average;
		  			ptr[2] = average;
		  			ptr+=3;
	  			}*/

	  			if( x > value_x_large or x < value_x_small)
	  			{
	  				float average = (ptr[0] + ptr[1] + ptr[2])/3;
	  				ptr[0] = average;
	  				ptr[1] = average;
	  				ptr[2] = average;
	  				ptr+=3;
	  			}

	  			if ( y > value_y_large or y < value_y_small )
	  			{
	  				float average = (ptr[0] + ptr[1] + ptr[2])/3;
	  				ptr[0] = average;
	  				ptr[1] = average;
	  				ptr[2] = average;
	  				ptr+=3;
	  			}
	  		}
	  	}


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