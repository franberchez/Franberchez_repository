#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <iomanip>

using namespace cv;
using namespace std;

// ./augReal -c=8 -r=6 -s=0.01 -y=camera.yml -v=definitivo.mp4
// ./augReal -c=8 -r=6 -s=0.01 -y=camera.yml -v=definitivo.mp4 -i=chinos.jpg
// ./augReal -c=8 -r=6 -s=0.01 -y=camera.yml -v=definitivo.mp4 -i=video.mp4

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{rows r         |      | number of rows of the chessboard.}"      //it is a positional argument, we assign repetitions with parser.get<int>(0)
    "{cols c         |      | number of cols of the chessboard}" //We can define default parameters
    "{size s         |      | string to show. Def. Hello}"
    "{yaml y         |      | .yml file obtained by calibration}"
    "{video v        |      | this is the video we are going to process}"
    "{image i        |      | image or video file}"
    ;

void video_function(Mat video_frame, Mat frame, vector<Point2f> inner_corners)
{
    resize(video_frame,video_frame,Size(inner_corners[7].x-inner_corners[0].x,inner_corners[40].y-inner_corners[0].y));

    vector<Point2f> dst;
    dst.push_back( inner_corners[0]);
    dst.push_back( inner_corners[7]);
    dst.push_back( inner_corners[40]);
    dst.push_back( inner_corners[47]);

    vector<Point2f> src;
    src.push_back(cv::Point2f(0, 0));
    src.push_back(cv::Point2f(video_frame.cols-1, 0));
    src.push_back(cv::Point2f(0, video_frame.rows-1));
    src.push_back(cv::Point2f(video_frame.cols-1, video_frame.rows-1));
    

    Mat changed=Mat(video_frame);
    Mat perspectivetransform=getPerspectiveTransform(src,dst);
    warpPerspective(video_frame, changed, perspectivetransform, frame.size());

    Mat mask = changed > 0;
    Mat merged = frame.clone();
    changed.copyTo(merged,mask);

    imshow("new_video", merged);
}


void image_function(Mat frame, Mat input_image, vector<Point2f> inner_corners)
{
    Point2f diff=inner_corners[0]-inner_corners[7];
    float dist_1 = sqrt((diff.x*diff.x) + (diff.y*diff.y));

    Point2f diff2=inner_corners[40]-inner_corners[0];
    float dist_2 = sqrt((diff2.x*diff2.x) + (diff2.y*diff2.y));

    resize(input_image,input_image,Size(dist_1, dist_2));

    vector<Point2f> dst;
    dst.push_back(inner_corners[0]);
    dst.push_back(inner_corners[7]);
    dst.push_back(inner_corners[40]);
    dst.push_back(inner_corners[47]);

    vector<Point2f> src;
    src.push_back(cv::Point2f(0, 0));
    src.push_back(cv::Point2f(input_image.cols-1, 0));
    src.push_back(cv::Point2f(0, input_image.rows-1));
    src.push_back(cv::Point2f(input_image.cols-1, input_image.rows-1));
    

    Mat changed=Mat(input_image);
    Mat perspectivetransform=getPerspectiveTransform(src,dst);
    warpPerspective(input_image, changed, perspectivetransform, frame.size());

    Mat mask = changed > 0;
    Mat merged = frame.clone();
    changed.copyTo(merged,mask);
    imshow("new_video", merged);
}

int main(int argc, char *argv[])
{
    CommandLineParser parser(argc, argv, keys);

    if (parser.has("help")) // if the user write help it will print the message
    {
       parser.printMessage();
       return 0;
    }

    /* Parameters to read a video or an image */
    Mat input_image;
    VideoCapture input_cap;
    bool video_flag = false;

    /* Main parameters for the program */
    string vid = parser.get<string>("video");

    VideoCapture cap(vid); // open the default camera

    int rows = parser.get<int>("rows");
    int cols = parser.get<int>("cols");

    double size = parser.get<double>("size");

    string fichero = parser.get<string>("yaml");

    FileStorage fs(fichero,FileStorage::READ);

    Mat video;

    vector<Point2f> inner_corners;
    vector<Point3f> points3D;
    vector<Point3f> axis;

    Mat rvec(3,1,CV_32F);
    Mat tvec(3,1,CV_32F);
    Mat cameraMatrix(3,3,CV_32F);
    Mat distCoeffs(5,1,CV_32F);

    Mat frame, grey_frame, video_frame;
    Size tamano (cols,rows);

  	fs["camera_matrix"] >> cameraMatrix;
  	fs["distortion_coefficients"] >> distCoeffs;

    Size winSize = Size( 2*cols+1, 2*rows+1 );
  	Size zeroZone = Size( -1, -1 );
  	TermCriteria criteria = TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, size );


    /* We are going to check if we put option -i */
    if(parser.has("image"))
    {
        video_flag=false;
        string input = parser.get<string>("image");
        
        // Read the image
        input_image=imread(input,CV_32F);

        // Check if we are reading an image
        if(!input_image.data)
        {
            // If is not an image is because we load a video
            input_cap.open(input);
            video_flag=true;

            if(!input_cap.isOpened())
            {
                return -1;
            }      
        }
    }

    if(!cap.isOpened())
        return -1;

    srand(time(NULL));
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            points3D.push_back(Point3f(j*size,i*size,0));
        }
    }

    axis.push_back(Point3f(0, 0, 0));
    axis.push_back(Point3f(size, 0, 0));
    axis.push_back(Point3f(0, size, 0));
    axis.push_back(Point3f(0, 0, -size));

    for(;;)
    {
        cap >> frame;

        if(!cap.read(frame))
        {
        	break;
        }

        cvtColor(frame, grey_frame, COLOR_BGR2GRAY);
        bool patternfound = findChessboardCorners(grey_frame, tamano, inner_corners);

        if(patternfound && !parser.has("image"))
        {  		
			/// Calculate the refined corner locations
			cornerSubPix(grey_frame, inner_corners, winSize, zeroZone, criteria);

		    solvePnP(points3D, inner_corners, cameraMatrix, distCoeffs, rvec, tvec);

		 	projectPoints(axis, rvec, tvec, cameraMatrix, distCoeffs, inner_corners);

		 	line(frame, inner_corners[0],inner_corners[1],Scalar(0,0,255),6);
		 	line(frame, inner_corners[0],inner_corners[2],Scalar(0,255,0),6);
		 	line(frame, inner_corners[0],inner_corners[3],Scalar(255,0,0),6);
		    
            imshow("video", frame);
        }

        if(parser.has("image"))
        {
            if(!video_flag)
            {
                image_function(frame, input_image, inner_corners);
            }

            else{

                input_cap >> video_frame;

                if(!input_cap.read(video_frame)){
                    break;
                }

                video_function(video_frame, frame, inner_corners);
            }
        }

		if(waitKey(30) >= 0) break;
    }

    return 0;
}