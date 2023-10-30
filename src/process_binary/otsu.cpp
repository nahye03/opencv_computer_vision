#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    string filename ="../../../images/rice.png";

    Mat src = imread(filename, IMREAD_GRAYSCALE);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    Mat dst;
    double th = threshold(src, dst, 0, 255, THRESH_BINARY|THRESH_OTSU);

    imshow("src", src);
    imshow("dst", dst);

    while(1){
        if(waitKey() == 27) break;
    }
}