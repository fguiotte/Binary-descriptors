/***************************************************************************
 *
 * First BRIEF implementation with Visp
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __VPBRIEF_H__
#define __VPBRIEF_H__

#include <vector>
#include <visp/vpImage.h>

class vpBrief {
    public :
        vpBrief(vpImage<unsigned char> init_im, int nb_pairs=100);
        ~vpBrief();

    private :
        int * pairs;
        int nb_pairs;
};

#endif /* __VPBRIEF_H__ */
