#include "diagonalizer.h"

Eigen::MatrixXd diagonalizer::transform(Marray<double, 2> Lmatrix){
	Eigen::MatrixXd Ematrix(Lmatrix.size[0],Lmatrix.size[1]);
	for (int i = 0; i < Lmatrix.size[0]; i++){
		for (int j = 0; j < Lmatrix.size[1]; j++){
			Ematrix(i,j) = Lmatrix(i,j);
		}
	}
	return Ematrix;
}

Marray<double, 2> diagonalizer::transform(Eigen::MatrixXd Ematrix){
	Marray<double,2 > Lmatrix(Ematrix.cols(), Ematrix.rows());
	for (int i = 0; i < Ematrix.cols(); i++){
		for (int j = 0; j < Ematrix.rows(); j++){
			Lmatrix(i,j) = Ematrix(i,j);
		}
	}
	return Lmatrix;
}

void diagonalizer::compute(Marray<double, 2> Matrix){
	Eigen::MatrixXd Eigenmatrix = transform(Matrix);

	Eigen::EigenSolver<Eigen::MatrixXd> Eigenobject(Eigenmatrix);
	Eigen::MatrixXd EigenvectorsMatrix = Eigenobject.pseudoEigenvectors();
	Eigen::MatrixXd EigenvaluesMatrix = Eigenobject.pseudoEigenvalueMatrix();

	Eigen::VectorXd Eigenvaluesvector = EigenvaluesMatrix.diagonal();
	Eigen::VectorXd Sortperm = sortperm(Eigenvaluesvector);
	Eigen::VectorXd sortedEigenvalues = sort(Eigenvaluesvector, Sortperm);
	Eigen::MatrixXd sortedEigenvectors = sort(EigenvectorsMatrix, Sortperm);



	Eigenvectors = transform(sortedEigenvectors);
	Eigenvalues = transform(sortedEigenvalues.asDiagonal());
}

Eigen::VectorXd diagonalizer::sortperm(Eigen::VectorXd Vector){
	Eigen::VectorXd Sortperm(Vector.rows());
	double store;
	for (int i = 0; i < Vector.rows(); i++){
		Sortperm(i) = i;
	}
	for (int j = 0; j < Vector.rows(); j++){
	for (int i = j-1; i >= 0; i--){
		if (Vector(i) > Vector(i+1)){
				store = Vector(i);
				Vector(i) = Vector(i+1);
				Vector(i+1) = store;

				store = Sortperm(i);
				Sortperm(i) = Sortperm(i+1);
				Sortperm(i+1) = store;
			}
		}
	}
	return Sortperm;
}

Eigen::VectorXd diagonalizer::sort(Eigen::VectorXd Vector, Eigen::VectorXd Sortperm){
	Eigen::VectorXd sortedVector(Vector.rows());
	for (int i = 0; i < Vector.rows() ; i++){
		sortedVector(i) = Vector(Sortperm(i));
	}
	return sortedVector;
}

Eigen::MatrixXd diagonalizer::sort(Eigen::MatrixXd Matrix, Eigen::VectorXd Sortperm){
	Eigen::MatrixXd sortedMatrix(Matrix.cols(),Matrix.rows());
	for (int i = 0; i < Matrix.cols() ; i++){
		sortedMatrix.col(i) = Matrix.col(Sortperm(i));
	}
	return sortedMatrix;
}
