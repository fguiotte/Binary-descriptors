#include "vpGetKeypointFast.h"

vector<vpImagePoint> vpGetKeypointFromFast(vpImage<unsigned char> img,int  threshold)
{
	bool kp;

	int h=img.getHeight();
	int w=img.getWidth();

	vector<vpImagePoint> vpKeypoints;
	// FAST
	for (int i=0; i<h; i++)
	{
		for (int j=0; j<w; j++){
			if(i>4 && i<(h-4)){
				if(j>4 && j<(w-4)){
					kp=vpFast(img, i, j,threshold);
					if(kp){
						vpImagePoint point(i,j);
						vpKeypoints.push_back(point);
					}
				}
			}
		}
	}
	return vpKeypoints;
}
