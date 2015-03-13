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
				int N1,N2,W1,W2,S1,S2,E1,E2;

				N1=img[i-3][j-1];
				N2=img[i-3][j+1];
				W1=img[i-1][j+3];
				W2=img[i+1][j+3];
				S1=img[i+3][j-1];
				S2=img[i+3][j+1];
				E1=img[i-1][j-3];
				E2=img[i+1][j-3];

				int TestN1 = std::abs(N1-threshold);
				int TestN2 = std::abs(N2-threshold);
				int TestW1 = std::abs(W1-threshold);
				int TestW2 = std::abs(W2-threshold);
				int TestS1 = std::abs(S1-threshold);
				int TestS2 = std::abs(S2-threshold);
				int TestE1 = std::abs(E1-threshold);
				int TestE2 = std::abs(E2-threshold);


				if(TestN1>threshold){cpt++;}
				if(TestN2>threshold){cpt++;}
				if(TestW1>threshold){cpt++;}
				if(TestW2>threshold){cpt++;}
				if(TestS1>threshold){cpt++;}
				if(TestS2>threshold){cpt++;}
				if(TestE1>threshold){cpt++;}
				if(TestE2>threshold){cpt++;}
				
				if(cpt>=12){
					while (1){
						int cptIsNeighbor,cptOut;
					}
					return true;
				}
			}
		}
	}
	
	return false;
}
