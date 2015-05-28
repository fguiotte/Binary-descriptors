/***************************************************************************
 *
 * First BRIEF implementation with Visp
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include <limits>
#include <cstdlib>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>
#include "vpBrief.h"
#include "function_opencv.h"
#include "ransac.h"
#include <visp/vpVideoReader.h>
#include "../vpFast/vpGetKeypointsFast.h"
#include "../vpFast/vpFast.h"

using std::rand;
using std::vector;

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
//                  --- descriptors_state[] ---               
//   TODO: REFACTOR STATE DESCRIPTION
//   0 = Not computed
//   1 = Computed
//   2 = Matched
//   3 = Ransac verified

vpBrief::vpBrief(int nb_pairs, int patch_size) : nb_pairs(nb_pairs), patch_size(patch_size) {
    pairs = new int[nb_pairs*4];
    for (int i=0; i<nb_pairs*4; i++)
        pairs[i] = rand() % (patch_size * 2 + 1) - patch_size;
}

void vpBrief::descriptorBit(const vpImage<unsigned char> & image, std::bitset<VPBRIEF_NB_PAIRS> & descriptor, vector<vpImagePoint>::const_iterator & it, int * pairs, int i) {
    int u1 = it->get_u() + pairs[i*4+0];
    int v1 = it->get_v() + pairs[i*4+1];
    int u2 = it->get_u() + pairs[i*4+2];
    int v2 = it->get_v() + pairs[i*4+3];
    bool res = (image[u1][v1] > image[u2][v2]);
    descriptor[0] = res;
}

void vpBrief::computeDescriptors(std::vector<std::bitset<VPBRIEF_NB_PAIRS> *> & descriptors, std::vector<int> & descriptors_state, const vpImage<unsigned char> & image, const vector<vpImagePoint> & keypoints) { 
    for (vector<vpImagePoint>::const_iterator it = keypoints.begin(); it!=keypoints.end(); it++) {
        std::bitset<VPBRIEF_NB_PAIRS> * newDescriptor = new std::bitset<VPBRIEF_NB_PAIRS>;
        if (it->get_u() > patch_size && it->get_u() < image.getHeight() - patch_size && it->get_v() > patch_size && it->get_v() < image.getWidth() - patch_size) { // Border conditions; please refactor
            for (int i=0; i<nb_pairs-1; i++) {
                descriptorBit(image, *newDescriptor, it, pairs, i);
                *newDescriptor <<= 1;
            }
            descriptorBit(image, *newDescriptor, it, pairs, nb_pairs-1);
            descriptors_state.push_back(1);
        } else {
            descriptors_state.push_back(0);
        }
        descriptors.push_back(newDescriptor);
    }
}

int vpBrief::hamming_distance(const std::bitset<VPBRIEF_NB_PAIRS> & first, const std::bitset<VPBRIEF_NB_PAIRS> & second) {
    std::bitset<VPBRIEF_NB_PAIRS> xor_val = first xor second;
    return xor_val.count();
}

void vpBrief::match(vector<int> & similarity, const vpImage<unsigned char> & first_image, const vector<vpImagePoint> & first_keypoints, const vpImage<unsigned char> & second_image, const vector<vpImagePoint> & second_keypoints, vector<int> & first_descriptors_state, vector<int> & second_descriptors_state) {
    vector<std::bitset<VPBRIEF_NB_PAIRS> *> first_descriptors;
    vector<std::bitset<VPBRIEF_NB_PAIRS> *> second_descriptors;
//    vector<int> first_descriptors_state;
//    vector<int> second_descriptors_state;

    computeDescriptors(first_descriptors, first_descriptors_state, first_image, first_keypoints);
    computeDescriptors(second_descriptors, second_descriptors_state, second_image, second_keypoints);

    for (int first_i = 0; first_i < first_keypoints.size(); first_i++) {
        int distance_min = std::numeric_limits<int>::max();
        int second_i_min;

        if (first_descriptors_state[first_i] == 0) {
            similarity.push_back(-1);
            continue;
        }

        for (int second_i = 0; second_i < second_keypoints.size(); second_i++) {
            if (second_descriptors_state[second_i] == 0) continue;
            int distance = hamming_distance(*first_descriptors[first_i], *second_descriptors[second_i]);
            if (distance < distance_min) {
                second_i_min = second_i;
                distance_min = distance;
            }
        }
        first_descriptors_state[first_i] = second_descriptors_state[second_i_min] = 2;
        similarity.push_back(second_i_min);
    }
}

void vpBrief::showMatching(const vpImage<unsigned char> & first_image, const vpImage<unsigned char> & second_image) {
}


//void vpBrief::demo(const std::string & first_image_str, const std::string & second_image_str) {
void vpBrief::demo(const vpImage<unsigned char> & first_image, const vpImage<unsigned char> & second_image) {
    double t0= vpTime::measureTimeMs();
	vector<vpImagePoint> first_keypoints = vpGetKeypointsFromFast(first_image, 30, 50);
	vector<vpImagePoint> second_keypoints = vpGetKeypointsFromFast(second_image, 30, 50);
	//vector<vpImagePoint> first_keypoints = getKeypointsFromOpenCV(first_image_str, 30);
	//vector<vpImagePoint> second_keypoints = getKeypointsFromOpenCV(second_image_str, 30);
    std::cout<<"Keypoints in first image : "<<first_keypoints.size()<<std::endl<<"Keypoints in second image : "<<second_keypoints.size()<<std::endl;

//    vpImage<unsigned char> first_image;
//    vpImage<unsigned char> second_image;
//	vpImageIo::read(first_image, first_image_str);
//	vpImageIo::read(second_image, second_image_str);

    vpImage<unsigned char> demo_image(max(first_image.getHeight(), second_image.getHeight()), second_image.getWidth() + second_image.getWidth());
    for (int i = 0; i < first_image.getHeight(); i++) 
        for (int j = 0; j < first_image.getWidth(); j++)
            demo_image[i][j] = first_image[i][j];
    for (int i = 0; i < second_image.getHeight(); i++) 
        for (int j = 0; j < second_image.getWidth(); j++)
            demo_image[i][first_image.getWidth() + j] = second_image[i][j];

    vector<int> similarity, first_descriptors_state, second_descriptors_state;
    match(similarity, first_image, first_keypoints, second_image, second_keypoints, first_descriptors_state, second_descriptors_state);
    ransac_full(first_keypoints, second_keypoints, first_descriptors_state,500,5,3);//, 1000, 5, 100); 
    double t1= vpTime::measureTimeMs();
    std::cout<<t1-t0<<" ms"<<std::endl;

	vpDisplayX d(demo_image);
	vpDisplay::display(demo_image);

    for (int i = 0; i < similarity.size(); i++) {
        if (first_descriptors_state[i] == 0) 
            vpDisplay::displayCross(demo_image, first_keypoints[i], 5, vpColor::yellow);
        else if (first_descriptors_state[i] == 1)
            vpDisplay::displayCross(demo_image, first_keypoints[i], 5, vpColor::blue);
        else if (second_descriptors_state[i] == 0)
            vpDisplay::displayCross(demo_image, first_keypoints[i], 5, vpColor::orange);
        else if (first_descriptors_state[i] == 2) {
            vpImagePoint demo_image_second_point(second_keypoints[similarity[i]].get_i(), second_keypoints[similarity[i]].get_j() + first_image.getWidth());
            vpDisplay::displayLine(demo_image, first_keypoints[i], demo_image_second_point, vpColor::red);
            //vpDisplay::displayLine(demo_image, first_keypoints[i], demo_image_second_point, vpColor(rand()%255,rand()%255,rand()%255));
        } else if (first_descriptors_state[i] == 3) {
            vpImagePoint demo_image_second_point(second_keypoints[similarity[i]].get_i(), second_keypoints[similarity[i]].get_j() + first_image.getWidth());
            //vpDisplay::displayLine(demo_image, first_keypoints[i], demo_image_second_point, vpColor(rand()%255,rand()%255,rand()%255));
            vpDisplay::displayLine(demo_image, first_keypoints[i], demo_image_second_point, vpColor::lightGreen);
        }
    }

	vpDisplay::flush(demo_image);
	vpDisplay::getClick(demo_image);

    /*
    string videoPath = "./ksp.mpg";

    vpImage<unsigned char> imgSource;
    vpVideoReader reader;
    reader.setFileName(videoPath);
    reader.open(imgSource);
    cout<< "video name : "<< videoPath <<endl;
    cout<< "video framerate : "<< reader.getFramerate() << "Hz" <<endl;
    cout<< "video dimension : "<< imgSource.getWidth() << " " << imgSource.getHeight()<<endl;
    
    vpDisplayX dv(imgSource);
    vpDisplay::setTitle(imgSource, "Video reader");
    double playSpeed = 500.0;

    while( true ) {
        double t = vpTime::measureTimeMs();
            
        reader.acquire(imgSource);
            
        vpDisplay::display(imgSource);
        vpDisplay::flush(imgSource);
        if(vpDisplay::getClick(imgSource, false)) { break; }
        vpTime::wait(t, playSpeed /reader.getFramerate());
    }
    reader.close();
    */

}

void vpBrief::demo_video(const std::string & videoPath) {
    vpImage<unsigned char> first_image, second_image;
    vpVideoReader reader;
    reader.setFileName(videoPath);
    reader.open(second_image);
    cout<< "video name : "<< videoPath <<endl;
    cout<< "video framerate : "<< reader.getFramerate() << "Hz" <<endl;
    cout<< "video dimension : "<< second_image.getWidth() << " " << second_image.getHeight()<<endl;
    
    vpDisplayX dv(second_image);
    vpDisplay::setTitle(second_image, "Video reader");
    double playSpeed = 1000.0;
    reader.acquire(second_image);

    first_image = second_image;
	vector<vpImagePoint> first_keypoints = vpGetKeypointsFromFast(first_image, 10, 150);

    vpImage<unsigned char> demo_image(max(first_image.getHeight(), second_image.getHeight()), second_image.getWidth() + second_image.getWidth());
	vpDisplayX d(demo_image);
	vpDisplay::display(demo_image);
    while( true ) {
        double t = vpTime::measureTimeMs();
            
        reader.acquire(second_image);
            
        double t0= vpTime::measureTimeMs();
        vector<vpImagePoint> second_keypoints = vpGetKeypointsFromFast(second_image, 10, 150);

        for (int i = 0; i < first_image.getHeight(); i++) 
            for (int j = 0; j < first_image.getWidth(); j++)
                demo_image[i][j] = first_image[i][j];
        for (int i = 0; i < second_image.getHeight(); i++) 
            for (int j = 0; j < second_image.getWidth(); j++)
                demo_image[i][first_image.getWidth() + j] = second_image[i][j];

        vector<int> similarity, first_descriptors_state, second_descriptors_state;
        match(similarity, first_image, first_keypoints, second_image, second_keypoints, first_descriptors_state, second_descriptors_state);
        ransac_full(first_keypoints, second_keypoints, first_descriptors_state,50,5,3);//, 1000, 5, 100); 
        double t1= vpTime::measureTimeMs();
        std::cout<<t1-t0<<" ms"<<std::endl;


        vpDisplay::display(demo_image);
        for (int i = 0; i < similarity.size(); i++) {
            if (first_descriptors_state[i] == 0) 
                vpDisplay::displayCross(demo_image, first_keypoints[i], 5, vpColor::yellow);
            else if (first_descriptors_state[i] == 1)
                vpDisplay::displayCross(demo_image, first_keypoints[i], 5, vpColor::blue);
            else if (second_descriptors_state[i] == 0)
                vpDisplay::displayCross(demo_image, first_keypoints[i], 5, vpColor::orange);
            else if (first_descriptors_state[i] == 2) {
                vpImagePoint demo_image_second_point(second_keypoints[similarity[i]].get_i(), second_keypoints[similarity[i]].get_j() + first_image.getWidth());
                vpDisplay::displayLine(demo_image, first_keypoints[i], demo_image_second_point, vpColor::red);
                //vpDisplay::displayLine(demo_image, first_keypoints[i], demo_image_second_point, vpColor(rand()%255,rand()%255,rand()%255));
            } else if (first_descriptors_state[i] == 3) {
                vpImagePoint demo_image_second_point(second_keypoints[similarity[i]].get_i(), second_keypoints[similarity[i]].get_j() + first_image.getWidth());
                //vpDisplay::displayLine(demo_image, first_keypoints[i], demo_image_second_point, vpColor(rand()%255,rand()%255,rand()%255));
                vpDisplay::displayLine(demo_image, first_keypoints[i], demo_image_second_point, vpColor::lightGreen);
            }
        }



        vpDisplay::flush(demo_image);
        if(vpDisplay::getClick(demo_image, false)) { break; }
        vpTime::wait(t, playSpeed /reader.getFramerate());
    }
    reader.close();
}

vpBrief::~vpBrief() {
    delete[] pairs;
}
