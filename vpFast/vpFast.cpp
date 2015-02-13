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

		if((primaryTestE > threshold) || (primaryTestW > threshold)){
			return true;
		}
	}
	
	return false;
}
