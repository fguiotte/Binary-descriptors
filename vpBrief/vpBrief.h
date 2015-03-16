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

class vpBrief {
    public :
        vpBrief(int nb_pairs=100);
        ~vpBrief();

    private :
        std::pair<int,int> * pairs;
        int nb_pairs;
};

#endif /* __VPBRIEF_H__ */
