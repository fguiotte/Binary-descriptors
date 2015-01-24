#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
	std::cout << "Veuillez entrer l'adresse de l'image à traiter: " << std::endl;
	string adresse_image;
	std::cin >> adresse_image;
	Mat image = imread(adresse_image);
	
	Mat gray;
	cvtColor(image, gray, CV_BGR2GRAY);
	vector<KeyPoint> keypoints;
	
	FAST(gray, keypoints, 30);
	
	for(size_t i = 0; i < keypoints.size(); i++)
	{
		const KeyPoint &kp = keypoints[i];
		cv::circle(image, kp.pt, kp.size/2, CV_RGB(255, 0, 0));
	}

	imwrite("Images/resultat.pgm", image);
}
