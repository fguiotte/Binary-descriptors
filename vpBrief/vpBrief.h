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
        vpBrief(int nb_pairs=100, int patch_size=10);
        ~vpBrief();

    private :
        int * pairs;
        int nb_pairs;
        int patch_size;
};

#endif /* __VPBRIEF_H__ */
