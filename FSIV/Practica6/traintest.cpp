//! \file traintest.cpp
//! \author FSIV

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include "common_code.hpp"
#include "lbp.h"


using namespace std;
using namespace cv;
using namespace cv::ml;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{@train_pos     |<none>| positive samples for training.}"
    "{@train_neg     |<none>| negative samples for training.}"
    "{@test_pos      |<none>| positive samples for testing.}"
    "{@test_neg      |<none>| negative samples for testing.}"
    "{@rows          |  6   | rows for GRID configuration.}"
    "{@cols          |  4   | cols for GRID configuration.}"
    "{C        | 1.0  | margin of the classifier.}"
    "{@degree        | 1.0  | degree for polinomial kernel.}"
    "{@coef0          | 1.0  | coeficient, optional parameter.}"
    "{@gamma          | 1.0  | gamma, optional parameter.}"
    "{notrain        |      | no training a model? Only testing.}"
    "{model          |model_svm.yml| filename for model.}"
    ;

int main(int argc, char * argv[])
{
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Train/test a pedestrian classifier using LBP as feature.");
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    setvbuf(stdout, NULL, _IONBF, 0);

    bool notraining = parser.has("notrain");

    Ptr<SVM> svm;
    Ptr<KNearest> knn;
    int classifier = 0;

    cout << endl;
    cout << "What type of classifier do yo want to use:" << endl;
    cout << endl;
    cout << "\t1 SVM classifier" << endl;
    cout << "\t2 KNN classifier" << endl;
    cout << endl;

    cout << "Introduce the option number of the classifier: ";
    cin >> classifier;

    double margin = parser.get<double>("C");

    //The txt files, refereced tio inria files that are the images

    // Load sample names

    /*
      PARAMETERS
      * lfiles_pos is an string array for the file txt with the positive images that I am going to use to train my system
      * lfiles_neg is an string array for the file txt with the negative images that I am going to use to train my system
      * lfiles_pos_test is an string array for the file txt with the positive images that I am going to use for validation
      * lfiles_neg_test is an string array for the file txt with the negative images that I am going to use for validation
    */

    // I suppose that the variables that ends in path is the path where we can find the images

    std::vector<std::string> lfiles_pos, lfiles_neg, lfiles_pos_test, lfiles_neg_test;
    cv::String filepath, filepath_neg , filepath_pos_test , filepath_neg_test;

    if (notraining) // If im not gonna train my computer i will only use the validation images
    {
    	filepath_pos_test  = parser.get<cv::String>(0);
    	filepath_neg_test  = parser.get<cv::String>(1);
    }
    else // In the oder hand if i am going to train my sytem, I am gonna use all the images that i define in PARAMETERS
    {
    	filepath = parser.get<cv::String>(0);
    	filepath_neg  = parser.get<cv::String>(1);
      filepath_pos_test  = parser.get<cv::String>(2);
      filepath_neg_test  = parser.get<cv::String>(3);
    }


	int retCode = -1;
    if (!notraining) // If im going to train my system
    {
      // Here I load the names of the positive images that im gonna use to train my system
  		retCode = load_filenames_from_txt(filepath, lfiles_pos);
  		if (retCode != 0)
  		{
  			 std::cerr << "Error loading filenames from: " << filepath << std::endl;
  			 exit(-1);
  		}

      // Here I load the names of the negative images that im gonna use to train my system
  		retCode = load_filenames_from_txt(filepath_neg, lfiles_neg);
  		if (retCode != 0)
  		{
  			 std::cerr << "Error loading filenames from: " << filepath_neg << std::endl;
  			 exit(-1);
  		}
	 }

  // Here I load the names of the negative images that I am gonna use for validation
	retCode = load_filenames_from_txt(filepath_neg_test, lfiles_neg_test);
	if (retCode != 0)
	{
		 std::cerr << "Error loading filenames from: " << filepath_neg_test << std::endl;
		 exit(-1);
	}

  // Here I load the names of the positive images that I am gonna use for validation
	retCode = load_filenames_from_txt(filepath_pos_test, lfiles_pos_test);
	if (retCode != 0)
	{
		 std::cerr << "Error loading filenames from: " << filepath_pos_test << std::endl;
		 exit(-1);
	}

   // Here I show the size of the positive and negative samples that I have already load
	 std::cout << lfiles_pos.size() << " positive training samples" << std::endl;
	 std::cout << lfiles_neg.size() << " negative training samples" << std::endl;

	 // Split image into cells to compute LBP full descriptor
	 // /int ncells[] = {6,4}; // Rows x cols // 6x4
   int rows = parser.get<int>(4);
   int cols = parser.get<int>(5);

   cout << endl;
   cout << "Rows = " << rows << endl;
   cout << "Cols = " << cols << endl;
   cout << endl;

   assert(rows > 0 and cols > 0);

   int ncells[] = {rows, cols};
	 cv::Mat train_lbp_pos, train_lbp_neg;

	 /// Training a new model?
   string modelname = parser.get<std::string>("model");

   if (!notraining)
   {
	   /// LBP
	   std::cout << "Computing LBP descriptors for training samples... ";
	   std::vector<float> train_labels_v;
	   int npos = compute_lbp_from_list(lfiles_pos, train_lbp_pos, ncells, true, true);
	   int nneg = compute_lbp_from_list(lfiles_neg, train_lbp_neg, ncells, true, true);

	   std::cout << "done!" << std::endl;

	   for (int i =0; i<npos; i++)
	      train_labels_v.push_back(1);
	   for (int i =0; i<nneg; i++)
	      train_labels_v.push_back(-1);

	   cv::Mat labelsMat(npos+nneg, 1, CV_32SC1);
	   for (int i =0; i < train_labels_v.size(); i++)
	      labelsMat.at<int32_t>(i,0) = train_labels_v[i];

     // Here you create an image from a previous vector
	   cv::Mat train_labels(train_labels_v);

     // cv::Mat train_lbp(Size((train_lbp_pos.rows+train_lbp_neg.rows),1),CV_32FC1);
     cv::Mat train_lbp;

     // Here we applies vertical concatenation to given matrices
     // The function vertically concatenates two or more cv::Mat matrices (with the same number of cols)
	   cv::vconcat(train_lbp_pos, train_lbp_neg, train_lbp);

     if (classifier == 1)
     {
       cout << endl;
       cout << "You select SVM classifier" << endl;
       cout << endl;

       int kernel = 0;

       cout << endl;
       cout << "KERNELS:" << endl;
       cout << endl;

       cout << "\t0 LINEAR" << endl;
       cout << "\t1 POLY" << endl;
       cout << "\t2 RBF" << endl;
       cout << "\t3 SIGMOID" << endl;
       cout << "\t4 CHI2" << endl;
       cout << "\t5 INTER" << endl;
       cout << endl;

       cout << "Introduce the number of the option: ";
       cin >> kernel;

       if (kernel == 0) cout << "You select the LINEAR kernel" << endl;
       if (kernel == 1) cout << "You select the POLY kernel" << endl;
       if (kernel == 2) cout << "You select the RBF kernel" << endl;
       if (kernel == 3) cout << "You select the SIGMOID kernel" << endl;
       if (kernel == 4) cout << "You select the CHI2 kernel" << endl;
       if (kernel == 5) cout << "You select the INTER kernel" << endl;
       cout << endl;

       // My classifier is goind to be a SVM (Support Vector Machines)
       svm = SVM::create();

       // Here we stablish the type of SVM
       svm->setType(SVM::C_SVC);

       // Here we stablish the margin that by defect is 1.0
       svm->setC(margin);

       // Initialize with one of predefined kernels, in that case I inicilize it with a LINEAR
       svm->setKernel(kernel);
       svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));

       svm->setDegree(parser.get<double>("@degree"));

       //	Optional parameters for some kernels. If the user don't give any value, the value will be set by default.
       svm->setGamma(parser.get<double>("@gamma"));
       svm->setCoef0(parser.get<double>("@coef0"));

       CV_Assert(train_lbp.type()==CV_32FC1);

       std::cout << "Starting training ...";

       // TODO: Start training
       // ...

       // le pasamos el conjunto de imagenes provesadas con el descriptor lbp con el que queremos entrenar el sistema
       // ponemos ROW_SAMPLE literalmente
       // le pasamos las etiquetas
       svm->train(train_lbp, ROW_SAMPLE, labelsMat);

       std::cout << "Trained" << std::endl;

       // TODO: Save model to disk
       // ...
       // Whith that option the program automatically save a file .yml that is going to be your model even if you write a name or not
       svm->save(modelname);
     }

     if (classifier == 2)
     {
       cout << endl;
       cout << "You select KNN classifier" << endl;
       cout << endl;

       // Here we create our KNN classifier
       knn = KNearest::create();

       // Here we train our KNN classifier
       knn->train(train_lbp, ROW_SAMPLE, labelsMat);

       knn->save(modelname);
     }

	}
	else
	{
		// TODO: load existing model
		// ...
    if(classifier == 1)
    {
      cout << "You select SVM classifier" << endl;
      svm = SVM::create();
      svm = SVM::load(modelname);
    }

    if(classifier == 2)
    {
      cout << "You select KNN classifier" << endl;
      knn = KNearest::create();
      knn = KNearest::load(modelname);
    }
    //svm->load(modelname);
		std::cout << "+ Model loaded from: " << modelname << std::endl;
	}


   /// Test time!
   cv::Mat test_lbp_pos, test_lbp_neg;
   std::cout << "Computing LBP on test samples..." << std::endl;
   int npos_test = compute_lbp_from_list(lfiles_pos_test, test_lbp_pos, ncells, true, true);
   int nneg_test = compute_lbp_from_list(lfiles_neg_test, test_lbp_neg, ncells, true, true);

   cv::Mat predictions_pos, predictions_neg, predictions_pos_raw, predictions_neg_raw;

   // TODO: run the trained model on the LBP descriptors, positive and negative samples
   // ...

   if(classifier == 1)
   {
     svm->predict(test_lbp_pos, predictions_pos);
     svm->predict(test_lbp_neg, predictions_neg);
   }

   if(classifier == 2)
   {
     int k;

     cout << endl;
     cout << "How many points to your Knn classifier: ";
     cin >> k;
     cout << endl;

     knn->findNearest(test_lbp_pos, k, predictions_pos);
     knn->findNearest(test_lbp_neg, k, predictions_neg);
   }

	std::cout << "Test done!" << std::endl;

	cv::Mat true_labels(npos_test+nneg_test, 1, CV_32F);
	cv::Mat predicted_labels(npos_test+nneg_test, 1, CV_32F);

	for (int i = 0; i < npos_test; i++)
	{
		true_labels.at<float>(i,0) = +1;
		predicted_labels.at<float>(i,0) = MAX(0, predictions_pos.at<float>(i,0));
	}

	for (int i = 0; i < nneg_test; i++)
	{
		true_labels.at<float>(npos_test+i,0) = 0;
		predicted_labels.at<float>(npos_test+i,0) = MAX(0, predictions_neg.at<float>(i,0));
	}

	// Some statistics about performance
	cv::Mat CM = compute_confusion_matrix(2, true_labels, predicted_labels);

	std::cout << CM << std::endl;

    double mean, dev;
	compute_recognition_rate(CM, mean, dev);

	std::cout << "Accuracy: " << mean << " (" << dev << ")" << std::endl;

	std::cout << "End! " <<std::endl;

   return 0;
}
