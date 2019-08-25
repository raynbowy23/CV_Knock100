#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Otsu binarization
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

    //gray scale
    int val = 0;
    for(int j=0;j<height;j++){
        for(int i=0;i<width;i++){
            uchar val = (int)((float)img.at<Vec3b>(j,i)[0] * 0.0722 + \
                                       (float)img.at<Vec3b>(j,i)[1] * 0.7152 + \
                                       (float)img.at<Vec3b>(j,i)[2] * 0.2126);
            
            out.at<uchar>(j,i) = (uchar)val;

        }
    }

    //determine threshold
    double w0 = 0, w1 = 0; // the number of pixels percentage of each class
    double m0 = 0, m1 = 0; // average of each class pixels
    double max_sb = 0, sb = 0; // outer class variance
    int th = 0;            // threshold

    // threshold t
    for(int t=0;t<255;t++){
        w0 = 0;
        w1 = 0;
        m0 = 0;
        m1 = 0;
        // for each pixels
        for(int j=0;j<height;j++){
            for(int i=0;i<width;i++){
                val = (int)(out.at<uchar>(j,i));

                // divide classes
                if(val < t){
                    w0++;
                    m0 += val;
                }else{
                    w1++;
                    m1 += val;
                }
            }
        }

        m0 /= w0; // w0 : the number of pixels in class0
        m1 /= w1; // w1 : the number of pixels in class1
        w0 /= (height * width); // determine w0 here
        w1 /= (height * width);
        sb = w0 * w1 * pow((m0 - m1), 2); // internal class variance

        // maximize variance and determine threshold
        if(sb > max_sb){
            max_sb = sb;
            th = t;
        }
    }

    // binalization
    for(int j=0;j<height;j++){
        for(int i=0;i<width;i++){
            val = (int)(out.at<uchar>(j,i));
            if(val < th){
                val = 0;
            }else{
                val = 255;
            }
            out.at<uchar>(j,i) = (uchar)val;
        }
    }

    std::cout << "threshold >> " << th << std::endl;

    imwrite("imoried.jpg", out);

    return 0;
}