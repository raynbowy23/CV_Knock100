#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <math.h>

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

    int height = img.rows;
    int width = img.cols;

    // Mat out = img.clone();
    Mat out = Mat::zeros(height, width, CV_8UC3);

    for(int j=0;j<height;j++){
        for(int i=0;i<width;i++){
            for(int c=0;c<3;c++){
                out.at<Vec3b>(j,i)[c] = (uchar)(floor((double)img.at<Vec3b>(j,i)[c]/64)*64 + 32);
            }
        }
    }

    imwrite("imoried.jpg", out);

    return 0;
}