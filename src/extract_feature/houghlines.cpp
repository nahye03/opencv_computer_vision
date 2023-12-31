#include <iostream>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("../../../images/building.jpg", IMREAD_GRAYSCALE);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    Mat src_edge;
    Canny(src, src_edge, 50, 150);

    vector<Vec2f> lines1;
    HoughLines(src_edge, lines1, 1, CV_PI/180, 250);

    Mat dst1;
    cvtColor(src_edge, dst1, COLOR_GRAY2BGR);

    //show lines on xy space
    for(size_t i = 0; i < lines1.size(); i++){
        float r = lines1[i][0], t = lines1[i][1];
        double cos_t = cos(t), sin_t = sin(t);
        double x0 = r*cos_t, y0 = r*sin_t;
        double alpha = 1000;

        Point pt1(cvRound(x0 + alpha*(-sin_t)), cvRound(y0 + alpha*cos_t));
        Point pt2(cvRound(x0 - alpha*(-sin_t)), cvRound(y0 - alpha*cos_t));

        line(dst1, pt1, pt2, Scalar(0,0,255), 2, LINE_AA);
    }

    vector<Vec4i> lines2;
    HoughLinesP(src_edge, lines2, 1, CV_PI/180, 160, 50, 5);

    Mat dst2;
    cvtColor(src_edge, dst2, COLOR_GRAY2BGR);

    for(size_t i = 0; i < lines2.size(); i++){
        Vec4i l = lines2[i];
        line(dst2, Point(l[0], l[1]), Point(l[2],l[3]), Scalar(0,0,255), 2, LINE_AA);
    }

    imshow("src", src);
    imshow("dst1", dst1);
    imshow("dst2", dst2);

    while(1){
        if(waitKey() == 27) break;
    }
}

