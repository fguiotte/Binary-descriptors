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

vpBrief::vpBrief(int nb_pairs) : nb_pairs(nb_pairs) { // Image in constructor ?
    pairs = new std::pair<int,int>[nb_pairs+1]; // +1 or x2 ?
    for (int i=0; i<nb_pairs; i++)      // Same
        if ( i % 2 != 0 ) pairs[i].first = rand(); // % Image height
        else pairs[i].first = rand(); // % Image width
}

vpBrief::~vpBrief() {
    delete[] pairs;
}
