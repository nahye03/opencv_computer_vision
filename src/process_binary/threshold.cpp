#include <iostream>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int t_val = 128;
void on_trackbar_threshold(int, void*);
Mat src, dst;


int main(int argc, char* argv[])
{
    string filepath ="../../../images/";
    string filename = filepath+"neutrophils.png";

    if(argc > 1){
        filename = filepath + argv[1];
        cout << "------------------------";
    }

    src = imread(filename, IMREAD_GRAYSCALE);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    namedWindow("src");
    imshow("src", src);

    namedWindow("dst");
    createTrackbar("Threshold", "dst", &t_val, 255, on_trackbar_threshold);
    on_trackbar_threshold(0, 0);

    while(1){
        if(waitKey() == 27) break;
    }
}

void on_trackbar_threshold(int, void*)
{
    threshold(src, dst, t_val, 255, THRESH_BINARY);
    imshow("dst", dst);
}