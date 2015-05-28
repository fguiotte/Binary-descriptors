#include "vpGetKeypointsFast.h"
#include <visp/vpImageFilter.h>

double harrisCornerness(vpImage<unsigned char> &img, vpImagePoint pt)
{
	double grad_x, grad_y;
	vpMatrix A(2,2);

	// Evaluating the autocorrelation matrix
	grad_x = vpImageFilter::derivativeFilterX(img, pt.get_i(), pt.get_j());
	grad_y = vpImageFilter::derivativeFilterY(img, pt.get_i(), pt.get_j());
	
	A[0][0] = grad_x*grad_x;
	A[0][1] = grad_x*grad_y;
	A[1][0] = grad_x*grad_y;
	A[1][1] = grad_y*grad_y;

	// Evaluating Harris measure
	vpColVector vecEigenValues;
	vecEigenValues = A.eigenValues();
	
	return vecEigenValues[0] * vecEigenValues[1] - (vecEigenValues[0] + vecEigenValues[1]) * (vecEigenValues[0] + vecEigenValues[1]);

}

vector<vpImagePoint> vpGetKeypointsFromFast(vpImage<unsigned char> &img, int threshold, int nbKeypoints)
{
	bool kp;
	double harris;
	int h=img.getHeight();
	int w=img.getWidth();

	vector<vpImagePoint> vpKeypoints;
	vector<double> vHarrisKeypoints;
	// FAST
	for (int i=0; i<h; i++)
	{
		for (int j=0; j<w; j++)
		{
			if(i>4 && i<(h-4))
			{
				if(j>4 && j<(w-4))
				{
					kp=vpFast(img, i, j, threshold);
					if(kp)
					{
						vpImagePoint point(i,j);
						harris = harrisCornerness(img, point);
						// vpKeypoints = decreasing order
						if(vHarrisKeypoints.empty() && vpKeypoints.empty())
						{
							vpKeypoints.push_back(point);
							vHarrisKeypoints.push_back(harris);
						}
						else if(vHarrisKeypoints.back() > harris)
						{
							int k = 0;
							for(k = vHarrisKeypoints.size() - 1; k > 0 && vHarrisKeypoints[k] > harris; k--)
							{
							}
							std::vector<vpImagePoint>::iterator itKeypoints = vpKeypoints.begin();
							std::vector<double>::iterator itHarris = vHarrisKeypoints.begin();
							std::advance(itKeypoints, k);
							std::advance(itHarris, k);

							vpKeypoints.insert(itKeypoints, point);
							vHarrisKeypoints.insert(itHarris, harris);
							if(vHarrisKeypoints.size() > nbKeypoints)
							{
								itKeypoints = vpKeypoints.end();
								itHarris = vHarrisKeypoints.end();
								vpKeypoints.erase(itKeypoints-1);
								vHarrisKeypoints.erase(itHarris-1);
							}
						}
					}	
				}	
			}
		}
	}	 
	return vpKeypoints;
}
