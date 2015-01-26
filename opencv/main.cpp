#include <iostream>
#include <vector>
#include "function_opencv.h"
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>

using namespace std;

int main(int argc, char** argv)
{
	cout << "Veuillez entrer l'adresse de l'image à traiter: " << endl;
	string adresse_image;
	cin >> adresse_image;
	/*Mat image = imread(adresse_image);
	
	Mat gray;
	cvtColor(image, gray, CV_BGR2GRAY);
	vector<KeyPoint> keypoints;
	
	FAST(gray, keypoints, 30);*/
	vpImage<vpRGBa> img;
	vpImageIo::read(img, adresse_image);
	vpDisplayX image(img, 100, 100);
	vpDisplay::display(img);
	vpDisplay::flush(img);
	vpDisplay::getClick(img);
	vector<vpImagePoint> keypoints = getKeypointsFromOpenCV(adresse_image);

	for(size_t i = 0; i < keypoints.size(); i++)
	{
		const vpImagePoint &kp = keypoints[i];
		vpRGBa red(255,0,0);
		img[(int)kp.get_i()-1][(int)kp.get_j()]= red;
		img[(int)kp.get_i()][(int)kp.get_j()-1] = red;
		img[(int)kp.get_i()][(int)kp.get_j()] = red;
		img[(int)kp.get_i()][(int)kp.get_j()+1] = red;
		img[(int)kp.get_i()+1][(int)kp.get_j()] = red;
	}

	vpDisplayX d(img);
	vpDisplay::display(img);
	vpDisplay::flush(img);
	vpDisplay::getClick(img);
}
