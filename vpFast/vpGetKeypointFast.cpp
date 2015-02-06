#include "vpGetKeypointFast.h"

vector<vpImagePoint> vpGetKeypointFromFast(vpImage<vpRGBa> img,int  threshold)
{
	bool kp;
	int n=0;
	vector<vpImagePoint> vpKeypoints;
	// Utilisation de FAST
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++){
			kp=vpFast(img, i, j);
			if(kp){
				vpImagePoint point(i,j);
				vpKeypoints.push_back(point);	
			}
		}
	}

	
	return vpKeypoints;
}
