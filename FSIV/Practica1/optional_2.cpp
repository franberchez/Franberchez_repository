/***********************************
 * Author: Francisco Berchez Moreno
 * Universidad de Córdoba (Spain)
 *
 * Subject: Fundaments in Intelligent Systems in Vision
 * 
 * Info: Draw a polygon in the image, the number of vertex is define by the user 
 * by clicking pointes with the left button of the mouse and when the user wants
 * to stop he/she just need to click one thime with the right button of the mouse
 * 
 * 
 * 
 * ******************************************/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/imgproc.hpp>
#include <vector>
#include <iostream>
using namespace std;
cv::Mat image;
cv::Mat image2;
cv::Mat image3;
int vertex;
vector <cv::Point> v;

//callback function. Whenever the mouse is moved or a button pressed, this function is called
void on_mouse( int event, int x, int y, int flags, void *param)
{
		
	if (event == CV_EVENT_RBUTTONDOWN)
	{
		const cv::Point *pts = (const cv::Point*) cv::Mat(v).data;
		int npts = cv::Mat(v).rows;

		image2 = image.clone();

		for(int y=0;y<image2.rows;y++)
		{ 
			uchar *ptr=image2.ptr<uchar>(y);//pointer to the y-th image row
			for(int x=0;x<image2.cols;x++)
			{
				ptr[0] = 255;
				ptr[1] = 0;
				ptr[2] = 0;
				ptr+=3;
			}
		}

		cv::fillPoly(image2, &pts, &npts, 1, cv::Scalar(255, 255, 255), 1, 0);
		
		image3 = image.clone();
		cv::namedWindow("New_image");

		for(int y=0;y<image3.rows;y++)
		{ 
			uchar *ptr_1=image2.ptr<uchar>(y);//pointer to the y-th image row
			uchar *ptr_2=image3.ptr<uchar>(y);
			for(int x=0;x<image3.cols;x++)
			{
				if( (ptr_1[0] == 255) and (ptr_1[1] == 0) and (ptr_1[2] == 0) and (ptr_1 != ptr_2) )
				{
					float average = (ptr_2[0] + ptr_2[1] + ptr_2[2])/3;
					ptr_2[0] = average;
					ptr_2[1] = average;
					ptr_2[2] = average;
				}
				ptr_1+=3;
				ptr_2+=3;
			}
		}
		cv::imshow("New_image", image3);

	}

	if (event == CV_EVENT_LBUTTONDOWN) 
	{
		v.push_back(cv::Point(x, y));
	}
}

int main(int argc, char **argv)
{
	try{
		if(argc!=2) {cerr<<"Usage:image"<<endl; return 0;}
		int response = 1;
		
		do{			
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
			char c = 0;
			while (c!=27)
				c = cv::waitKey(100);

			cv::destroyAllWindows();
			v.clear();

			cout << endl;
			cout << "Do you want to repeat the process" << endl;
			cout << "\tPress 1 for YES" << endl;
			cout << "\tPress 2 for NO" << endl;
			cout << "Introduce your option: ";
			cin >> response;
			cout << endl;

			if(response == 1) response = 1;

			else response = 2;

		}while (response != 2);


	}catch(std::exception &ex)
	{
		cout<<ex.what()<<endl;
	}
}