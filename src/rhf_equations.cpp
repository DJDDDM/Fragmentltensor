#include "rhf_equations.h"
#include <iostream>

Focktensor rhf_equations::Fock(Htensor H, Gtensor G){
	Focktensor F(H.size[0],H.size[1]);
	F(i,j) = H(i,j) + G(i,j);
	return F;
}

Gtensor rhf_equations::G(Densitytensor P, TWOtensor two){
	Gtensor G(P.size[0],P.size[1]);
	G(i,j) = two(i,j,k,l)*P(l,k);
	return G;
}

TWOtensor rhf_equations::two(ERItensor eri){
	TWOtensor two(eri.size[0],eri.size[1],eri.size[2],eri.size[3]);
	two(i,j,k,l) = 2*eri(i,j,k,l) + -1 * eri(i,l,k,j);
	return two;
}
Densitytensor rhf_equations::Density(Transtensor AOtoCO, NELEC nelec){
	// I hate this but it seems like the current ltensorversion does not support slices any longer. one might think
	// about a downgraded ltensorversion.
	Densitytensor P(AOtoCO.size[0],AOtoCO.size[1]);

	int dim1 = AOtoCO.size[0];
	int dim2 = AOtoCO.size[1];
	int dim3 = nelec;

	for (int a = 0; a < dim1; a++){
		for (int b = 0; b < dim2; b++){
			P(a,b) = 0;
			for (int c = 0; c < dim3; c++){
				P(a,b) += AOtoCO(a,c)*AOtoCO(b,c);
			}
		}
	}
	return P;
}

Transtensor rhf_equations::AOtoCO(Focktensor Fock){
	diagonalizer diag = diagonalizer();
	diag.compute(Fock);
	return diag.Eigenvectors;
}

Transtensor rhf_equations::initialguess(NORB norb, NELEC nelec){
	Transtensor C(norb, norb);
	for (int i = 0; i < nelec; i++){
		C(i,i) = 1;
	}
	return C;
}

double rhf_equations::Energy(Densitytensor P, Htensor ONE, Focktensor Fock){
	int dim = P.size[0];
	double E = 0;
	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){
			E +=P(j,i)*(ONE(i,j)+Fock(i,j));
		}
	}
	return E;
}
