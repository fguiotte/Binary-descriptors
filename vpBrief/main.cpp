/***************************************************************************
 *
 * TODO: Test de l'implémentation de BRIEF
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include "function_opencv.h"
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>

int main( int argc, char* argv[] )
{

    std::cout<<"Test manuel BRIEF"<<std::endl;


    vpImage<unsigned char> img;
    string adresse_image("img.pgm");
	vpImageIo::read(img, adresse_image);
	vector<vpImagePoint> keypoints = getKeypointsFromOpenCV(adresse_image, 30);

	vpDisplayX d(img);
	vpDisplay::display(img);
	vpDisplay::flush(img);
	vpDisplay::getClick(img);
    return 0;
}
