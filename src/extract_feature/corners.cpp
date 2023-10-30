#include <iostream>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("../../../images/building.jpg", IMREAD_GRAYSCALE);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    //good feature to track
    vector<Point2f> corners;
    goodFeaturesToTrack(src, corners, 400, 0.1, 10);

    Mat dst1;
    cvtColor(src, dst1, COLOR_GRAY2BGR);

    for(size_t i = 0; i < corners.size(); i++){
        circle(dst1, corners[i], 5, Scalar(0,0,255), 2);
    }

    //Fast
    vector<KeyPoint> keypoints;
    FAST(src, keypoints, 60, true);

    Mat dst2;
    cvtColor(src, dst2, COLOR_GRAY2BGR);

    for(const KeyPoint &kp : keypoints){
        circle(dst2, Point(kp.pt.x, kp.pt.y), 5, Scalar(0,0,255), 2);
    }

    imshow("dst1", dst1);
    imshow("dst2", dst2);

    while(1){
        if(waitKey() == 27) break;
    }

}