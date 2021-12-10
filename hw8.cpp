#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    VideoCapture capture("background.mp4");
    
    Mat background, image, gray, avg, Mask, Img;
    int cnt = 2;

    capture >> avg;

    vector<vector<Point> > contours;
    vector<Vec4i>hierarchy;
    
        while(cnt<=10){
        if(!capture.read(image)) break;
        add(image/cnt, avg*(cnt-1)/cnt, avg);
        cnt++;
        }
        cvtColor(avg, background, CV_BGR2GRAY);
        imshow("background", background);
        
        while(true){
        if(capture.grab()==0) break;
        capture.retrieve(image);
        cvtColor(image, gray, CV_BGR2GRAY);
        
        absdiff(background, gray, Mask);
        threshold(Mask, Mask, 20, 255, CV_THRESH_BINARY);
        Mask.copyTo(Img);
        gray.copyTo(Img, Mask);

        imshow("Img", Img);
        imshow("Result(x,y)", Mask);

    
        findContours(Mask, contours, hierarchy, 
        CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
    
        vector<Rect> boundRect(contours.size());
        int num = 0; 

        for(int i=0; i<contours.size(); i++)
            if(boundingRect(Mat(contours[i])).area()>400){
                boundRect[num] = boundingRect(Mat(contours[i]));
                num++;}

        for(int i=0; i<num; i++){
            rectangle(image, boundRect[i].tl(), boundRect[i].br(), 
            Scalar(0,0,255), 2, 8, 0);
            }

        putText(image, format("total count: %d", num), Point(50, image.rows - 50), 
        FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,0), 4);
    
        imshow("result", image);
    
        waitKey(33); 

    }
}