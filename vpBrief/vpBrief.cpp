/***************************************************************************
 *
 * First BRIEF implementation with Visp
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include <cstdlib>
#include "vpBrief.h"

using std::rand;

//   
//                  --- pairs[] ---               
//   first pt                                     
//   <----->                                      
//                                                
//   +--+--+--+--+--+--+--+--+-------------------+
//   |x0|y0|x1|y1|x2|y2|x3|y3|                   |
//   +--+--+--+--+--+--+--+--+-------------------+
//                                                
//   <----------->                                
//    first pair                                  
//   

vpBrief::vpBrief(int nb_pairs, int patch_size) : nb_pairs(nb_pairs), patch_size(patch_size) {
    pairs = new int[nb_pairs*4];
    for (int i=0; i<nb_pairs*4; i++)
        pairs[i] = rand() % (patch_size * 2 + 1) - patch_size;
}

void vpBrief::descriptorBit(const vpImage<unsigned char> & image, std::bitset<NB_PAIRS> & descriptor, vector<vpImagePoint>::const_iterator & it, int * pairs, int i) {
    int u1 = it->get_u() + pairs[i*4+0];
    int v1 = it->get_v() + pairs[i*4+1];
    int u2 = it->get_u() + pairs[i*4+2];
    int v2 = it->get_v() + pairs[i*4+3];
    bool res = (image[u1][v1] > image[u2][v2]);
    descriptor[0] = res;
}

std::bitset<NB_PAIRS> * vpBrief::compute(const vpImage<unsigned char> & image, const vector<vpImagePoint> & keypoints) { 
    std::bitset<NB_PAIRS> * desc = new std::bitset<NB_PAIRS>[keypoints.size()];

    int n = 0;
    for (vector<vpImagePoint>::const_iterator it = keypoints.begin(); it!=keypoints.end(); it++) {
        desc[n] = 0;
        if (it->get_u() > patch_size && it->get_u() < image.getHeight() - patch_size && it->get_v() > patch_size && it->get_v() < image.getWidth() - patch_size) {
            for (int i=0; i<nb_pairs-1; i++) {
                descriptorBit(image, desc[n], it, pairs, i);
                desc[n] <<= 1;
            }
            descriptorBit(image, desc[n], it, pairs, nb_pairs-1);
        }
        std::cout<<desc[n]<<std::endl;
        n++;
    }
    return desc;
}

vpBrief::~vpBrief() {
    delete[] pairs;
}
