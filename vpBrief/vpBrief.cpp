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
using std::vector;

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

std::vector<std::bitset<NB_PAIRS> *> * vpBrief::computeDescriptors(const vpImage<unsigned char> & image, const vector<vpImagePoint> & keypoints) { 
    std::vector<std::bitset<NB_PAIRS> *> * desc = new std::vector<std::bitset<NB_PAIRS> *>;

    for (vector<vpImagePoint>::const_iterator it = keypoints.begin(); it!=keypoints.end(); it++) {
        std::bitset<NB_PAIRS> * newDescriptor = new std::bitset<NB_PAIRS>;
        *newDescriptor = 0;
        if (it->get_u() > patch_size && it->get_u() < image.getHeight() - patch_size && it->get_v() > patch_size && it->get_v() < image.getWidth() - patch_size) { // Border conditions; please refactor
            for (int i=0; i<nb_pairs-1; i++) {
                descriptorBit(image, *newDescriptor, it, pairs, i);
                *newDescriptor <<= 1;
            }
            descriptorBit(image, *newDescriptor, it, pairs, nb_pairs-1);
        }
        desc->push_back(newDescriptor);
    }
    return desc;
}

vpBrief::~vpBrief() {
    delete[] pairs;
}
