#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void split_bgr();
void split_hsv();
void split_ycrcb();


int main()
{
    // split_bgr();
    // split_hsv();
    split_ycrcb();
}


void split_bgr()
{
    string fp = "../../../images/candies.png";
    Mat src = imread(fp, IMREAD_COLOR);
    resize(src, src, Size(src.cols/2,src.rows/2));

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return;
    }
    vector<Mat> ycrcb_planes;
    split(src, ycrcb_planes);

    imshow("src", src);
    imshow("B plane", ycrcb_planes[0]);
    imshow("G plane", ycrcb_planes[1]);
    imshow("R plane", ycrcb_planes[2]);

    while(1){
        if(waitKey() == 27) break;
    }
}

void split_hsv()
{
    string fp = "../../../images/candies.png";
    Mat src = imread(fp, IMREAD_COLOR);
    resize(src, src, Size(src.cols/2,src.rows/2));

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return;
    }

    Mat src_hsv;
    cvtColor(src, src_hsv, COLOR_BGR2HSV);


    vector<Mat> ycrcb_planes;
    split(src_hsv, ycrcb_planes);

    imshow("src", src);
    imshow("H plane", ycrcb_planes[0]);
    imshow("S plane", ycrcb_planes[1]);
    imshow("V plane", ycrcb_planes[2]);

    while(1){
        if(waitKey() == 27) break;
    }
}


void split_ycrcb()
{
    string fp = "../../../images/candies.png";
    Mat src = imread(fp, IMREAD_COLOR);
    resize(src, src, Size(src.cols/2,src.rows/2));

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return;
    }

    Mat src_ycrcb;
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);


    vector<Mat> ycrcb_planes;
    split(src_ycrcb, ycrcb_planes);

    imshow("src", src);
    imshow("Y plane", ycrcb_planes[0]);
    imshow("Cr plane", ycrcb_planes[1]);
    imshow("Cb plane", ycrcb_planes[2]);

    while(1){
        if(waitKey() == 27) break;
    }
}