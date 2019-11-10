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
    int R = 8; //平均グリッド
    double v = 0;

    // Mat out = img.clone();
    Mat out = Mat::zeros(height, width, CV_8UC3);

    for(int j=0;j<height;j+=R){
        for(int i=0;i<width;i+=R){
            for(int c=0;c<3;c++){
                v = 0;
                for(int _j=0;_j<R;_j++){
                    for(int _i=0;_i<R;_i++){
                        v += (double)img.at<Vec3b>(j+_j, i+_i)[c];
                    }
                }
                v /= (R * R);
                for(int _j=0;_j<R;_j++){
                    for(int _i=0;_i<R;_i++){
                        out.at<Vec3b>(j+_j, i+_i)[c] = (uchar)v;
                    }
                }
            }
        }
    }

    imwrite("imoried.jpg", out);

    return 0;
}