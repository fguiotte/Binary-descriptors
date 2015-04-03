/***************************************************************************
 *
 * First BRIEF implementation with Visp
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include <cstdlib>
#include <bitset>
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

long double * vpBrief::compute(const vpImage<unsigned char> & image, const vector<vpImagePoint> & keypoints) { 
    long double * descriptor = new long double[keypoints.size()];
    unsigned long * descriptors = new unsigned long[keypoints.size()];
//    const unsigned long tmp(nb_pairs);
//    const int inter(nb_pairs);
//    const std::size_t N(inter);
    std::bitset<nb_pairs> desc ;//= new std::bitset<nb_pairs>[keypoints.size()];

    int n = 0;
    for (vector<vpImagePoint>::const_iterator it = keypoints.begin(); it!=keypoints.end(); it++) {
        descriptors[n] = 0;
        if (it->get_u() > patch_size && it->get_u() < image.getHeight() - patch_size && it->get_v() > patch_size && it->get_v() < image.getWidth() - patch_size)
            for (int i=0; i<nb_pairs; i++) {
                int u1 = it->get_u() + pairs[i*4+0];
                int v1 = it->get_v() + pairs[i*4+1];
                int u2 = it->get_u() + pairs[i*4+2];
                int v2 = it->get_v() + pairs[i*4+3];
                bool res = (image[u1][v1] > image[u2][v2]);
                //bool res = (image[it->get_u()+pairs[i*4+0]][it->get_v()+pairs[i*4+1]] - image[pairs[i*4+2]][pairs[i*4+3]]) > 0;
                //descriptor[n] += res << 1;
                desc[0] = res;
                desc <<= 1;
                //descriptors[n] = descriptors[n] << 1;
            }
            //unsigned long x = descriptors[n];
            std::cout<<desc<<std::endl;
//            for (int k=0; k<sizeof(x)*8; k++) {
//                if (x & 1)
//                    printf("1");
//                else
//                    printf("0");
//
//                x >>= 1;
//            }
//            printf("\n");
        n++;
    }

    return descriptor;
//        for (int i=0; i<image.getHeight(); i++)
//            for (int j=0; j<image.getWidth(); j++)
//        for (int k=0;
//                image[
}

vpBrief::~vpBrief() {
    delete[] pairs;
}
