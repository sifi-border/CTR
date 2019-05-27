#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	//入力画像読み込み
	Mat img = imread("img/reina.png", IMREAD_UNCHANGED);
	if (img.empty())
	{
		cout << "READ FAILED..." << endl;
		return -1;
	}

	//分類機に顔識別用パラメータを読み込ませる
	CascadeClassifier cascade;
	cascade.load("xml/lbpcascade_animeface.xml");

	vector<Rect> faces;

	cascade.detectMultiScale(img, faces, 1.1, 4);

	int faceNum = faces.size();

	cout << faceNum << " faces detected." << endl;

	for (int i = 0; i < faceNum; i++)
	{
		//検出した顔の周りに赤い長方形を描画
		rectangle(img, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 0, 255), 3, CV_AA);
	}

	//windowを作り、表示する
	namedWindow("reina", WINDOW_AUTOSIZE);
	imshow("reina", img);

	waitKey(0);

	imwrite("img/res.jpg", img);
	return 0;
}
