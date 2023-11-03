#include <cstddef>
#include <iostream>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include "opencv2/opencv.hpp"
#include "opencv2/core/ocl.hpp"

using namespace cv;
using namespace std;

int main()
{
    ocl::setUseOpenCL(false);
    Mat src = imread("../../../images/lenna.bmp", IMREAD_GRAYSCALE);
    if(src.empty()){
        cerr << "image load failed" << endl;
        return -1;
    }

    string cascade_path = "../../../thirdparty/OpenCV/opencv/data/haarcascades/";
    CascadeClassifier face_cascade(cascade_path+"haarcascade_frontalface_default.xml");
    CascadeClassifier eye_cascade(cascade_path+"/haarcascade_eye.xml");

    if(face_cascade.empty() && eye_cascade.empty()){
        cerr << "failed to open xml file!" << endl;
        return -1;
    }

    TickMeter tm;
    tm.start();

    vector<Rect> faces;
    face_cascade.detectMultiScale(src, faces);

    tm.stop();
    cout << "face detect: " << tm.getTimeMilli() << ".ms" << endl;

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for (size_t i = 0; i < faces.size(); i++){
        rectangle(dst, faces[i], Scalar(255,0,255), 2, LINE_AA);
        Mat faceROI = src(faces[i]);

        vector<Rect> eyes;
        eye_cascade.detectMultiScale(faceROI, eyes);

        for(size_t j = 0; j < eyes.size(); j++){
            Point eye_center(faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2);
            int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
            circle(dst, eye_center, radius, Scalar(255, 0, 0), 2, LINE_AA);
        }
    }

    imshow("dst", dst);
    while(1){
        if(waitKey() == 27) break;
    }
}
