//
//  main.cpp
//  BSPL_Image_Analysis
//
//  Created by Alice Fockele - July 2017.
//


#include "functions.h"

using namespace std;
using namespace cv;

Mat org;
vector<Vec4i> hough_lines;


int sensorCount = 24;

//int min_threshold = 20; //hough
//int max_trackbar = 40; //hough
//int p_trackbar = max_trackbar;//hough




int main(int argc, const char * argv[]) {
    org = imread("../../../filtered_1pixel.png",0); //read in the source image
    
    cout << "Original Size: " << org.size() << endl;
    

//---------------------------------MEAN DENOISE-----------------------------------------//
    
    Mat denoise;
    fastNlMeansDenoising(org, denoise,10,9,15);


//----------------------------HOUGH TRANSFORM------------------------------------------//
    

    hough_lines = Probabilistic_Hough(0, denoise);
    cout << "Number of Hough Lines: " << hough_lines.size() << endl;

    
//    Mat temp1, temp2;
//    vector<Point> features;
//    for( size_t i = 0; i < hough_lines.size(); i++ )
//    {
//        Vec4i l = hough_lines[i];
//        temp1.push_back(l[0]);
//        temp2.push_back(l[1]);
//        features.push_back(Point(l[0],l[1]));
//        cout << " | values: " << l[0] <<" and " << l[1] <<" | " << l[2] << " and " << l[3] << endl;
//    }
    
    
//    cout << "test: " << hough_lines[1][0] << endl;

//----------------------------DRAW HOUGH LINES-----------------------------------------//
    
    Mat img_hough(denoise.rows,denoise.cols,CV_8UC3,Scalar(0,0,0));
    Mat denoise_hough = denoise.clone(); //(denoise.rows,denoise.cols,CV_8UC3);
    cvtColor(denoise_hough, denoise_hough, COLOR_GRAY2BGR);
//    cvtColor(resized, resized, COLOR_GRAY2BGR );

    for( size_t i = 0; i< hough_lines.size(); i++)
    {
        int a = hough_lines[i][0];
//        int a = hough_lines[i][1];
//        int b = hough_lines[i][3];
        for(int b = hough_lines[i][3]; b < hough_lines[i][1]; b++)
        {
            cout << "b index: " << b << endl;
            denoise_hough.at<Vec3b>(b,a) = 0;
            denoise_hough.at<Vec3b>(b,a).val[0]=255;
            img_hough.at<Vec3b>(b,a).val[0] = 255;
            
        }
//        for(a = hough_lines[i][0]*20; a < (hough_lines[i][0]+1)*20;a++)
//            for(int b = hough_lines[i][3]; b < hough_lines[i][1]; b++)
//            {
//                resized.at<Vec3b>(b,a) = 0;
//                resized.at<Vec3b>(b,a).val[0]=255;
//            }
    }

        
//    for( size_t i = 0; i < hough_lines.size(); i++ )
//    {
//        Vec4i l = hough_lines[i];
//        line(resized, Point(l[0]*20+5, l[1]), Point(l[2]*20+5, l[3]), Scalar(255,0,0), 3, LINE_AA);
//    }

    
    //---------------------------ORGANIZE COLUMNS INTO LIST---------------------------------//
    
    vector<Mat> col_lst;
    int colPixel = denoise_hough.cols / sensorCount;
    for (int j = 0; j<denoise_hough.cols; j = j+colPixel) {
        col_lst.push_back(denoise_hough.colRange(j,j+colPixel));
    }
    
    cout << "List Length: " << col_lst.size() << endl;
    cout << "Column Size : " << col_lst[23].size() << endl;
    
    
    
    //----------------------------RESIZE IMAGE---------------------------------------------//
    
    
    for (int j = 0; j<sensorCount;j++){
        resize(col_lst[j], col_lst[j], Size(20,col_lst[j].rows),INTER_NEAREST);
    }
    Mat resized;
    hconcat(col_lst,resized);
    
//// START CLUSTERING ?!?!


    
// MEAN-SHIFT CLUSTERING
    denoise_hough.convertTo(denoise_hough, CV_8UC3);
    Mat denoise_clustered;
    double spatialRadius = 4;
    double colorRadius = 1;
    int maxLevel = 3;
    pyrMeanShiftFiltering(denoise_hough, denoise_clustered, spatialRadius, colorRadius, maxLevel, TermCriteria(TermCriteria::MAX_ITER+TermCriteria::EPS,5,1) );
    imshow("Clustered?",denoise_clustered);
    
// HIERARCHICAL CLUSTERING

//    Mat mergedFeatures(int(features.size()), 2, CV_32F);
//    hconcat(temp1, temp2, mergedFeatures);
//    cout << "Features: " << mergedFeatures.size() << endl << features << endl;
//    Mat centers(100, 2, CV_32F);
//    cvflann::KMeansIndexParams kmeans_param;
//    int numClusters = flann::hierarchicalClustering<flann::L2<float>>(mergedFeatures, centers, kmeans_param);
//    cvflann::KMeansIndexParams k_params = cvflann::KMeansIndexParams();
//    cvflann::AutotunedIndexParams atp = cvflann::AutotunedIndexParams();
//    int numClusters = cvflann::hierarchicalClustering(features, centers, k_params, 20);
//    int numClusters = cv::flann::hierarchicalClustering(mergedFeatures, centers, k_params)
//    cout << "Number of Clusters: " << numClusters << endl;


    
//-----------------------------------DISPLAY-------------------------------------------//

    
    imshow("Original", org);
    imshow("Denoise - Without IsolateNoise()",denoise);
//    imwrite("hough_probabilistic_output.png",resized);
    imshow("Resized", resized);
    imshow("Denoise - with Hough", denoise_hough);
    
    waitKey();
    return(0);
}

