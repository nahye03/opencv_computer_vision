#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

//bigger than index
uchar curve1[256] = {
	0, 2, 3, 4, 7, 8, 9, 11,
	12, 14, 15, 16, 18, 19, 21, 22,
	24, 25, 27, 28, 30, 31, 33, 34,
	36, 37, 39, 40, 42, 43, 45, 46,
	47, 49, 50, 52, 53, 55, 56, 58,
	59, 61, 62, 63, 65, 66, 68, 69,
	71, 72, 73, 75, 76, 78, 79, 80,
	82, 83, 85, 86, 87, 89, 90, 91,
	93, 94, 95, 97, 98, 100, 101, 102,
	104, 105, 106, 107, 109, 110, 111, 113,
	114, 115, 117, 118, 119, 120, 122, 123,
	124, 125, 127, 128, 129, 130, 131, 133,
	134, 135, 136, 137, 139, 140, 141, 142,
	143, 144, 145, 146, 148, 149, 150, 151,
	152, 153, 154, 155, 156, 157, 158, 159,
	160, 161, 162, 164, 165, 165, 166, 167,
	168, 169, 170, 171, 172, 173, 174, 175,
	176, 177, 178, 179, 180, 180, 181, 182,
	183, 184, 185, 186, 186, 187, 188, 189,
	190, 191, 191, 192, 193, 194, 195, 195,
	196, 197, 198, 198, 199, 200, 201, 201,
	202, 203, 204, 204, 205, 206, 207, 207,
	208, 209, 209, 210, 211, 211, 212, 213,
	213, 214, 215, 215, 216, 217, 217, 218,
	219, 219, 220, 221, 221, 222, 222, 223,
	224, 224, 225, 226, 226, 227, 227, 228,
	229, 229, 230, 230, 231, 231, 232, 233,
	233, 234, 234, 235, 235, 236, 237, 237,
	238, 238, 239, 239, 240, 241, 241, 242,
	242, 243, 243, 244, 244, 245, 246, 246,
	247, 247, 248, 248, 249, 249, 250, 250,
	251, 252, 252, 253, 254, 254, 255, 255
};

//less than index
uchar curve2[256] = {
	0, 0, 1, 1, 1, 2, 3, 3,
	4, 4, 5, 6, 6, 7, 7, 8,
	8, 9, 9, 10, 10, 11, 11, 12,
	12, 13, 13, 14, 14, 15, 15, 16,
	17, 17, 18, 18, 19, 19, 20, 20,
	21, 21, 22, 23, 23, 24, 24, 25,
	25, 26, 27, 27, 28, 28, 29, 30,
	30, 31, 31, 32, 33, 33, 34, 35,
	35, 36, 37, 37, 38, 38, 39, 40,
	40, 41, 42, 43, 43, 44, 45, 45,
	46, 47, 47, 48, 49, 50, 50, 51,
	52, 53, 53, 54, 55, 56, 57, 57,
	58, 59, 60, 61, 61, 62, 63, 64,
	65, 66, 67, 68, 68, 69, 70, 71,
	72, 73, 74, 75, 76, 77, 78, 79,
	80, 81, 82, 82, 83, 85, 86, 87,
	88, 89, 90, 91, 92, 93, 94, 95,
	96, 97, 98, 99, 100, 102, 103, 104,
	105, 106, 107, 108, 110, 111, 112, 113,
	114, 115, 117, 118, 119, 120, 121, 123,
	124, 125, 126, 128, 129, 130, 131, 133,
	134, 135, 136, 138, 139, 140, 141, 143,
	144, 145, 147, 148, 149, 151, 152, 153,
	155, 156, 157, 159, 160, 161, 163, 164,
	165, 167, 168, 169, 171, 172, 174, 175,
	176, 178, 179, 180, 182, 183, 185, 186,
	187, 189, 190, 192, 193, 195, 196, 197,
	199, 200, 202, 203, 205, 206, 207, 209,
	210, 212, 213, 215, 216, 217, 219, 220,
	222, 223, 225, 226, 228, 229, 230, 232,
	233, 235, 236, 238, 239, 241, 242, 244,
	245, 246, 248, 249, 250, 252, 253, 255
};


int main()
{
    string fp = "../../../images/girl.jpg";
    Mat src = imread(fp, IMREAD_COLOR);

    if(src.empty()){
        cerr << "image load failed!!" << endl;
        return -1;
    }

    resize(src, src, Size(src.cols/2, src.rows/2));

    vector<Mat> channels; //B, G, R
    split(src, channels);

    for(int y = 0; y < src.rows; y++){
        for(int x = 0; x < src.cols; x++){
            //to more red
            channels[2].at<uchar>(y,x) = curve1[channels[2].at<uchar>(y,x)];
            //to less blue
            channels[0].at<uchar>(y,x) = curve2[channels[0].at<uchar>(y,x)];
        }
    }

    Mat dst;
    merge(channels, dst);

    imshow("src", src);
    imshow("dst", dst);

    while(1){
        if(waitKey() == 27) break;
    }
}