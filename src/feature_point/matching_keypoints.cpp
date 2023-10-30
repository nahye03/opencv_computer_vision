#include <iostream>
#include <opencv2/features2d.hpp>
#include "opencv2/core/ocl.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    ocl::setUseOpenCL(false);
    /*
    string filepath = "../../../images/lenna.bmp";
    Mat src1 = imread(filepath, IMREAD_GRAYSCALE);

    if (src1.empty()){
        cerr << "Image load failed!" << endl;
        return -1;
    }

    //create src2 (resize & rotate src)
    Mat src2;
    resize(src1, src2, Size(), 0.8, 0.8);

    Point cp(src2.cols / 2, src2.rows / 2); //center of src2
    Mat rot = getRotationMatrix2D(cp, 10, 1); //rotate anti-clockwise 10 degree
    warpAffine(src2, src2, rot, Size()); //rotate

    */
    Mat src1 = imread("../../../images/box.png", IMREAD_GRAYSCALE);
    Mat src2 = imread("../../../images/box_in_scene.png", IMREAD_GRAYSCALE);

    Ptr<Feature2D> detector = SIFT::create();


    TickMeter tm;
    tm.start();

    //detect and compute
    vector<KeyPoint> kp1, kp2;
    Mat desc1, desc2;
    detector->detectAndCompute(src1, Mat(), kp1, desc1);
    detector->detectAndCompute(src2, Mat(), kp2, desc2);


    tm.stop();

    cout << kp1.size() << endl;
    cout << kp2.size() << endl;
    cout << "time: " << tm.getTimeMilli() << endl;

    //matching
    Ptr<BFMatcher> matcher = BFMatcher::create();

#if 1
//select method 1 : match() & sort
    vector<DMatch> matches;
    matcher->match(desc1, desc2, matches);

    sort(matches.begin(),matches.end());
    vector<DMatch> good_matches(matches.begin(), matches.begin() + 80);
#else
//select method 2 : knnmatch() & ratio of best and second
    vector<vector<DMatch>> matches;
    matcher->knnMatch(desc1, desc2, matches, 2);

    vector<DMatch> good_matches;
    for(auto& m: matches){
        if(m[0].distance / m[1].distance < 0.7)
            good_matches.push_back(m[0]);
    }

#endif

    //draw result of matching
    Mat dst;
    drawMatches(src1, kp1, src2, kp2, good_matches, dst);

    imshow("dst", dst);


    //draw keypoints
    // Mat dst1, dst2;
    // drawKeypoints(src1, kp1, dst1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    // drawKeypoints(src2, kp2, dst2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    // imshow("dst1", dst1);
    // imshow("dst2", dst2);

    while(true){
        if(waitKey()==27) break;
    }
}