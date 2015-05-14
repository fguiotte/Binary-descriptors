/***************************************************************************
 *
 * TODO: Test de l'implémentation de BRIEF
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include "function_opencv.h"
#include "vpBrief.h"
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>

int main( int argc, char* argv[] )
{

    std::cout<<"Test manuel BRIEF"<<std::endl;


    vpImage<unsigned char> img;
    string adresse_image("lena.pgm");
	vpImageIo::read(img, adresse_image);
	vector<vpImagePoint> keypoints = getKeypointsFromOpenCV(adresse_image, 30);

    vpBrief brief;

    std::cout<<"Keypoints : "<<keypoints.size()<<std::endl;

    //long int * tmp[2];
    std::cout<<sizeof(unsigned long)<<std::endl;
    vector<std::bitset<NB_PAIRS> *> descriptors;
    vector<int> descriptors_state;
    brief.computeDescriptors(descriptors, descriptors_state, img, keypoints);
    for (int i=0; i<descriptors.size(); i++) {
        std::cout<<*descriptors[i]<<std::endl;
        std::cout<<descriptors_state[i]<<std::endl;
    }

	vpDisplayX d(img);
	vpDisplay::display(img);
	vpDisplay::flush(img);
	vpDisplay::getClick(img);
    return 0;
}
