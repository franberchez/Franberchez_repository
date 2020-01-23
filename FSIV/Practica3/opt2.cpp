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


// ./opt2 -i -f 0 -g 0 rgb.png output.png

typedef struct{
	cv::Mat in;
	cv::Mat filter;
	cv::Mat out;
}parameters;

int type_slider;
int gain_slider;


cv::Mat out;

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



void convolve(const cv::Mat& in, const cv::Mat& filter, cv::Mat& out, int border_type=0)
{
	out = in.clone();

	int filter_rows = (filter.rows-1)/2;

	for (int x = 0; x < in.rows; x++)
	{
		for (int y = 0; y < in.cols; y++)
		{

			if (x < filter_rows || y < filter_rows ||+ (y + filter_rows)>=in.cols || (x+filter_rows)>=in.rows)
			{
				out.at<float>(x,y)=0.0;
			}

			else
			{			
				float sum = 0.0;

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




static void on_trackar( int , void* userdata)
{

	parameters* images = (parameters*) userdata;

	cv::Mat image = ((*images).in).clone();

	cv::Mat filter;

	int f = (int) type_slider;
	float g = (float) gain_slider / 100.;

	image.convertTo(image, CV_32FC1, 1./255.);

	out = cv::Mat::zeros(image.size(),image.type());

	cv::cvtColor(image, image, CV_RGB2GRAY);
	cv::cvtColor(out, out, CV_RGB2GRAY);

	// filter is going to be the mask
	filter.create(3,3,CV_32FC1);
	filter = create_sharp_filter(f, g).clone();

	convolve(image, filter, out, 0);

	out = image + out*g;

   	cv::imshow("RGB_image", out);
}




int main(int argc,char **argv){
	try{
		//if(argc!=8) {cerr<<"Usage:image"<<endl;return 0;} 
		
		/* Initial variables */		
		int f; // Controlls the type
		float g; // Give us the gain
		int border_type = 0;

		/* Parameter for waitkey */
		char c;

		cv::Mat image;
		cv::Mat filter;

		parameters images;

		cv::namedWindow("RGB_image");


		//loads the image from file
		image=cv::imread(argv[argc-2]);
		images.in = image.clone();
		
		if( image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}


		/* Here we read the arguments */

		CmdLineParser cml(argc, argv);

		if(cml["-f"])
		{
			f = stoi(cml("-f"));
		}

		f = stoi(cml("-f", "1"));
		cout << "The values of -f is = " << f << endl;

		if(cml["-g"])
		{
			g = stof(cml("-g"));
		}

		g = stof(cml("-g", "1"));

		if (g < 0)
		{
			cout << "Error, the gain must be bigger than 0" << endl;
			return 0;
		}


		else cout << "The values of -g is = " << g << endl;

		/* Now we are going to see if the interactive mode is ON */

		if(cml["-i"])
		{	
			//interactive_flag = 1;
			cout << "Interactive mode: ON" << endl;

			type_slider = f;
			cv::createTrackbar("Type", "RGB_image", &type_slider, 1, on_trackar, &images);

			gain_slider = (int) g * 100.;
			cv::createTrackbar("Gain", "RGB_image", &gain_slider, 400, on_trackar, &images);

		}


		else
		{		
			//creates a window and show an image
			cv::imshow("RGB_image",image);

			image.convertTo(image, CV_32FC1, 1./255.);

			out = cv::Mat::zeros(image.size(),image.type());

			cv::cvtColor(image, image, CV_RGB2GRAY);
			cv::cvtColor(out, out, CV_RGB2GRAY);

			// filter is going to be the mask
			filter.create(3,3,CV_32FC1);
			filter = create_sharp_filter(f, g).clone();

			convolve(image, filter, out, border_type);

			out = image + out*g;

			cv::namedWindow("Mask_image");
			cv::imshow("Mask_image", out);
		}

		cv::imshow("RGB_image",image);

	   
		//wait for a key to be pressed
		c = cv::waitKey(0);

		if(c == 27)
		{
			return 0;
		}

		if(c == 10)
		{
			out.convertTo(out, CV_32FC1, 255.);
			cv::imwrite(argv[argc-1], out);
		}

	}catch(std::exception &ex)
	{
		cout<<ex.what()<<endl;
	}

}
