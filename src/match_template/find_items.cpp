#include <iostream>
#include <opencv2/calib3d.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("../../../images/cookierun.png");
    Mat tmp1 = imread("../../../images/item.png");

    if(src.empty() || tmp1.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    Mat res, res_norm;
    matchTemplate(src, tmp1, res, TM_CCOEFF_NORMED);
    normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8UC1);

    Mat local_max = res_norm > 220;

    Mat labels;
    int num = connectedComponents(local_max, labels);

    Mat dst = src.clone();

    for(int i = 1; i < num; i++){
        Point max_loc;
        Mat mask = (labels == i);
        minMaxLoc(res, 0, 0, 0, &max_loc, mask);

        cout << max_loc.x << ", " << max_loc.y << endl;

        Rect b_rect = Rect(max_loc.x, max_loc.y, tmp1.cols, tmp1.rows);
        rectangle(dst, b_rect, Scalar(0,255,255), 2);
    }

    imshow("src", src);
    imshow("local_max", local_max);
    imshow("dst", dst);

    while(1){
        if(waitKey() == 27) break;
    }

}