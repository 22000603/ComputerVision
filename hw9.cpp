#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace cv;

static void origin(Mat image);
static void function1(Mat image);
static void function2(Mat image, vector<Rect> boundRect);
static void function3(Mat image, vector<Rect> boundRect);
int main()
{
    //Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
    Mat image, foregroundMask, backgroundImg, foregroundImg;
    VideoCapture cap("Faces.mp4");
    int sign = 0;
    int fps = (int)cap.get(CAP_PROP_FPS);

    if(!cap.isOpened()){
        printf("Can't open the camera");
        return -1;
    }

    while (true)
    {
        cap >> image;
        resize(image, image, Size(640, 480));

        waitKey(1000/fps);
        
        CascadeClassifier face_classifier;
        face_classifier.load("haarcascade_frontalface_alt.xml");
        Mat grayImage;
        vector<Rect> faces;

        cvtColor(image, grayImage, COLOR_BGR2GRAY);
        face_classifier.detectMultiScale(grayImage, faces, 1.1, 3, 0, Size(10, 10));

        if (waitKey(1000 / fps) == 98 && sign == 0)
        {
            function1(image);
            sign = 1;
        }
        else if (waitKey(1000 / fps) == 102 && sign == 0)
        {
            function2(image, faces);
            sign = 1;
        }
        else if (waitKey(1000 / fps) == 103 &&sign == 0)
            {
            function3(image, faces);
            sign = 1;
            }
        else
        {
            origin(image);
            sign = 0;
        }
        
    }
    waitKey(0);
    cap.release();
    return 0;
}
static void origin(Mat image)
{
    imshow("hw9", image);
}
static void function1(Mat image)
{
    // Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
    // Mat gray, mask, result, back;

    resize(image, image, Size(640, 480));

    // if(mask.empty())
    //     mask.create(image.size(), image.type());

    // bg_model->apply(image, mask);
    // GaussianBlur(mask, mask, Size(11,11), 3.5, 3.5);
    // threshold(mask, mask, 10, 255, THRESH_BINARY);
    // result = Scalar::all(0);
    // image.copyTo(result, mask);
    // bg_model->getBackgroundImage(back);

    // imshow("function1_mask", mask);
    // imshow("function1_result", result);
    
    Rect rectangle(0, 0, image.cols, image.rows);
    Mat result, bgModel, fgModel;

    grabCut(image, result, rectangle, bgModel, fgModel, 10, GC_INIT_WITH_RECT);
    compare(result, GC_PR_FGD, result, CMP_EQ);
    Mat foreground(image.size(), CV_8UC3, Scalar(0, 0, 0));
    image.copyTo(foreground, result);

    imshow("result", result);

    vector<vector<Point> > countors;
    vector<Vec4i> hierarchy;

    findContours(result, countors, hierarchy,
                 CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    putText(foreground, format("There are %d people.", countors.size()), Point(50, 80),
            FONT_HERSHEY_SIMPLEX, 1, Scalar(0), 4);

    imshow("function1", foreground);
}
static void function2(Mat image, vector<Rect> faces)
{

    vector<int> faces_size;

    for (int i = 0; i < faces.size(); i++)
    {
        faces_size.push_back(faces[i].area());
    }
    int max = max_element(faces_size.begin(), faces_size.end()) - faces_size.begin();
    int min = min_element(faces_size.begin(), faces_size.end()) - faces_size.begin();


    for (int i = 0; i < faces.size(); i++)
    {
        //boundRect[i].tl() = Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
        //Point tr(faces[i].x, faces[i].y);
        if (i == max)
            rectangle(image, faces[i].tl(), faces[i].br(), 
            Scalar(0, 255, 0), 3, 4, 0);
        else if (i == min)
            rectangle(image, faces[i].tl(), faces[i].br(), 
            Scalar(255, 0, 0), 3, 4, 0);
        else
            rectangle(image, faces[i].tl(), faces[i].br(), 
            Scalar(100, 255, 255), 3, 4, 0);
    }
    imshow("function2", image);
}
static void function3(Mat image, vector<Rect> faces)
{
    Mat result1, result2, result3;
    Mat bgModel, fgModel;
    Mat result(image.size(), CV_8UC3, Scalar(0, 0, 0));
    
    for (int i = 0; i < faces.size(); i++)
    {
            Rect rec(faces[i].tl(), faces[i].br());
            grabCut(image, result, rec, bgModel, fgModel, 10, GC_INIT_WITH_RECT);

    }

    imshow("function3", result);
}