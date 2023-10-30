#include <iostream>
#include <opencv2/core/base.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("../../../images/tekapo.bmp");
    if(src.empty()){
        cerr <<"image load failed!!" << endl;
        return -1;
    }

    int w = src.cols;
    int h = src.rows;

    Mat map1 = Mat::zeros(h, w, CV_32FC1);
    Mat map2 = Mat::zeros(h, w, CV_32FC1);

    for(int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            map1.at<float>(y,x) = x;
            // map2.at<float>(y,x) = y;
            // map2.at<float>(y, x) = h - 1 -y;
            map2.at<float>(y,x) = y + 10 * sin(x / 32.f);
         }
    }

    Mat dst;
    // remap(src, dst, map1, map2, INTER_LINEAR);
    remap(src, dst, map1, map2, INTER_LINEAR, BORDER_DEFAULT);
    imshow("src", src);
    imshow("dst", dst);

    while(1){
        if(waitKey()==27) break;
    }
}
