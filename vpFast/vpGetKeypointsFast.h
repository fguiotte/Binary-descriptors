#include <iostream>
#include <vector>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>
#include "vpFast.h"

vector<vpImagePoint> vpGetKeypointsFromFast(const vpImage<unsigned char> &img, int threshold, int nbKeypoints);
double harrisCornerness(const vpImage<unsigned char> &img, vpImagePoint pt);
