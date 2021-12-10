#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat finger, adaptive_1, adaptive;

    finger = imread("finger_print.png", 0);
    threshold(finger, finger, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("finger_print", finger);

    Mat binary;
    adaptive_1 = imread("adaptive_1.jpg", 0);
    adaptiveThreshold(adaptive_1, adaptive_1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 8);
    imshow("adaptive_1", adaptive_1);

    adaptive = imread("adaptive.png", 0);
    adaptiveThreshold(adaptive, adaptive, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 2);
    imshow("adaptive", adaptive);

    waitKey();
}