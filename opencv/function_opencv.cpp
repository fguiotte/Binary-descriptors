#include "function_opencv.h"

vector<vpImagePoint> getKeypointsFromOpenCV(string imagePath,int  threshold)
{
	// Iniatialisation de l'image en OpenCV
	cv::Mat image = cv::imread(imagePath);
	cv::Mat gray;
	cv::cvtColor(image, gray, CV_BGR2GRAY);
	cv::vector<cv::KeyPoint> keypoints;
	// Utilisation de FAST
	cv::FAST(gray, keypoints, threshold);

	// Conversion des Keypoints d'OpenCV vers ViSP
	vector<vpImagePoint> vpKeypoints;
	for(size_t i=0; i<keypoints.size(); i++)
	{
		vpImagePoint point(keypoints[i].pt.y, keypoints[i].pt.x);	
		vpKeypoints.push_back(point);
	}
	return vpKeypoints;
}
