#include <iostream>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("../../../images/circuit2.bmp", cv::IMREAD_GRAYSCALE);
    Mat tmp1 = imread("../../../images/crystal.bmp", IMREAD_GRAYSCALE);

    if(src.empty() || tmp1.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

#if 1
    //src + noise
    src = src + 50;
    Mat noise(src.size(), CV_32S);
    randn(noise, 0, 10);
    add(src, noise, src, noArray(), CV_8U);
#endif

#if 0
    GaussianBlur(src, src, Size(), 1);
    GaussianBlur(tmp1, tmp1, Size(), 1);
#endif

#if 0
    resize(src, src, Size(), 0.9, 0.9);
#endif

#if 1
    Point2f cp(src.cols / 2.f, src.rows / 2.f);
    Mat rot = getRotationMatrix2D(cp, 10, 1);
    warpAffine(src, src, rot, src.size());
#endif


    Mat res, res_norm;
    matchTemplate(src, tmp1, res, TM_CCOEFF_NORMED);
    normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);

    double maxv;
    Point maxloc;
    minMaxLoc(res, 0, &maxv, 0, &maxloc);

    cout << "maxv: " << maxv << endl;
    cout << "maxloc: " << maxloc << endl;

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    rectangle(dst, Rect(maxloc.x, maxloc.y, tmp1.cols, tmp1.rows), Scalar(0,0,255), 2);

    imshow("tmp1", tmp1);
    imshow("res_norm", res_norm);
    imshow("dst", dst);

    while(1){
        if(waitKey() == 27) break;
    }
     
}
