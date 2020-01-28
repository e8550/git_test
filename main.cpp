/*
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

*/

#include <iostream>

#include <opencv2/opencv.hpp>

#include <string>



#ifdef _DEBUG

#pragma comment(lib, "opencv_core230d.lib")

#pragma comment(lib, "opencv_imgproc230d.lib")

#pragma comment(lib, "opencv_highgui230d.lib")

#else

#pragma comment(lib, "opencv_core230.lib")

#pragma comment(lib, "opencv_imgproc230.lib")

#pragma comment(lib, "opencv_highgui230.lib")

#endif



#define  LOW_HUE        40              //hueの下限

#define  UP_HUE         80              //hueの上限

#define  LOW_SATURATION 60              //saturation（彩度）の下限

#define  LOW_VALUE      80              //value（明度）の下限





int main()

{

	string window_capture = "capture"; // キャプチャした画像用

	cv::namedWindow(window_capture, CV_WINDOW_AUTOSIZE);

	string window_output = "output"; // 結果表示用

	cv::namedWindow(window_output, CV_WINDOW_AUTOSIZE);

	//カメラのオープン

	cv::VideoCapture cap;

	cap.open(0);

	//エラー処理

	if (!cap.isOpened()) {

		std::cout << "cannot find a camera." << std::endl;

		cv::waitKey(5000);

		return -1;

	}

	cv::Mat hsv, frame, hue, hue1, hue2, saturation, value, hue_saturation, image_black_white;          //変数確保

	while (1) {

		cap >> frame;                                       //画像取り込み

		cv::cvtColor(frame, hsv, CV_BGR2HSV);               // RGB（BGR）画像をHSV画像に変換する（frame → hsv）

	//赤い領域を取得

			// hsvをチャンネル毎にsinglechannelsというMat型の配列に分解して格納する。その結果、singlechannels[0]がHue, singlechannels[1]がSaturation, singlechannels[2]がValueの情報を持つ。

		std::vector<cv::Mat> singlechannels;//Matクラスのベクトルとしてsinglechannelsを定義

		cv::split(hsv, singlechannels);//hsvをsinglechannelsに分解([0]:h, [1]:s,[2]:v)

		//それぞれのチャンネルことに閾値を設定して二値化

		cv::threshold(singlechannels[0], hue1, LOW_HUE, 255, CV_THRESH_BINARY);                 // singlechannels[0]をLOW_HUEを閾値処理して、LOW_HUE以上の部分が255,それ以下の部分が0になるように、hue1に格納する。

		cv::threshold(singlechannels[0], hue2, UP_HUE, 255, CV_THRESH_BINARY_INV);              // singlechannels[0]をUP_HUEを閾値処理して、UP_HUE以上の部分が0,それ以下の部分が255になるように、hue2に格納する。

		cv::threshold(singlechannels[1], saturation, LOW_SATURATION, 255, CV_THRESH_BINARY);    //彩度LOW_SATURATION以上

		cv::threshold(singlechannels[2], value, LOW_VALUE, 255, CV_THRESH_BINARY);              //明度LOW_VALUE以上

		//条件を満たした領域をoutに設定

		cv::bitwise_and(hue1, hue2, hue);                                                       // hue1とhue2のbitごとのandをとる→hue

		cv::bitwise_and(hue, saturation, hue_saturation);                                       // hueとsaturationのbitごとのandをとる→hue_saturation



		cv::bitwise_and(hue_saturation, value, image_black_white);                              // hue_saturationとvalueのbitごとのandをとる→image_black_white





	// 画像を表示する

		cv::imshow(window_capture, frame);

		cv::imshow(window_output, image_black_white);

		int key = cv::waitKey(5);

		if (key == 'q') {

			break;

		}

	}

	return 0;

}