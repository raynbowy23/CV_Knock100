#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char* argv[])
{
    Mat img = imread("../dataset/imori.jpg", IMREAD_COLOR);

    if(! img.data)
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    int width = img.cols;
    int height = img.rows;

    Mat out = Mat::zeros(height, width, CV_8UC1);

    int th = 128;

    for(int j=0;j<height;j++){
        for(int i=0;i<width;i++){
            uchar val = (int)((float)img.at<Vec3b>(j,i)[0] * 0.0722 + \
                                       (float)img.at<Vec3b>(j,i)[1] * 0.7152 + \
                                       (float)img.at<Vec3b>(j,i)[2] * 0.2126);

            if(val < th){
                val = 0;
            }else{
                val = 255;
            }
            out.at<uchar>(j,i) = val;
        }
    }

    imwrite("imoried.jpg", out);

    return 0;
}