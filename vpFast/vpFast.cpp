#include "vpFast.h"

bool vpFast(vpImage<unsigned char> img, int i,int j, int threshold){
	int north,south,east,west;

	int base=img[i][j];

	north= img[i-3][j];

	south= img[i+3][j];

	east= img[i][j-3];

	west= img[i][j+3];

	//We are testing first with cardinals point on the image
	int primaryTestN = std::abs(north-base);
	int primaryTestS = std::abs(south-base);

	if((primaryTestN>threshold) && (primaryTestS>threshold)){
		int primaryTestE = std::abs(north-threshold);
		int primaryTestW = std::abs(south-threshold);

		int cpt = 2;

		if((primaryTestE > threshold) || (primaryTestW > threshold)){
			int NW,NE,SW,SE;
			if(primaryTestE > threshold){cpt++;}
			if(primaryTestW > threshold){cpt++;}
			NW= img[i-2][j-2];
			NE= img[i-2][j+2];
			SW= img[i+2][j-2];
			SE= img[i+2][j+2];
			
			int primaryTestNW = std::abs(NW-threshold);
			int primaryTestNE = std::abs(NE-threshold);
			int primaryTestSW = std::abs(SW-threshold);
			int primaryTestSE = std::abs(SE-threshold);
				
			if(primaryTestNW>threshold){cpt++;}
			if(primaryTestSW>threshold){cpt++;}
			if(primaryTestNE>threshold){cpt++;}
			if(primaryTestSW>threshold){cpt++;}
	
			if(cpt >= 6){
				return true;
			}
		}
	}
	
	return false;
}
