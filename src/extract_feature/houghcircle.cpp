#include <iostream>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("../../../images/coins.jpg", IMREAD_GRAYSCALE);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    Mat dst1, dst2;
    cvtColor(src, dst1, COLOR_GRAY2BGR);
    cvtColor(src, dst2, COLOR_GRAY2BGR);

    //HOUGH_GRADIENT
    Mat blr;
    GaussianBlur(src, blr, Size(), 1.0);

    vector<Vec3f> circles1;
    HoughCircles(blr, circles1, HOUGH_GRADIENT, 1, 10, 150, 30, 10, 50);

    for(size_t i = 0; i < circles1.size(); i++){
        Vec3i c = circles1[i];
        circle(dst1, Point(c[0], c[1]), c[2], Scalar(0,0,255), 2, LINE_AA);
    }

    //HOUGH_GRADIENT_ALT
    vector<Vec3f> circles2;
    HoughCircles(src, circles2, HOUGH_GRADIENT_ALT, 1.5, 10, 300, 0.9, 10, 50);

    for(size_t i = 0; i < circles2.size(); i++){
        Vec3i c = circles2[i];
        circle(dst2, Point(c[0], c[1]), c[2], Scalar(0,0,255), 2, LINE_AA);
    }

    imshow("src", src);
    imshow("dst1", dst1);
    imshow("dst2", dst2);

    while(1){
        if(waitKey() == 27) break;
    }
}