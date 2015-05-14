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
#include <bitset>
#define NB_PAIRS 256 // TODO: compilation option

class vpBrief {
    public :
        vpBrief(int nb_pairs=NB_PAIRS, int patch_size=10); // Refactor nb_pairs = sizeof(type[n])
        std::vector<std::bitset<NB_PAIRS> *> * computeDescriptors(const vpImage<unsigned char> & image, const std::vector<vpImagePoint> & keypoints); 
        void computeDescriptors(std::vector<std::bitset<NB_PAIRS> *> & descriptors, const vpImage<unsigned char> & image, const std::vector<vpImagePoint> & keypoints); // TODO Refactor take into account user defined nb_pairs (see boost, bitmagic)

        ~vpBrief();

    private :
        int * pairs;
        const int nb_pairs;
        int patch_size;
        //const std::size_t N;
        void descriptorBit(const vpImage<unsigned char> & image, std::bitset<NB_PAIRS> & descriptor, std::vector<vpImagePoint>::const_iterator & it, int * pairs, int i);
};

#endif /* __VPBRIEF_H__ */
