#include <iostream>
#include "opencv2/core/ocl.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    ocl::setUseOpenCL(false);

    string filepath = "/home/nahye/coding/computer_vision/images/lenna.bmp";
    Mat src = imread(filepath, IMREAD_GRAYSCALE);

    if (src.empty()){
        cerr << "Image load failed!" << endl;
        return -1;
    }

    //create detector
    // Ptr<SIFT> detector = SIFT::create();
    // Ptr<KAZE> detector = KAZE::create();
    // Ptr<ORB> detector = ORB::create();
    // Ptr<AKAZE> detector = AKAZE::create();
    Ptr<Feature2D> detector = SIFT::create();


    TickMeter tm;
    tm.start();

    //detect keypoints
    vector<KeyPoint> keypoints;
    detector->detect(src, keypoints);

    tm.stop();

    cout << keypoints.size() << endl;
    cout << "time: " << tm.getTimeMilli() << endl;

    //compute feature vector
    Mat desc;
    detector->compute(src, keypoints, desc);
    cout << desc.size() << endl; //[width, height]

    //draw keypoints
    Mat dst;
    // drawKeypoints(src, keypoints, dst);
    drawKeypoints(src, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    imshow("src", src);
    imshow("dst", dst);

    while(true){
        if(waitKey()==27) break;
    }
}