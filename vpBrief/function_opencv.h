#include <iostream>
#include <opencv2/opencv.hpp>
#include <visp/vpImagePoint.h>

using namespace std;

vector<vpImagePoint> getKeypointsFromOpenCV(string imagePath,int threshold);
