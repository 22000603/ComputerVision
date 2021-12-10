#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    //Mat image1, image2, image3;
    Mat lena, lena_filtered, lena_blur;
    Mat moon, moon_filtered, sharp_moon, lap_moon, abs_moon;
    Mat saltnpepper, saltnpepper_filtered;

    //average filtering
    lena = imread("lena.png");
    if(lena.empty()) {cout << "Image load failed!" <<endl; return -1;}
    lena_filtered = lena.clone();
    Rect rect1(0, 0, (lena.size().width)/2, lena.size().height);
    lena_blur= lena_filtered(rect1);
    blur(lena_blur, lena_blur, Size(7,7));

    //sharpening
    moon = imread("moon.png", 0);
    if(moon.empty()) {cout << "Image load failed!" <<endl; return -1;}
    moon_filtered = moon.clone();
    Rect rect2(moon.size().width / 2, 0, moon.size().width / 2, moon.size().height);
    sharp_moon = moon_filtered(rect2);
    GaussianBlur(sharp_moon, sharp_moon, Size(3,3), 0, 0, BORDER_DEFAULT);
    Laplacian(sharp_moon, lap_moon, CV_16S);
    convertScaleAbs(lap_moon, abs_moon);
    sharp_moon = abs_moon + sharp_moon;

    //median filtering
    saltnpepper = imread("saltnpepper.png", 0);
    if(saltnpepper.empty()) {cout << "Image load failed!" <<endl; return -1;}
    saltnpepper_filtered = saltnpepper.clone();
    medianBlur(saltnpepper_filtered, saltnpepper_filtered, 9);

    imshow("lena", lena);
    imshow("lena_filtered", lena_filtered);
    imshow("moon", moon);
    imshow("moon_filtered", moon_filtered);
    imshow("saltnpepper", saltnpepper);
    imshow("saltnpepper_filtered", saltnpepper_filtered);

    waitKey(0);
    return(0);
}