 #include <iostream>
#include <vector>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>
#include "vpFast.h"

using namespace std;

vector<vpImagePoint> vpGetKeypointFromFast(vpImage<vpRGBa> img,int threshold);
