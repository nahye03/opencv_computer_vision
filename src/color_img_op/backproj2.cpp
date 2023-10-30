#include <iostream>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat ref, ref_ycrcb, mask;
    ref = imread("../../../images/ref.png", IMREAD_COLOR);
    mask = imread("../../../images/mask.bmp", IMREAD_GRAYSCALE);
    cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

    Mat hist;
    int channels[] = {1, 2}; //cr, cb
    int cr_bins = 128, cb_bins = 128; //originally 256 but want to make more simple so 128
    int histSize[] = {cr_bins, cb_bins};
    float cr_range[] = {0, 256};
    float cb_range[] = {0, 256};
    const float* ranges[] = {cr_range, cb_range};

    calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

#if 0
//show histogram
    Mat hist_norm;
    normalize(hist, hist_norm, 0, 255, NORM_MINMAX, CV_8UC1);
    imshow("hist_norm", hist_norm);
#else

    Mat src, src_ycrcb;
    src = imread("../../../images/kids.png", IMREAD_COLOR);
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

    Mat backproj;
    calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges);

    GaussianBlur(backproj, backproj, Size(), 1.0); //remove noise
    backproj = backproj > 50;

    Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);
    src.copyTo(dst, backproj);

#endif

    imshow("ref", ref);
    imshow("mask", mask);
    imshow("src", src);
    imshow("backproj", backproj);
    imshow("dst", dst);

    while(1){
        if(waitKey() == 27) break;
    }
}