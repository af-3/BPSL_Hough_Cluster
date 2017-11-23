//
//  functions.h
//  BSPL_Image_Analysis
//
//  Created by Alice Fockele on 11/3/17.
//  Copyright © 2017 Alice Fockele. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/flann/flann.hpp>

using namespace std;
using namespace cv;


Mat closeImage(Mat img,int x,int y){
    Mat kernel = Mat::ones(x,y,CV_8U);
    Mat dst;
    dilate(img, dst, kernel,Point(-1,-1), 1);
    erode(dst, dst, kernel, Point(-1,-1), 1);
    return dst;
}

vector<Vec4i> Probabilistic_Hough(int, Mat grey_clean) // from opencv samples
{
    vector<Vec4i> p_lines;
    Mat edges,probabilistic_hough;

    threshold(grey_clean, edges, 50, 255, THRESH_BINARY);
    cvtColor( edges, probabilistic_hough, COLOR_GRAY2BGR );
    
    /// 2. Use Probabilistic Hough Transform
    
    HoughLinesP( edges, p_lines, 1, CV_PI, 50, 30, 50);
    
//    imshow("Edges used in Hough", edges);
    
//    /// Show the result
//    for( size_t i = 0; i < p_lines.size(); i++ )
//    {
//        Vec4i l = p_lines[i];
//        //        cout << "points: (" <<l[0]<<" , "<<l[1] << ") & (" <<l[2]<<" , "<<l[3] << ")"<< endl;
//        line( probabilistic_hough, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
//    }
//    
    return p_lines;
}

//void contours(Mat img, Mat drawing)
//{
//    RNG rng(12345);//contour
//    Mat edges;
//    int low_thresh = 20;
//    vector<vector<Point> > contours;
//    vector<Vec4i> hierarchy;
//    
//    /// Detect edges using Threshold
//    Canny( img, edges, low_thresh, low_thresh*3 , 3 );
//    
//    /// Find contours
//    findContours( edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
//    
//    /// Find the convex hull object for each contour
//    vector<vector<Point> >hull( contours.size() );
//    for( size_t i = 0; i < contours.size(); i++ )
//    {   convexHull( Mat(contours[i]), hull[i], false ); }
//    
//    /// Draw contours + hull results
//    vector<vector<Point> > contours_poly( contours.size() );
//    vector<Rect> boundRect( contours.size() );
//    drawing = Mat::zeros( edges.size(), CV_8UC3 );
//    for( size_t i = 0; i< contours.size(); i++ )
//    {
//        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
//        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
//        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//        //        Scalar color = Scalar(159,176,113);
//        drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
//        rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
//        //        drawContours( drawing, hull, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
//    }
//    
//    /// Show in a window
//    //    namedWindow( "Hull demo", WINDOW_AUTOSIZE );
//    imshow( "Hull demo", drawing );
//}


//    rotate(grey_clean, grey_clean, ROTATE_90_CLOCKWISE);
//    circle(org, seedL, 20, Scalar(0,0,0),2);
//    circle(org, seedR, 20, Scalar(0,0,0),2);
//    inRange(org, Scalar(0,0,10), Scalar(255,255,255), org_thresh);


#endif /* functions_h */
