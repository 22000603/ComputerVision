#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat image;
    image = imread("lena.png", IMREAD_COLOR);
    
    if(image.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    Mat negative_img = image.clone();
    Mat log_img = image.clone();
    
    Mat gamma_img_1 = image.clone();
    Mat gamma_img_2 = image.clone();

    //negative transformation
    for (int i = 0; i < image.rows; i++){
        for (int j = 0; j < image.cols; j++){
            for(int s = 0; s < image.channels(); s++){
                negative_img.at<Vec3b>(i,j)[s] = 255 - image.at<Vec3b>(i,j)[s];
            }
        }
    }
    
    //log transformation 
    float c = 1.5;
    log_img.convertTo(log_img, CV_32F); //change pixel type to float
    for (int i = 0; i < image.rows; i++){
        for (int j = 0; j < image.cols; j++){
            for(int s = 0; s < image.channels(); s++){
                log_img.at<Vec3b>(i,j)[s] = log(1+image.at<Vec3b>(i,j)[s]);
            }
        }
    }
    normalize(log_img, log_img, 0, 255, NORM_MINMAX);
    convertScaleAbs(log_img, log_img, c);


    //gamma transformation 1
    float gamma = 0.5;
    for (int i = 0; i < image.rows; i++){
        for (int j = 0; j < image.cols; j++){
            for(int s = 0; s < image.channels(); s++){
                gamma_img_1.at<Vec3b>(i,j)[s] = saturate_cast<uchar>(pow(((float) image.at<Vec3b>(i,j)[s]/255.0),(1/gamma))*255.0);
            }
        }
    }

    //gamma transformation 2
    
    for (int i = 0; i < image.rows; i++){
        for (int j = 0; j < image.cols; j++){
            for(int s = 0; s < image.channels(); s++){
                gamma_img_2.at<Vec3b>(i,j)[s] = saturate_cast<uchar>(pow(((float) image.at<Vec3b>(i,j)[s]/255.0),gamma)*255.0);
            }
        }
    }

    imshow("HW2_negative transformation", negative_img);
    imshow("HW2_log transformation", log_img);
    imshow("HW2_gamma transformation 1", gamma_img_1);
    imshow("HW2_gamma transformation 2", gamma_img_2);

    waitKey(0);
    return(0);
}