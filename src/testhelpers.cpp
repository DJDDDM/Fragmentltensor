#include <cmath>
#include <LTensor.h>
#include "testhelpers.h"
bool isequal(double first, double second, double thresh){
	return (abs(first - second) < thresh) ? true : false;
}

bool dimensionsequal(Marray<double, 2>first, Marray<double, 2>second){
	if(first.size[0] != second.size[0]) return false;
	if(first.size[1] != second.size[1]) return false;
	return true;
}


bool isequal(Marray<double, 2> first, Marray<double, 2> second, double thresh){
	if (!dimensionsequal(first, second)){
		return false;
	}
	for (int i = 0; i < first.size[0]; i++){
		for (int j = 0; j < first.size[1]; j++){
			if(!isequal(first(i,j),second(i,j),thresh)) return false;
		}
	}
	return true;
}



