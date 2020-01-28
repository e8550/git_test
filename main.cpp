
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream> 
#include <vector> 
using namespace cv;
using namespace std;


int main(){
	Mat img;
	img = imread("C:/Users/takashi/Desktop/電気情報工学科/電気情報工学実験/2/mini_gamesection/17918.jpg");
	Mat hsv_img;
	cvtColor(img, hsv_img, COLOR_RGB2HSV);
	imshow("hsv", hsv_img);
	Mat channels[3];
	split(hsv_img, channels);
	imshow("H", channels[0]*1.417);
	imshow("S", channels[1]);
	imshow("V", channels[2]);
	waitKey(0);
    return 0;
}