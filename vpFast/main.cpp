
#include <iostream>
#include <vector>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>
#include "vpGetKeypointFast.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "Veuillez entrer l'adresse de l'image à traiter: " << endl;
	string imagePath;
	cin >> imagePath;

	vpImage<unsigned char> imgSource;
	vpImageIo::read(imgSource, imagePath);
	
	int threshold=30;
	
	// récupération des points d'intérèts dans un vecteur
	vector<vpImagePoint> keypoints = vpGetKeypointFromFast(imgSource, threshold);


	vpImage<vpRGBa> img;
	vpImageIo::read(img, imagePath);
	
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
