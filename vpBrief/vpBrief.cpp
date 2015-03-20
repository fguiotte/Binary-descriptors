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

vpBrief::vpBrief(vpImage<unsigned char> init_im, int nb_pairs) : nb_pairs(nb_pairs) { // Image in constructor ? or height/width
    pairs = new int[nb_pairs*4];
    for (int i=0; i<nb_pairs*4; i++)
        if ( i % 2 != 0 ) pairs[i] = rand() % init_im.getHeight(); // % Image height
        else pairs[i] = rand() % init_im.getWidth(); // % Image width
}

vpBrief::~vpBrief() {
    delete[] pairs;
}
