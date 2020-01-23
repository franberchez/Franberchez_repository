//! \file lbp.cpp
//! Utils for LBP

#include "lbp.h"
#include <vector>

using namespace std;
using namespace cv;


void fsiv_lbp(const cv::Mat & imagem, cv::Mat & lbp)
{
	lbp = imagem.clone();
	//lbp=Mat::zeros(imagem.size(), imagem.type());

	for (int i = 0; i < imagem.rows; i++)
	{
		for (int j = 0; j < imagem.cols; j++)
		{
			if (i < 1 || j < 1 || (j + 1)>=imagem.cols || (i + 1)>=imagem.rows)
			{
				lbp.at<uchar>(i,j)=imagem.at<uchar>(i,j);
			}

			else
			{
				unsigned char anumber = 0;
				if(imagem.at<uchar>(i-1,j-1) > imagem.at<uchar>(i,j)) {anumber = anumber | (1<<7);}

				if(imagem.at<uchar>(i-1,j) > imagem.at<uchar>(i,j)) {anumber = anumber | (1<<6);}

				if(imagem.at<uchar>(i-1, j+1) > imagem.at<uchar>(i,j)) {anumber = anumber | (1<<5);}

				if(imagem.at<uchar>(i, j+1) > imagem.at<uchar>(i,j)) {anumber = anumber | (1<<4);}

				if(imagem.at<uchar>(i+1, j+1) > imagem.at<uchar>(i,j)) {anumber = anumber | (1<<3);}

				if(imagem.at<uchar>(i+1, j) > imagem.at<uchar>(i,j)) {anumber = anumber | (1<<2);}

				if(imagem.at<uchar>(i+1, j-1) > imagem.at<uchar>(i,j)) {anumber = anumber | (1<<1);}

				if(imagem.at<uchar>(i, j-1) > imagem.at<uchar>(i,j)) {anumber = anumber | (1<<0);}

				lbp.at<uchar>(i,j)=anumber;
			}

		}
	}
}

void fsiv_lbp_hist(const cv::Mat & lbp, cv::Mat & lbp_hist, bool normalize)
{
	// We are going to use the function calcHist()

	int histSize[] = {256};

	// Saturation varies from 0 to 255
	float sranges[] = {0, 256};
	const float* ranges[] = {sranges};

	// We compute the histogram from the 0-th and 1-st channels
	int channels[] = {0};

	calcHist(&lbp, 1, channels, Mat(), lbp_hist, 1, histSize, ranges, true);

	if(normalize == true)
	{
		int total_pixels = lbp.rows * lbp.cols;
		for (int i = 0; i < 256; i++)
		{
			lbp_hist.at<float>(0, i) = lbp_hist.at<float>(0, i)/total_pixels;
		}
	}

	transpose(lbp_hist, lbp_hist);
}

void fsiv_lbp_desc(const cv::Mat & image, cv::Mat & lbp_desc, const int *ncells, bool normalize, bool asrows)
{
	vector<Mat> histograms;

	lbp_desc = Mat::zeros(Size(ncells[0]*ncells[1], 1), image.type());

	int height = image.rows / ncells[0];
	int width = image.cols / ncells[1];

	Mat lbp_region = Mat::zeros(Size(height, width), image.type());
	Mat lbp_region_hist = Mat::zeros(Size(height, width), image.type());

	//fsiv_lbp_disp(image, "Image");

	for (int i = 0; i < height*ncells[0]; i=i+height)
	{
		for (int j = 0; j < width*ncells[1]; j=j+width)
		{
			Rect r(j, i, width, height);
			Mat region = image(r);

			//fsiv_lbp_disp(region, "region");

			fsiv_lbp(region, lbp_region);
			fsiv_lbp_hist(lbp_region, lbp_region_hist, true);
			histograms.push_back(lbp_region_hist);
		}

	}

	hconcat(histograms, lbp_desc);
}

void fsiv_lbp_disp(const cv::Mat & lbpmat, const std::string & winname)
{
	namedWindow(winname);
	imshow(winname, lbpmat);

	waitKey(0);
}

float fsiv_chisquared_dist(const cv::Mat & h1, const cv::Mat & h2)
{
	float sum = 0;
	float div = 0;

	for (int i = 0; i<h1.cols; i++)
	{
		if ( (h1.at<float>(0,i) + h2.at<float>(0,i)) != 0 )
		{
				sum += pow( (h1.at<float>(0,i) - h2.at<float>(0,i)), 2) / (h1.at<float>(0,i) + h2.at<float>(0,i));
		}

		else
		{
			sum = 0.000000000000000000000001;
		}
	}

	div = 0.5 * sum;

	return div;
}


void fsiv_detect_pyr(const cv::Mat & image, const cv::Ptr<SVM> & svm, const int *winsize, int stride, int * ncells, int nlevels, float factor, float thr_det, std::vector<cv::Rect> & lRs, std::vector<float> & lscores)
{
	Mat image2 = image.clone();

	for (int i = 0; i < nlevels; i++)
	{
		Mat lbp_desc;

		if(i!=0)
		{
			Size new_size=image2.size();
			new_size.height = new_size.height*factor;
			new_size.width = new_size.width*factor;
			//new_size.height = new_size.height/factor;
			//new_size.width = new_size.width/factor;
			resize(image2, image2, new_size);
		}

		for (int j = 0; j < image2.rows-winsize[0]; j+=stride)
  		{
			for (int z = 0; z < image2.cols-winsize[1]; z+=stride)
			{
				// To have the rectangle that is to travel all the image
				Rect r(z, j, winsize[1], winsize[0]);
				Mat roi = image2(r);
				fsiv_lbp_desc(roi, lbp_desc, ncells);

				Mat prediction;
				svm->predict(lbp_desc, prediction, true);

				if (prediction.at<float>(0, 0) >= thr_det)
				{
					if(i==0)
					{
						lRs.push_back(r);
						lscores.push_back(prediction.at<float>(0, 0));
					}

					else
					{
						Rect r(z/pow(factor,i), j/pow(factor,i), winsize[1]/pow(factor,i), winsize[0]/pow(factor,i));
						// Rect r(z*pow(factor,i), j*pow(factor,i), winsize[1]*pow(factor,i), winsize[0]*pow(factor,i));
						lRs.push_back(r);
						lscores.push_back(prediction.at<float>(0, 0));
					}
				}
			}
		}
		//pyrDown(image2, image2, Size(image2.cols/factor, image2.rows/factor));
	}
}
