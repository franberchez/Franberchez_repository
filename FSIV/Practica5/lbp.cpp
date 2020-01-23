//! \file lbp.cpp
//! Utils for LBP

#include "lbp.h"
#include <vector>

using namespace std;


void fsiv_lbp(const cv::Mat & imagem, cv::Mat & lbp)
{
	lbp = imagem.clone();

	for (int i = 0; i < imagem.rows; i++)
	{
		for (int j = 0; j < imagem.cols; j++)
		{
			if (i < 1 || j < 1 || (j + 1)>=imagem.cols || (i + 1)>=imagem.rows)
			{
				lbp.at<uchar>(i,j)=0.0;
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

	// La funcion para calcular el histograma de la imagen
	calcHist(&lbp, 1, channels, Mat(), lbp_hist, 1, histSize, ranges, true);

	if(normalize == true)
	{
		int total_pixels = lbp.rows * lbp.cols;
		for (int i = 0; i < 256; i++)
		{
			lbp_hist.at<float>(0, i) = lbp_hist.at<float>(0, i)/total_pixels;
		}
	}

	// Para hacer la traspuesta de la normalizacion y hacer que todo salga bien
	transpose(lbp_hist, lbp_hist);
}

void fsiv_lbp_desc(const cv::Mat & image, cv::Mat & lbp_desc, const int *ncells, bool normalize, bool asrows)
{
	// Creamos el vector de Mat para los histogramas y asi poder obtener el descriptor lbp
	vector<Mat> histograms;

	// En size determino que el numero de columnas es el numero de filas por el numero de columnas que he introducido por teclado y de una sola fila
	lbp_desc = Mat::zeros(Size(ncells[0]*ncells[1], 1), image.type());

	// height es la altura y se refiere al numero de filas que tiene y tiene sentido que lo divida entre el numero de filas que introduzco por teclado
	// ya que es de lo que quiero hacer el split
	int height = image.rows / ncells[0];

	// Con el width o el ancho ocurre lo mismo
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

void fsiv_ulbp(const cv::Mat & imagem, cv::Mat & ulbpmat)
{
	Mat lbp_mat;
	int value;

	static int uniform[256] =
	{
	0,1,2,3,4,58,5,6,7,58,58,58,8,58,9,10,11,58,58,58,58,58,58,58,12,58,58,58,13,58,
	14,15,16,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,17,58,58,58,58,58,58,58,18,
	58,58,58,19,58,20,21,22,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,
	58,58,58,58,58,58,58,58,58,58,58,58,23,58,58,58,58,58,58,58,58,58,58,58,58,58,
	58,58,24,58,58,58,58,58,58,58,25,58,58,58,26,58,27,28,29,30,58,31,58,58,58,32,58,
	58,58,58,58,58,58,33,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,34,58,58,58,58,
	58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,
	58,35,36,37,58,38,58,58,58,39,58,58,58,58,58,58,58,40,58,58,58,58,58,58,58,58,58,
	58,58,58,58,58,58,41,42,43,58,44,58,58,58,45,58,58,58,58,58,58,58,46,47,48,58,49,
	58,58,58,50,51,52,58,53,54,55,56,57
	};

	fsiv_lbp(imagem, lbp_mat);
	ulbpmat = lbp_mat.clone();


	for (int i = 0; i < ulbpmat.rows; i++)
	{
		for (int j = 0; j < ulbpmat.cols; j++)
		{
			value = (int)ulbpmat.at<uchar>(i,j);
			ulbpmat.at<uchar>(i,j) = uniform[value];
		}
	}

	fsiv_lbp_disp(lbp_mat, "LBP_matrix");
	fsiv_lbp_disp(ulbpmat, "ULBP_matrix");
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
