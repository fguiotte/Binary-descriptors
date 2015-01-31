#include "vpGetKeypointFast.h"

vector<vpImagePoint> getKeypointFromFast(vpImage<vpRGBa> img,int  threshold)
{
	bool kp;
	vector<vpImagePoint> vpKeypoints;
	// Utilisation de FAST
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++){
			kp=vpFast(img, i, j)
			if(kp){
				vpImagePoint point(img[i],img[j]);
				pKeypoints.push_back(point);	
			}
		}
	}

	
	return vpKeypoints;
}
