#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("../../../images/digit_consolas.bmp", IMREAD_GRAYSCALE);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    //binary src + inverse
    Mat src_bin;
    threshold(src, src_bin, 128, 255, THRESH_BINARY_INV);

    Mat labels, stats, centroids;
    int label_cnt = connectedComponentsWithStats(src_bin, labels, stats, centroids);

    string filepath = "../../../images/digits/";

    for(int i = 1; i < label_cnt; i++){
        //get bounding box
        int sx = stats.at<int>(i,0);
        int sy = stats.at<int>(i, 1);
        int w = stats.at<int>(i,2);
        int h = stats.at<int>(i, 3);

        //digit save file
        Mat digit;
        resize(src(Rect(sx,sy,w,h)), digit, Size(100,150));

        string filename = filepath + cv::format("temp%d.bmp", i - 1);
        imwrite(filename, digit);
        cout << filename << " file is generated!" << endl;

    }
}