
#include <iostream>
#include <vector>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>
#include "vpGetKeypointFast.h"
#include <visp/vpImageFilter.h>
#include <visp/vpImageConvert.h>

#include <visp/vpTime.h>
#include <visp/vpVideoReader.h>

using namespace std;

void color_keypoints(vpImage<vpRGBa> & imgSource, const int threshold = 30)
{

  // convertir l'image vpRGBa en unsigned char
  vpImage<unsigned char> imgChar;
  vpImageConvert::convert(imgSource, imgChar);
    
  // flouter l'image de source pour réduire du bruit
  vpImage<double> imgfloutee;
	vpImageFilter::gaussianBlur(imgChar, imgfloutee);
	vpImageConvert::convert(imgfloutee, imgChar);
	
	// récupération des points d'intérèts dans un vecteur
	vector<vpImagePoint> keypoints = vpGetKeypointFromFast(imgChar, threshold);


	// afficher les points caractéristiques en crois rouge
	for(size_t i = 0; i < keypoints.size(); i++)
	{
		const vpImagePoint &kp = keypoints[i];
		vpRGBa red(255,0,0);
		imgSource[(int)kp.get_i()-1][(int)kp.get_j()] = red;
		imgSource[(int)kp.get_i()][(int)kp.get_j()-1] = red;
		imgSource[(int)kp.get_i()][(int)kp.get_j()]   = red;
		imgSource[(int)kp.get_i()][(int)kp.get_j()+1] = red;
		imgSource[(int)kp.get_i()+1][(int)kp.get_j()] = red;
	}
}

void char_keypoints(vpImage<unsigned char> & imgSource, vpImage<vpRGBa> & imgColor, const int threshold = 30) {
    
  // flouter l'image de source pour réduire du bruit
  vpImage<double> imgfloutee;
	vpImageFilter::gaussianBlur(imgSource, imgfloutee);
	vpImageConvert::convert(imgfloutee, imgSource);
	
	// récupération des points d'intérèts dans un vecteur
	vector<vpImagePoint> keypoints = vpGetKeypointFromFast(imgSource, threshold);

	// afficher les points caractéristiques en crois rouge
	vpImageConvert::convert(imgSource, imgColor);
	for(size_t i = 0; i < keypoints.size(); i++)
	{
		const vpImagePoint &kp = keypoints[i];
		vpRGBa red(255,0,0);
		imgColor[(int)kp.get_i()-1][(int)kp.get_j()] = red;
		imgColor[(int)kp.get_i()][(int)kp.get_j()-1] = red;
		imgColor[(int)kp.get_i()][(int)kp.get_j()]   = red;
		imgColor[(int)kp.get_i()][(int)kp.get_j()+1] = red;
		imgColor[(int)kp.get_i()+1][(int)kp.get_j()] = red;
	}
}


int main(int argc, char** argv)
{
  string videoPath = "../images/babypandas.mpg";
    
  vpImage<vpRGBa> imgSource;
  vpVideoReader reader;
  reader.setFileName(videoPath);
  reader.open(imgSource);
  cout<< "video name : "<< videoPath <<endl;
  cout<< "video framerate : "<< reader.getFramerate() << "Hz" <<endl;
  cout<< "video dimension : "<< imgSource.getWidth() << " " << imgSource.getHeight()<<endl;
    
  vpDisplayX dv(imgSource);
  vpDisplay::setTitle(imgSource, "Video reader");
  double playSpeed = 2000.0;
  while( true )
	{
    
    double t = vpTime::measureTimeMs();
        
    reader.acquire(imgSource);
        
    color_keypoints(imgSource);
        
		vpDisplay::display(imgSource);
	  vpDisplay::flush(imgSource);
	  if(vpDisplay::getClick(imgSource, false)) { break; }
	  vpTime::wait(t, playSpeed /reader.getFramerate());
	}
  reader.close();
    
    
  /*
	string imagePath = "../images/img1.ppm";
	vpImage<vpRGBa> imgColor;
	vpImage<unsigned char> imgSource;
	
	
	vpImageIo::read(imgColor, imagePath);
	color_keypoints(imgColor);
	
	
	//vpImageIo::read(imgSource, imagePath);
	//char_keypoints(imgSource, imgColor);
	

	vpDisplayX d(imgColor);
	vpDisplay::display(imgColor);
	vpDisplay::flush(imgColor);
	vpDisplay::getClick(imgColor);
	*/
	
}
