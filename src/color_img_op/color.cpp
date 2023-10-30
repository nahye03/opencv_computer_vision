#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

#define RGB2GRAY(r, g, b) ((4899*(r) + 9617*(g) + 1868*(b)) >> 14)

int main()
{
    string fp = "../../../images/lenna.bmp";
    Mat src = imread(fp, IMREAD_COLOR);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

#if 0
    //color img reverse 1
    Mat dst = Scalar(255,255,255) - src;

    //color img revers 2
    Mat dst(src.rows, src.cols, src.type());

    for(int y = 0; y < src.rows; y++){
        for(int x = 0; x < src.cols; x++){
            Vec3b& p1 = src.at<Vec3b>(y,x);
            Vec3b& p2 = dst.at<Vec3b>(y, x);

            p2 = Vec3b(255,255,255) - p1;
            // p2[2] = 255 - p1[2]; //Red
            // p2[1] = 255 - p1[1]; //Green
            // p2[0] = 255 - p1[0]; //Blue
        }
    }
#else
    //color to gray 1
    // Mat dst(src.rows, src.cols, CV_8UC1);

    // for(int y = 0; y < src.rows; y++){
    //     for(int x = 0; x < src.cols; x++){
    //         Vec3b& p1 = src.at<Vec3b>(y,x);
    //         uchar b = p1[0];
    //         uchar g = p1[1];
    //         uchar r = p1[2];

    //         // uchar gray = (uchar)(0.299 * r + 0.587 * g + 0.114 * b);
    //         uchar gray = RGB2GRAY(r, g, b);
    //         dst.at<uchar>(y, x) = gray;
    //     }
    // }

    //color to gray 2
    Mat dst;
    cvtColor(src, dst, COLOR_BGR2GRAY);

#endif

    imshow("src", src);
    imshow("dst", dst);
    while(1){
        if(waitKey() == 27) break;
    }
}








