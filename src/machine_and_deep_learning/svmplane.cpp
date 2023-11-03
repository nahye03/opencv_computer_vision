#include <iostream>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
using namespace cv::ml;

int main()
{
    Mat train = Mat_<float>({ 8, 2 }, {
		150, 200, 200, 250, 100, 250, 150, 300,
		350, 100, 400, 200, 400, 300, 350, 400 });
	Mat label = Mat_<int>({ 8, 1 }, { 0, 0, 0, 0, 1, 1, 1, 1 });

    Ptr<SVM> svm = SVM::create();

#if 0
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::RBF);
    svm->trainAuto(train, ROW_SAMPLE, label);
#else
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->trainAuto(train, ROW_SAMPLE, label);
#endif

    cout << svm->getC() << endl; //c값 확인
    cout << svm->getGamma() << endl; //gamma 값 확인

    //이미지로 보여주기 위한 작업
    Mat img = Mat::zeros(Size(500,500), CV_8UC3);

    //데이터 생성하여 예측
    for(int y = 0; y < img.rows; y++){
        for(int x = 0; x < img.cols; x++){
            Mat test = Mat_<float>({1, 2}, {(float)x, (float)y});
            int res = cvRound(svm->predict(test));

            if(res == 0)
                img.at<Vec3b>(y,x) = Vec3b(128, 128, 255); //R
            else
                img.at<Vec3b>(y,x) = Vec3b(128, 255, 128); //G
        }
    }

    for(int i = 0; i < train.rows; i++){
        int x = cvRound(train.at<float>(i,0));
        int y = cvRound(train.at<float>(i, 1));
        int l = label.at<int>(i,0);

        if(l==0)
            circle(img, Point(x, y), 5, Scalar(0,0,128), -1, LINE_AA);
        else
            circle(img, Point(x, y), 5, Scalar(0,128,0), -1, LINE_AA);
    }

    imshow("img", img);
    while(1){
        if(waitKey()==27)
            break;
    }

}

