#ifndef TESTHELPERS_H_
#define TESTHELPERS_H_

bool isequal(double first, double second, double thresh);
bool isequal(Marray<double, 2> first, Marray<double, 2> second, double thresh);
Marray<double, 2> fillmatrix(int dim1, int dim2);


#endif /* TESTHELPERS_H_ */
