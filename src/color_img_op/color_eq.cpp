#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

#define RGB2GRAY(r, g, b) ((4899*(r) + 9617*(g) + 1868*(b)) >> 14)

int main()
{
    string fp = "../../../images/peppers.bmp";
    Mat src = imread(fp, IMREAD_COLOR);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    Mat src_ycrcb;
    cvtColor(src, src_ycrcb, COLOR_RGB2YCrCb);

    vector<Mat> planes;
    split(src_ycrcb, planes);

    equalizeHist(planes[0], planes[0]);

    Mat dst_ycrcb;
    merge(planes, dst_ycrcb);

    Mat dst;
    cvtColor(dst_ycrcb, dst, COLOR_YCrCb2RGB);

    imshow("src",src);
    imshow("dst", dst);

    while(1){
        if(waitKey() == 27) break;
    }
}