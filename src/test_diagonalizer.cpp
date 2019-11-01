#include <iostream>
#include "main.h"
#include <eigen3/Eigen/Eigenvalues>
#include "diagonalizer.h"
#include "testhelpers.h"
using namespace std;

void test_transform(){
	int NORB = 3;
	diagonalizer diag = diagonalizer();

	Marray<double, 2> Lmatrix(NORB,NORB);

	double counter = 0;
	for (int i=0; i < 3; i++){
		for (int j=0; j < 3; j++){
			counter ++;
			Lmatrix(i,j) = counter;
		}
	}

	double expcounter = 0;
	Eigen::Matrix<double, 3, 3> Eigenmatrix_exp;
	for (int i=0; i < 3; i++){
		for (int j=0; j < 3; j++){
			expcounter ++;
			Eigenmatrix_exp(i,j) = expcounter;
		}
	}

	Eigen::MatrixXd Eigenmatrix1 = diag.transform(Lmatrix);
	Marray<double, 2> Lmatrix1 = diag.transform(Eigenmatrix1);
	Eigen::MatrixXd Eigenmatrix2 = diag.transform(Lmatrix1);

	assert(Lmatrix == Lmatrix1);
	assert(Eigenmatrix1 == Eigenmatrix2);
}

void test_compute(){
	//because phasefactors the Eigenvectorassertion is not allways valid
	diagonalizer diag = diagonalizer();
	Marray<double, 2> Matrix(2,2);
	Matrix(1,0) = 1;
	Matrix(0,1) = 1;

	diag.compute(Matrix);

	Marray<double, 2> Eigenvalues_exp(2,2);
	Eigenvalues_exp(0,0) = -1;
	Eigenvalues_exp(1,0) = 0;
	Eigenvalues_exp(0,1) = 0;
	Eigenvalues_exp(1,1) = 1;

	Marray<double, 2> Eigenvectors_exp(2,2);
	Eigenvectors_exp(0,0) = -0.70711;
	Eigenvectors_exp(1,0) = 0.70711;
	Eigenvectors_exp(0,1) = 0.70711;
	Eigenvectors_exp(1,1) = 0.70711;

	Marray<double, 2> Eigenvectors = diag.Eigenvectors;
	Marray<double, 2> Eigenvalues = diag.Eigenvalues;

	cout << Eigenvalues << endl;
	cout << Eigenvectors << endl;
	assert(isequal(Eigenvectors, Eigenvectors_exp, 0.00001));
	assert(isequal(Eigenvalues, Eigenvalues_exp, 0.000000001));


}

void test_sort(){
	diagonalizer diag = diagonalizer();

	Eigen::VectorXd Vektor(5);
	Eigen::VectorXd Vektor_exp(5);
	Eigen::VectorXd Sortperm_exp(5);

	for (int i = 0; i < 5; i++){
		Vektor(i) = 5-i;
		Vektor_exp(i) = i+1;
		Sortperm_exp(i) = 4-i;
	}

	Eigen::VectorXd Sortperm = diag.sortperm(Vektor);
	Eigen::VectorXd sortedVektor = diag.sort(Vektor,Sortperm);

	assert(Sortperm == Sortperm_exp);
	assert(sortedVektor == Vektor_exp);
}

void test_diagonalizer(){
	test_transform();
	test_sort();
	test_compute();
	cout << "passed diagonalizer" << endl;
}



