#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream> //追加
#include <vector> //追加
using namespace cv;
using namespace std; //追加
int main() {
//	Mat img = imread("C:/Users/takashi/Desktop/電気情報工学科/電気情報工学実験/2/mini_gamesection/S__24526852.jpg", 1);
//	if (img.empty()) return -1;
	VideoCapture cap(1);
	if (!cap.isOpened()) return -1;
	Mat img;
	Mat gray_img;
	Mat bin_img;
	Mat element = Mat::ones(5, 5, CV_8UC1);
	while (cap.read(img)) {
		cvtColor(img, gray_img, CV_BGR2GRAY);
		threshold(gray_img, bin_img, 100, 255, THRESH_BINARY);
		erode(bin_img, bin_img, element, Point(-1, -1), 1);
		erode(bin_img, bin_img, element, Point(-1, -1), 1);
		erode(bin_img, bin_img, element, Point(-1, -1), 1);
		erode(bin_img, bin_img, element, Point(-1, -1), 1);
		erode(bin_img, bin_img, element, Point(-1, -1), 1);
//		erode(bin_img, bin_img, element, Point(-1, -1), 1);
//		erode(bin_img, bin_img, element, Point(-1, -1), 1);
		vector<vector<Point>> contours;
		findContours(bin_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		for (int i = 0; i < contours.size(); i++) {
			int count = contours.at(i).size();
			double x = 0; double y = 0;
			for (int j = 0; j < count; j++) {
				x += contours.at(i).at(j).x;
				y += contours.at(i).at(j).y;
			}
			x /= count;
			y /= count;
			circle(img, Point(x, y), 5, Scalar(0, 0, 255), 2, 4);
		}
		cout << contours.size() << endl;
		imshow("binary", bin_img);
		imshow("image", img);
		const int key = waitKey(1);
		if (key == 'q') {
			break;
		}
	}
	destroyAllWindows();
//	waitKey(0);
    return 0;
}