#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;

// HSV conversion
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

    // calculate HSV
    double Max, Min;
    double H, S, V; // Hue, Saturation, Value;
    double R, G, B;
    double C, H_, X;

    Mat out = Mat::zeros(height, width, CV_8UC3);

    for(int j=0;j<height;j++){
        for(int i=0;i<width;i++){
            // between 0 to 1
            R = (float)img.at<Vec3b>(j,i)[2] / 255;
            G = (float)img.at<Vec3b>(j,i)[1] / 255;
            B = (float)img.at<Vec3b>(j,i)[0] / 255;

            Max = fmax(R, fmax(G, B));
            Min = fmin(R, fmin(G, B));

            if(Min == Max){
                H = 0;
            }else if(Min == B){
                H = 60 * (G-R) / (Max-Min) + 60;
            }else if(Min == R){
                H = 60 * (B-G) / (Max-Min) + 180;
            }else if(Min == G){
                H = 60 * (R-B) / (Max-Min) + 300;
            }

            V = Max;
            S = Max - Min;

            // inverse Hue
            H = fmod((H + 270), 360);

            // convert HSV to RGB
            C = S;
            H_ = H / 60;
            X = C * (1 - abs(fmod(H_,2)-1));

            R = G = B = V - C;

            if(0 <= H_ && H_ < 1){
                R += C;
                G += X;
            }else if(1 <= H_ && H_ < 2){
                R += X;
                G += C;
            }else if(2 <= H_ && H_ < 3){
                G += C;
                B += X;
            }else if(3 <= H_ && H_ < 4){
                G += X;
                B += C;
            }else if(4 <= H_ && H_ < 5){
                R += X;
                B += C;
            }else if(5 <= H_ && H_ < 6){
                R += C;
                B += X;
            }else{
                R = G = B = 0;
            }

            out.at<Vec3b>(j,i)[0] = (uchar)(B * 255);
            out.at<Vec3b>(j,i)[1] = (uchar)(G * 255);
            out.at<Vec3b>(j,i)[2] = (uchar)(R * 255);
        }
    }

    for(int j=0;j<height;j++){
        for(int i=0;i<width;i++){
            unsigned char R = out.at<Vec3b>(j,i)[0]; // R
            unsigned char G = out.at<Vec3b>(j,i)[1]; // G
            unsigned char B = out.at<Vec3b>(j,i)[2]; // B
        }
    }


    imwrite("imoried.jpg", out);

    return 0;
}