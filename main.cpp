#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream> 
#include <vector> 
using namespace cv;
using namespace std;
int level1 =0, level2 = 255, level3 = 0, level = 0, n = 0, n2 = 0, flag = 0;
int  loop_end;
Mat img;
//Mat gray_img;
//Mat hsv_img;
Mat channels[3];
Mat bin_img;
Mat bin1_img;
Mat bin2_img;
Mat erode_img;
Mat img2;
Mat element = Mat::ones(2, 2, CV_8UC1);
int Syori() {
	img2 = img.clone();
//	cvtColor(img, hsv_img, COLOR_RGB2HSV);
	split(img, channels);
//	cvtColor(channels[0], channels[0], CV_RGB2GRAY);
//	channels[0] = channels[0] * 1.417;
	if (flag) {
		threshold(channels[1], bin1_img, level1, 255, THRESH_TOZERO);
		threshold(bin1_img, bin2_img, level2, 255, THRESH_TOZERO_INV);
		threshold(bin2_img, bin_img, level3, 255, THRESH_BINARY);
	}
	else threshold(channels[1], bin_img, level, 255, THRESH_BINARY);
	//	bin_img = ~bin_img;
	erode_img = bin_img.clone();
	for (int i = 0; i < n; i++) {
		erode(erode_img, erode_img, element, Point(-1, -1), 1);
	}
	erode_img = ~erode_img;
	for (int i = 0; i < n2; i++) {
		erode(erode_img, erode_img, element, Point(-1, -1), 1);
	}
	erode_img = ~erode_img;
	vector<vector<Point>> contours;
	findContours(erode_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); i++) {
		int count = contours.at(i).size();
		double x = 0; double y = 0;
		for (int j = 0; j < count; j++) {
			x += contours.at(i).at(j).x;
			y += contours.at(i).at(j).y;
		}
		x /= count;
		y /= count;
		circle(img2, Point(x, y), 5, Scalar(0, 0, 255), 2, 4);
	}
	cout << contours.size() << endl;
	imshow("RGB_R", channels[1]);
	if (flag) {
		imshow("binary1", bin1_img);
		imshow("binary2", bin2_img);
	}
	imshow("binary", bin_img);
	imshow("erode", erode_img);
	imshow("image", img);
	imshow("circle", img2);
	const int key = waitKey(1);
	if (key == 'q') {
		return 1;
	}
	else if (key == 's') {
		imwrite("C:/Users/takashi/Desktop/電気情報工学科/電気情報工学実験/2/mini_gamesection/camera.png", img);
		imwrite("C:/Users/takashi/Desktop/電気情報工学科/電気情報工学実験/2/mini_gamesection/camera_red.png", channels[1]);
	}
	else if (key == 'f') cin >> flag;
	else if (key == 'a') cin >> level;
	else if (key == 'w') cin >> level1;
	else if (key == 'e') cin >> level2;
	else if (key == 'r') cin >> level3;
	else if (key == 'z') cin >> n;
	else if (key == 'x') cin >> n2;
	else if (key == 'd') {
		cout << flag << "," << level << "," << level1 << "," << level2 << "," << level3 << "," << n << "," << n2 << endl;
		waitKey(0);
	}
	return 0;
}
int Capture() {
	VideoCapture cap(1);
	if (!cap.isOpened()) return -1;
	while (cap.read(img)) {
		loop_end = Syori();
		if (loop_end) break;
	}
	destroyAllWindows();
	return 0;
}
int Img() {
	while (1) {
		img = imread("C:/Users/takashi/Desktop/電気情報工学科/電気情報工学実験/2/mini_gamesection/dack2.jpg", 1);
		if (img.empty()) return -1;
		loop_end = Syori();
		if (loop_end) break;
	}
	destroyAllWindows();
	//	waitKey(0);
	return 0;
}
int main() {
	int mode;
	int hoge;
	cin >> mode;
	if (mode) hoge = Capture();
	else  hoge = Img();
	if (hoge == -1) cout << "error";
	else if (hoge == 1) cout << "finished";

	return 0;
}


/*
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream> 
#include <vector> 
using namespace cv;
using namespace std;
int main() {
	Mat img;
	img = imread("C:/Users/takashi/Desktop/電気情報工学科/電気情報工学実験/2/mini_gamesection/dack2.jpg");
	Mat rgb_img;
	rgb_img = img.clone();
	imshow("rgb", rgb_img);
	Mat channels[3];
	split(rgb_img, channels);
	imshow("G", channels[0]);
	imshow("R", channels[1]);
	imshow("B", channels[2]);
	imwrite("C:/Users/takashi/Desktop/電気情報工学科/電気情報工学実験/2/mini_gamesection/red.jpg", channels[1]);
	waitKey(0);
	return 0;
}*/