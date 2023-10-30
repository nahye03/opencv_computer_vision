#include <iostream>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


int main()
{
    string fp = "../../../images/cropland.png";
    Mat src = imread(fp, IMREAD_COLOR);
    resize(src, src, Size(src.cols/2,src.rows/2));

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    Rect rc = selectROI(src); //select some space in srcImg

    Mat src_ycrcb;
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

    Mat crop = src_ycrcb(rc);

    Mat hist;
	int channels[] = {1, 2};
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = {cr_bins, cb_bins};
	float cr_range[] = {0, 256};
	float cb_range[] = {0, 256};
	const float* ranges[] = {cr_range, cb_range};

	// calc histogram
	calcHist(&crop, 1, channels, Mat(), hist, 2, histSize, ranges);

    //backprojection
	Mat backproj;
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges);

	Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);
	src.copyTo(dst, backproj);

	//imshow("src", src);
	imshow("dst", dst);

    while(1){
        if(waitKey() == 27) break;
    }
}