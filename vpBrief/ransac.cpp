/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "ransac.h"
#include <visp/vpColVector.h>
#include <cstdlib>

using std::vector;

void DLT(unsigned int n, const vector<vpImagePoint> & p1, const vector<vpImagePoint> & p2, vpMatrix &H12)
{

#define NBPTMIN 4 
    if(n < NBPTMIN ) {
        std::cout << "there must be at least " << NBPTMIN <<  " points in the both images\n";
        throw ;
    }
    vpMatrix gamma(2*n,9);

    for (int i=0; i<n; i++) {
        gamma[i*2][0] = 0;
        gamma[i*2][1] = 0; 
        gamma[i*2][2] = 0; 

        gamma[i*2][3] = -1 * p1[i].get_u(); 
        gamma[i*2][4] = -1 * p1[i].get_v(); 
        gamma[i*2][5] = -1; 

        gamma[i*2][6] = p2[i].get_v() * p1[i].get_u(); 
        gamma[i*2][7] = p2[i].get_v() * p1[i].get_v(); 
        gamma[i*2][8] = p2[i].get_v(); 

        gamma[i*2+1][0] = p1[i].get_u(); 
        gamma[i*2+1][1] = p1[i].get_v(); 
        gamma[i*2+1][2] = 1; 

        gamma[i*2+1][3] = 0;
        gamma[i*2+1][4] = 0; 
        gamma[i*2+1][5] = 0; 

        gamma[i*2+1][6] = -p2[i].get_u() * p1[i].get_u(); 
        gamma[i*2+1][7] = -p2[i].get_u() * p1[i].get_v(); 
        gamma[i*2+1][8] = -p2[i].get_u(); 
    }

    vpMatrix v;
    vpColVector d;
    gamma.svd(d, v);

    H12[0][0] = v[0][8] / v[8][8];
    H12[0][1] = v[1][8] / v[8][8];
    H12[0][2] = v[2][8] / v[8][8];
    H12[1][0] = v[3][8] / v[8][8];
    H12[1][1] = v[4][8] / v[8][8];
    H12[1][2] = v[5][8] / v[8][8];
    H12[2][0] = v[6][8] / v[8][8];
    H12[2][1] = v[7][8] / v[8][8];
    H12[2][2] = v[8][8] / v[8][8];
    vpMatrix H21 = H12.inverseByLU();
    H12 = H21;
}


void random_my_indexes(std::vector<int> & indexes, int ind_max, int nb_ind) {
    for (int i = 0; i < nb_ind; i++) {
        int new_ind;
        bool notOk;
        do {
        new_ind = std::rand() % ind_max;
        notOk = false;
        for (int j = 0; j < i ; j++)
            if (indexes[j] == new_ind) { 
                notOk = true;
                break;
            }
        } while (notOk);
        indexes.push_back(new_ind);
    }
}

void make_my_points_array(const std::vector<int> & indexes, const std::vector<vpImagePoint> & first_list, const std::vector<vpImagePoint> second_list, vector<vpImagePoint> & first_array, vector<vpImagePoint> & second_array) {
    for (int i = 0; i < indexes.size(); i++) {
        first_array.push_back(first_list[indexes[i]]);
        second_array.push_back(second_list[indexes[i]]);
    }
}

void pointToM(const vpImagePoint & point, vpColVector & pointm) {
    pointm[0] = point.get_u();
    pointm[1] = point.get_v();
    pointm[2] = 1;
}

void MtoPoint(const vpColVector & pointm, vpImagePoint & point) {
    point.set_u(pointm[0]);
    point.set_v(pointm[1]);
}

vpImagePoint point_by_homography(const vpMatrix & H, const vpImagePoint & p1) {
    vpImagePoint p2;

    vpColVector p1m(3);
    pointToM(p1,p1m);

    vpColVector p2m = H * p1m;
    p2m /= p2m[2] ;

    MtoPoint(p2m, p2);
    return p2;
}

vpMatrix ransac_homography(const vector<vpImagePoint> & p1, const vector<vpImagePoint> & p2, int nb_try, int nb_points_h, float epsilon) {
    int best_score = 0;
    vpMatrix best_homo;
    for (int x = 0; x < nb_try; x++) {
        std::vector<int> indexes;
        random_my_indexes(indexes, p1.size(), nb_points_h);
        vector<vpImagePoint> point1_h, point2_h;
        make_my_points_array(indexes, p1, p2, point1_h, point2_h);
        vpMatrix H12(3,3);
        DLT(nb_points_h, point1_h, point2_h, H12);

        int score = 0;
        for (int i = 0; i < p1.size(); i++ ) {
            vpImagePoint point_1_computed = point_by_homography(H12, p2[i]);
            if (p1[i].distance(p1[i], point_1_computed) < epsilon) score ++;
        }

        if (score > best_score) {
            best_homo = H12;
            best_score = score;
        }
    }
    std::cout<<"Best Score : " <<best_score<<std::endl;
    return best_homo;
}

void ransac_full(const vector<vpImagePoint> & p1, const vector<vpImagePoint> & p2, vector<int> & descriptors_state, int nb_try, int nb_points_h, float epsilon) {
    vpMatrix best_homo = ransac_homography(p1, p2, nb_try, nb_points_h, epsilon);

    for (int i = 0; i < p1.size(); i++) {
        vpImagePoint point_1_computed = point_by_homography(best_homo, p2[i]);
        if (p1[i].distance(p1[i], point_1_computed) < epsilon)
            descriptors_state[i] = 3;
        //std::cout<<"State Score : " <<p1[i]<<" -> "<<point_1_computed<<" : "<<p1[i].distance(p1[i], point_1_computed)<<std::endl;
    }
}
