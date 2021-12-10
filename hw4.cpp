#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat drawHistogram( Mat src);
Mat drawHistogramWithValue( Mat src);

int main(){

    Mat image, equalized_image;
    Mat hist_graph, hist_equalized_graph;
    Mat image_with_value;
    image = imread("moon.png", 0);
    if(!image.data) exit(1);

    //perform histogram equalization
    equalizeHist(image, equalized_image);
    imshow("before", image);
    imshow("after", equalized_image);

    //display each histogram
    hist_graph = drawHistogram(image);
    hist_equalized_graph = drawHistogram(equalized_image);
    imshow("h1", hist_graph);
    imshow("h2", hist_equalized_graph);

    //compute the value of each component
    image_with_value = writeValue(image);
    imshow("value", image_with_value);

waitKey(0);
return 0;
}
Mat drawHistogram(Mat src){

    Mat hist, histImage;

    float range[] = {0, 256};
    const float* histRange = {range};

    int hist_w = 512;
    int hist_h = 512;
    int number_bins = 16;
    int bin_w = cvRound((double)hist_w / number_bins);

    histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255,255,255));

    calcHist(&src, 1, 0, Mat(), hist, 1, &number_bins, &histRange);
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for(int i = 0; i<number_bins; i++)
    {
        rectangle(histImage, Point(bin_w*i, hist_h), Point(bin_w*(i+1), hist_h - cvRound(hist.at<float>(i))), Scalar(0,0,0), -1);
    }
   return histImage;

}
Mat writeValue( Mat src){

    Mat hist;

    float range[] = {0, 256};
    const float* histRange = {range};
    int number_bins = 8;

    calcHist(&src, 1, 0, Mat(), hist, 1, &number_bins, &histRange);
    
    for(int i = 0; i<number_bins; i++)
    {
        putText(src, to_string(hist.at<float>(i)/src.total()), Point(src.size().width/3, src.size().height/8*(i+1)-15), 1, 1, 0, 1, 8);
    }

   return src;
}
