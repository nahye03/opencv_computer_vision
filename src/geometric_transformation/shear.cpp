#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(){
    Mat src = imread("../../../images/lenna.bmp", IMREAD_GRAYSCALE);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

#if 1
	Mat dst(src.rows* 3 / 2, src.cols , src.type(), Scalar(0));

	double m = 0.5;
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			int nx = x;
			int ny = int(y + m * x);
			dst.at<uchar>(ny, nx) = src.at<uchar>(y, x);
		}
	}
#else
#endif
    imshow("src", src);
    imshow("dst", dst);

    while(1){
        if(waitKey() == 27){
            break;
        }
    }
}