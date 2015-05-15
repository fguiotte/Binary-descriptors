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
#define VPBRIEF_NB_PAIRS 256 // TODO: compilation option

class vpBrief {
    public :
        vpBrief(int nb_pairs=VPBRIEF_NB_PAIRS, int patch_size=10); // Refactor nb_pairs = sizeof(type[n])
        std::vector<std::bitset<VPBRIEF_NB_PAIRS> *> * computeDescriptors(const vpImage<unsigned char> & image, const std::vector<vpImagePoint> & keypoints); 
        void computeDescriptors(std::vector<std::bitset<VPBRIEF_NB_PAIRS> *> & descriptors, std::vector<int> & descriptors_state, const vpImage<unsigned char> & image, const std::vector<vpImagePoint> & keypoints); // TODO Refactor take into account user defined nb_pairs (see boost, bitmagic)
        void match(std::vector<int> & similarity, const vpImage<unsigned char> & first_image, const std::vector<vpImagePoint> & first_keypoints, const vpImage<unsigned char> & second_image, const std::vector<vpImagePoint> & second_keypoints);
        void showMatching(const vpImage<unsigned char> & first_image, const vpImage<unsigned char> & second_image);
        void demo(const std::string & first_image_str, const std::string & second_image_str);

        ~vpBrief();

    private :
        int * pairs;
        const int nb_pairs;
        int patch_size;
        //const std::size_t N;
        void descriptorBit(const vpImage<unsigned char> & image, std::bitset<VPBRIEF_NB_PAIRS> & descriptor, std::vector<vpImagePoint>::const_iterator & it, int * pairs, int i);
        int hamming_distance(const std::bitset<VPBRIEF_NB_PAIRS> & first, const std::bitset<VPBRIEF_NB_PAIRS> & second);
};

#endif /* __VPBRIEF_H__ */
