#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    
    VideoCapture video("background.mp4"); //Read a video
    
    if(!video.isOpened())
    {
        cout << "Could not open or find the video" << endl;
        waitKey(0);
    }

    Mat videoFrame;
    float fps = video.get(CAP_PROP_FPS);
    int frame = video.get(CAP_PROP_FRAME_COUNT);
    int currentFrame = video.get(CAP_PROP_POS_FRAMES);

    video >> videoFrame;
    imshow ("HW1", videoFrame);
    waitKey(3000); //Display video for the first 3seconds


    while(1){

        
        video >> videoFrame;
        currentFrame = video.get(CAP_PROP_POS_FRAMES);

        if(videoFrame.empty()){
            cout << "end of video" << endl;
            break;
        }
        //Print out the number of the current frame and the total number of frames
        cout << "Frames : " << currentFrame << "/" << frame << endl ;
        imshow ("HW1", videoFrame);
        waitKey(1000/fps);
    }
    
    return 0;
}