#include <iostream>
#include <algorithm>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("../../../images/lenna.bmp", IMREAD_GRAYSCALE);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    Mat dx, dy, mag;
    Sobel(src, dx, CV_32F, 1, 0);
    Sobel(src, dy, CV_32F, 0, 1);

    magnitude(dx, dy, mag);
    mag.convertTo(mag, CV_8UC1);

    Mat dst = mag > 120;

    imshow("src", src);
    imshow("mag", mag);
    imshow("dst", dst);


    /*
    Mat dx = Mat::zeros(src.rows, src.cols, CV_8UC1);
    Mat dy = Mat::zeros(src.rows, src.cols, CV_8UC1);
    Mat mag = Mat::zeros(src.rows, src.cols, CV_8UC1);

    for(int y = 1; y < src.rows - 1; y++){
        for(int x = 1; x < src.cols - 1; x++){
            int v1 = src.at<uchar>(y - 1, x + 1)
                + src.at<uchar>(y, x + 1) * 2
                + src.at<uchar>(y + 1, x + 1)
                - src.at<uchar>(y - 1, x - 1)
                - src.at<uchar>(y, x - 1) * 2
                - src.at<uchar>(y + 1, x - 1);

            int v2 = src.at<uchar>(y + 1, x + 1)
                + src.at<uchar>(y + 1, x + 1) * 2
                + src.at<uchar>(y + 1, x - 1)
                - src.at<uchar>(y - 1, x - 1)
                - src.at<uchar>(y - 1, x) * 2
                - src.at<uchar>(y - 1, x + 1);

            dx.at<uchar>(y,x) = saturate_cast<uchar>(v1+128);
            dy.at<uchar>(y,x) = saturate_cast<uchar>(v2+128);
            mag.at<uchar>(y, x) = saturate_cast<uchar>(sqrt(v1 * v1 + v2 * v2));

        }
    }

    Mat dst = mag > 150;

    imshow("src", src);
    // imshow("dx", dx);
    // imshow("dy", dy);
    imshow("mag", mag);
    imshow("dst",dst);
    */

    while(1){
        if(waitKey() == 27) break;
    }
}

