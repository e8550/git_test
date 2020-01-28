
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream> 
#include <vector> 
using namespace cv;
using namespace std;

int level1 = 110, level2 = 120, level3 = 240, level = 200, n = 0, n2 = 0, flag = 0;
int  loop_end;
Mat img;
Mat gray_img;
Mat bin_img;
Mat bin1_img;
Mat bin2_img;
Mat erode_img;
Mat element = Mat::ones(5, 5, CV_8UC1);
int Syori() {
	cvtColor(img, gray_img, CV_BGR2GRAY);
	if (flag) {
		threshold(gray_img, bin1_img, level1, 255, THRESH_TOZERO);
		threshold(bin1_img, bin2_img, level2, 255, THRESH_TOZERO_INV);
		threshold(bin2_img, bin_img, level3, 255, THRESH_BINARY);
	}
	else threshold(gray_img, bin_img, level, 255, THRESH_BINARY);
	//	bin_img = ~bin_img;
	erode_img = bin_img;
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
		circle(img, Point(x, y), 5, Scalar(0, 0, 255), 2, 4);
	}
	cout << contours.size() << endl;
	imshow("gray", gray_img);
	if (flag) {
		imshow("binary1", bin1_img);
		imshow("binary2", bin2_img);
	}
	imshow("binary", bin_img);
	imshow("erode", erode_img);
	imshow("image", img);
	const int key = waitKey(1);
	if (key == 'q') {
		return 1;
	}
	else if (key == 's') {
		imwrite("C:/Users/takashi/Desktop/電気情報工学科/電気情報工学実験/2/mini_gamesection/camera.png", img);
		imwrite("C:/Users/takashi/Desktop/電気情報工学科/電気情報工学実験/2/mini_gamesection/camera_gray.png", gray_img);
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
	img = imread("C:/Users/takashi/Desktop/電気情報工学科/電気情報工学実験/2/mini_gamesection/17918.jpg", 1);
	if (img.empty()) return -1;
	while (1) {
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