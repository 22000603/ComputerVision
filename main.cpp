#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat image;
    Mat result;
    image = imread("pic.png", 0);
    if(image.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    unsigned char pix[256];
    float gamma = 10.0;
    MatIterator_<uchar> it, end;

    for ( int i=0; i < 256; i++){
    pix[i] = saturate_cast<uchar>(pow((float)(i/255.0), gamma)*255.0f);
    }
    result = image.clone();
    for(it=result.begin<uchar>(), end = result.end<uchar>(); it != end; it++){
        *it = pix[(*it)];
    }
    imshow("code", result);

    waitKey(0);
}