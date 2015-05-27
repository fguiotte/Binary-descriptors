/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __RANSAC_H__
#define __RANSAC_H__

#include <vector>
#include <visp/vpImagePoint.h>
#include <visp/vpMatrix.h>

void DLT(unsigned int n, const std::vector<vpImagePoint> & p1, const std::vector<vpImagePoint> & p2, vpMatrix &H12);
void random_my_indexes(std::vector<int> & indexes, int ind_max, int nb_ind);
void make_my_points_array(const std::vector<int> & indexes, const std::vector<vpImagePoint> & first_list, const std::vector<vpImagePoint> second_list, std::vector<vpImagePoint> & first_array, std::vector<vpImagePoint> & second_array);
void pointToM(const vpImagePoint & point, vpColVector & pointm);
void MtoPoint(const vpColVector & pointm, vpImagePoint & point);
vpImagePoint point_by_homography(const vpMatrix & H, const vpImagePoint & p1);
vpMatrix ransac_homography(const std::vector<vpImagePoint> & p1, const std::vector<vpImagePoint> & p2, int nb_try = 100, int nb_points_h = 5, float epsilon = 15);
void ransac_full(const std::vector<vpImagePoint> & p1, const std::vector<vpImagePoint> & p2, std::vector<int> & descriptors_state, int nb_try = 100, int nb_points_h = 5, float epsilon = 15);

#endif /* __RANSAC_H__ */
