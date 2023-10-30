#include <iostream>
#include "opencv2/opencv.hpp"

#include "include/mycanny.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("../../../images/circuit.bmp", IMREAD_GRAYSCALE);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    Mat dst1, dst2;
    Canny(src, dst1, 50, 150);
    myCanny(src, dst2, 50, 150);

    imshow("Src", src);
    imshow("OpenCV Canny", dst1);
    imshow("my canny", dst2);

    while(1){
        if(waitKey() == 27) break;
    }
}