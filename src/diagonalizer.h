#ifndef DIAGONALIZER_H_
#define DIAGONALIZER_H_

#include "Tensorclasses.h"
#include <eigen3/Eigen/Eigenvalues>

class diagonalizer {
public:
	Eigen::MatrixXd transform(Marray<double, 2> Lmatrix);
	Marray<double, 2> transform(Eigen::MatrixXd Ematrix);
	void compute(Marray<double,2> Matrix);
	Eigen::VectorXd sortperm(Eigen::VectorXd Vector);
	Eigen::VectorXd sort(Eigen::VectorXd Vector, Eigen::VectorXd Sortperm);
	Eigen::MatrixXd sort(Eigen::MatrixXd Matrix, Eigen::VectorXd Sortperm);
	Marray<double, 2> Eigenvectors;
	Marray<double, 2> Eigenvalues;

};




#endif /* DIAGONALIZER_H_ */
