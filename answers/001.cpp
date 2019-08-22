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

    int width = img.rows;
    int height = img.cols;

    Mat out = img.clone();


    for(int j=0;j<height;j++){
        for(int i=0;i<width;i++){
            unsigned char tmp = out.at<Vec3b>(i,j)[0]; // R
            out.at<Vec3b>(i,j)[0] = img.at<Vec3b>(i,j)[2]; // B
            out.at<Vec3b>(i,j)[2] = tmp;
        }
    }

    imwrite("imoried.jpg", out);

    return 0;
}