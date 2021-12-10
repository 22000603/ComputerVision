#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void white_balacing(Mat img);

int main(){
    Mat lena, colorful, balancing;
    Mat reset_lena, reset_colorful, reset_balancing;
    Mat hsv;

    char input;
    lena = imread("lena.png", IMREAD_COLOR);
    colorful = imread("colorful.png", IMREAD_COLOR);
    balancing = imread("balancing.png", IMREAD_COLOR);

    lena.copyTo(reset_lena);
    colorful.copyTo(reset_colorful);
    balancing.copyTo(reset_balancing);

    if(lena.empty())
    {   cout << "Could not open the lena image" << endl; return -1; }
    if(colorful.empty())
    {   cout << "Could not open the colorful image" << endl; return -1; }
    if(balancing.empty())
    {   cout << "Could not open the balancing image" << endl; return -1; }

    while(true){
        imshow("lena", lena);
        imshow("colorful", colorful);
        imshow("balancing", balancing);

        if (waitKey(0) == 'n') //negative 
    {
        //negative transformation
    for (int i = 0; i < lena.rows; i++){
        for (int j = 0; j < lena.cols; j++){
            for(int s = 0; s < lena.channels(); s++){
                lena.at<Vec3b>(i,j)[s] = 255 - lena.at<Vec3b>(i,j)[s];
            }
        }
    }
    }
    else if(waitKey(0) == 'g') //gamma
    {
        float gamma = 2.5;
    for (int i = 0; i < lena.rows; i++){
        for (int j = 0; j < lena.cols; j++){
            for(int s = 0; s < lena.channels(); s++){
                lena.at<Vec3b>(i,j)[s] = saturate_cast<uchar>(pow(((float) lena.at<Vec3b>(i,j)[s]/255.0),(1/gamma))*255.0);
            }
        }
    }
    }
    else if(waitKey(0) == 'h') //histogram equalization
    {
        vector<Mat> channels;
        Mat e;
        cvtColor(lena, e, CV_BGR2YCrCb);
        split(e, channels);
        equalizeHist(channels[0], channels[0]);
        merge(channels, lena);
        cvtColor(lena, lena, CV_YCrCb2BGR);
    }
    else if(waitKey(0) == 's') //color slicing
    {   
        uchar* h;
        uchar* s;

        cvtColor(colorful, hsv, CV_BGR2HSV);
        vector<Mat> channels(3);
        split(hsv, channels);

        for(int i=0; i<colorful.rows; i++){
            h = channels[0].ptr<uchar>(i);
            s = channels[1].ptr<uchar>(i);
            for(int j=0; j<colorful.cols; j++){
                if(h[j] > 9 && h[j] < 23) s[j] = s[j];
                else s[j] = 0;
            }
        }

        merge(channels, colorful);
        cvtColor(colorful, colorful, CV_HSV2BGR);

    }
    else if(waitKey(0) == 'c') //color conversion
    {
        uchar* h;
        uchar* s;

        cvtColor(colorful, hsv, CV_BGR2HSV);
        vector<Mat> channels(3);
        split(hsv, channels);

        for(int i=0; i<colorful.rows; i++){
            h = channels[0].ptr<uchar>(i);
            s = channels[1].ptr<uchar>(i);
            for(int j=0; j<colorful.cols; j++){
                if(h[j]+50 > 129) h[j] = h[j] + 50 - 129;
                else h[j] += 50;
            }
        }

        merge(channels, colorful);
        cvtColor(colorful, colorful, CV_HSV2BGR);
    }
    else if(waitKey(0) == 'a') //average filtering
    {
        blur(balancing, balancing, Size(9,9));
    }
    else if(waitKey(0) == 'w') //white balancing
    {
        white_balacing(balancing);
    }
    else if(waitKey(0) == 'r') //reset
    {
        reset_lena.copyTo(lena);
        reset_colorful.copyTo(colorful);
        reset_balancing.copyTo(balancing);
    }
    else if(waitKey(0) == 27)    break;

    else    break;
    }
    return 0;
}
void white_balacing(Mat img) {   
    Mat channels[3];
    split(img, channels);
    double avg;
    int sum, temp, i, j, c;
    for(c=0; c<img.channels(); c++){
        sum = 0;
        avg = 0.0f;
        for(i=0; i<img.rows; i++){
            for(j=0; j<img.cols; j++){
                sum += channels[c].at<uchar>(i,j);
            }
        }
        avg = sum / (img.rows * img.cols);
        for (i=0; i<img.rows; i++){
            for(j=0; j<img.cols; j++){
                temp = (128/avg) * channels[c].at<uchar>(i,j);
                if(temp>255) channels[c].at<uchar>(i,j) = 255;
                else channels[c].at<uchar>(i,j) = temp;
            }
        }
    }
    merge(channels, 3, img);
}
