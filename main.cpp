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
		imwrite("C:/Users/takashi/Desktop/�d�C���H�w��/�d�C���H�w����/2/mini_gamesection/camera.png", img);
		imwrite("C:/Users/takashi/Desktop/�d�C���H�w��/�d�C���H�w����/2/mini_gamesection/camera_gray.png", gray_img);
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
	img = imread("C:/Users/takashi/Desktop/�d�C���H�w��/�d�C���H�w����/2/mini_gamesection/17918.jpg", 1);
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



#define  LOW_HUE        40              //hue�̉���

#define  UP_HUE         80              //hue�̏��

#define  LOW_SATURATION 60              //saturation�i�ʓx�j�̉���

#define  LOW_VALUE      80              //value�i���x�j�̉���





int main()

{

	string window_capture = "capture"; // �L���v�`�������摜�p

	cv::namedWindow(window_capture, CV_WINDOW_AUTOSIZE);

	string window_output = "output"; // ���ʕ\���p

	cv::namedWindow(window_output, CV_WINDOW_AUTOSIZE);

	//�J�����̃I�[�v��

	cv::VideoCapture cap;

	cap.open(0);

	//�G���[����

	if (!cap.isOpened()) {

		std::cout << "cannot find a camera." << std::endl;

		cv::waitKey(5000);

		return -1;

	}

	cv::Mat hsv, frame, hue, hue1, hue2, saturation, value, hue_saturation, image_black_white;          //�ϐ��m��

	while (1) {

		cap >> frame;                                       //�摜��荞��

		cv::cvtColor(frame, hsv, CV_BGR2HSV);               // RGB�iBGR�j�摜��HSV�摜�ɕϊ�����iframe �� hsv�j

	//�Ԃ��̈���擾

			// hsv���`�����l������singlechannels�Ƃ���Mat�^�̔z��ɕ������Ċi�[����B���̌��ʁAsinglechannels[0]��Hue, singlechannels[1]��Saturation, singlechannels[2]��Value�̏������B

		std::vector<cv::Mat> singlechannels;//Mat�N���X�̃x�N�g���Ƃ���singlechannels���`

		cv::split(hsv, singlechannels);//hsv��singlechannels�ɕ���([0]:h, [1]:s,[2]:v)

		//���ꂼ��̃`�����l�����Ƃ�臒l��ݒ肵�ē�l��

		cv::threshold(singlechannels[0], hue1, LOW_HUE, 255, CV_THRESH_BINARY);                 // singlechannels[0]��LOW_HUE��臒l�������āALOW_HUE�ȏ�̕�����255,����ȉ��̕�����0�ɂȂ�悤�ɁAhue1�Ɋi�[����B

		cv::threshold(singlechannels[0], hue2, UP_HUE, 255, CV_THRESH_BINARY_INV);              // singlechannels[0]��UP_HUE��臒l�������āAUP_HUE�ȏ�̕�����0,����ȉ��̕�����255�ɂȂ�悤�ɁAhue2�Ɋi�[����B

		cv::threshold(singlechannels[1], saturation, LOW_SATURATION, 255, CV_THRESH_BINARY);    //�ʓxLOW_SATURATION�ȏ�

		cv::threshold(singlechannels[2], value, LOW_VALUE, 255, CV_THRESH_BINARY);              //���xLOW_VALUE�ȏ�

		//�����𖞂������̈��out�ɐݒ�

		cv::bitwise_and(hue1, hue2, hue);                                                       // hue1��hue2��bit���Ƃ�and���Ƃ遨hue

		cv::bitwise_and(hue, saturation, hue_saturation);                                       // hue��saturation��bit���Ƃ�and���Ƃ遨hue_saturation



		cv::bitwise_and(hue_saturation, value, image_black_white);                              // hue_saturation��value��bit���Ƃ�and���Ƃ遨image_black_white





	// �摜��\������

		cv::imshow(window_capture, frame);

		cv::imshow(window_output, image_black_white);

		int key = cv::waitKey(5);

		if (key == 'q') {

			break;

		}

	}

	return 0;

}