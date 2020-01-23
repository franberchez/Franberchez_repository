//! \file test_lbp.cpp
//! \author FSIV-UCO

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "lbp.h"

using namespace std;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{@image         |<none>| path to input image.}"
    "{image2         |      | path to second image, for comparison.}"
    "{u              |      | create uniform lbp.}"
    ;

int main(int argc, char * argv[])
{
   cv::CommandLineParser parser(argc, argv, keys);
   parser.about("Test LBP implementation.");
   if (parser.has("help"))
   {
      parser.printMessage();
      return 0;
   }

   setvbuf(stdout, NULL, _IONBF, 0);

   /// Load the image
   cv::Mat image;
   image = imread(parser.get<string>("@image"), CV_8UC1);

   /// Compute LBP matrix
   cv::Mat lbpmat;
   fsiv_lbp(image, lbpmat);

   // Display LBP image
   fsiv_lbp_disp(lbpmat, "LBP image");

   /// Save LBP image to disk
   // TODO

   /// Compute the LBP histogram
   cv::Mat lbp_h1;
   fsiv_lbp_hist(lbpmat, lbp_h1, true); // that histogram is completed directly given the matrix

   // assert(cv::sum(lbp_h1.sum) == 1.0)

   /// Compute the Chi^2 distance between the input image and its mirror
   if (parser.has("image2"))
   {
      cv::Mat lbp_h2;
      cv::Mat image_2;
      cv::Mat lbpmat_2;

      image_2 = imread(parser.get<string>("image2"), CV_8UC1);

      fsiv_lbp(image_2, lbpmat_2);
      fsiv_lbp_disp(lbpmat_2, "LBP image");
      fsiv_lbp_hist(lbpmat_2, lbp_h2, true);

      float dist = fsiv_chisquared_dist(lbp_h1, lbp_h2);

      // Show distance
      cout << "The distance is = " << dist << endl;
   }

   int rows, cols;
   int ncells[2];

   Mat lbp_desc;

   cout << "Introduce the number of rows: ";
   cin >> rows;

   cout << "Introduce the number of column: ";
   cin >> cols;

   ncells[0] = rows;
   ncells[1] = cols;

   fsiv_lbp_desc(image, lbp_desc, ncells, true);

   if (parser.has("u"))
   {
     cv::Mat ulbpmat;
     fsiv_ulbp(image, ulbpmat);
   }


   std::cout << "End! " <<std::endl;

   return 0;
}
