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

using std::vector;

class vpBrief {
    public :
        vpBrief(int nb_pairs=128, int patch_size=10); // Refactor nb_pairs = sizeof(type[n])
        long double * compute(const vpImage<unsigned char> & image, const vector<vpImagePoint> & keypoints); // Refactor type[n*]
        ~vpBrief();

    private :
        int * pairs;
        const std::size_t nb_pairs;
        int patch_size;
        //const std::size_t N;
};

#endif /* __VPBRIEF_H__ */
