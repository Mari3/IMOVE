#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <cv.hpp>

using namespace std;
using namespace cv;

int main() {

    /*vector<String> fn;
    vector<Mat> data;
    cout << "glob" << endl;
    glob("/Users/wouter/ClionProjects/opencvtest/forumoverheadimagesubset/",fn,true); // recurse
    for (size_t k=0; k<fn.size(); ++k)
    {
        Mat im = imread(fn[k]);
        if (im.empty()) continue; //only proceed if successful
        // you probably want to do some preprocessing
        Mat without_text = im(Range(0,464),Range(0,640));
        data.push_back(without_text);
    }

    Mat bg = data[0];*/

    VideoCapture cap("/Users/wouter/ClionProjects/opencvtest/IMG_0639.mp4");

    cout << "opening window" << endl;
    namedWindow("display", WINDOW_AUTOSIZE);

    SimpleBlobDetector::Params params;
    params.filterByCircularity = false;
    params.filterByColor = false;
    params.filterByConvexity = false;
    params.filterByInertia = false;
    params.filterByArea = true;
    params.minArea = 400;
    params.minDistBetweenBlobs = 50;
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);


    //for(int i=0;i<423;++i){
    //    cap.grab();
    //}
    //Mat bg;
    //cap >> bg;
    //bg = bg(Range(212,212+192),Range(174,174+240));

    Ptr<BackgroundSubtractorKNN> subtractor = createBackgroundSubtractorKNN();
    //subtractor->setShadowValue(0);

    Mat image;
    while(true) {
        for(int i = 0; i<2; ++i){
            cap.grab();
        }
        cap >> image;
        //image = image(Range(212,212+192),Range(174,174+240));

        //Mat diff = abs(image-bg);
        Mat thresh0;
        Mat thresh;

        subtractor->apply(image,thresh);

        //inRange(diff,Scalar(40,40,40),Scalar(255,255,255),thresh);
        cvtColor(thresh,thresh,COLOR_GRAY2BGR);

        vector<KeyPoint> keypoints;
        detector->detect(thresh,keypoints);

        //Mat im_with_keypoints;
        for(auto &keypoint : keypoints) {
            circle(thresh, keypoint.pt, 40, Scalar(0, 0, 255));
            circle(image, keypoint.pt, 40, Scalar(0, 0, 255));
        }
        //drawKeypoints( thresh, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

        Mat both;
        hconcat(thresh,image,both);

        imshow("display", both);

        if(waitKey(20) >= 0){
            break;
        }
    }

    return 0;
}