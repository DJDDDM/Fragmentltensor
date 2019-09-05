/*
 * rhf_equations.h
 *
 *  Created on: Aug 20, 2019
 *      Author: dama
 */

#ifndef RHF_EQUATIONS_H_
#define RHF_EQUATIONS_H_

#include "Tensorclasses.h"
#include "diagonalizer.h"

class rhf_equations{
public:
	Focktensor Fock(Htensor H, Gtensor G);
	TWOtensor two(ERItensor eri);
	Gtensor G(Densitytensor P, TWOtensor two);
	Densitytensor Density(Transtensor AOtoCO, NELEC nelec);
	Transtensor AOtoCO(Focktensor Fock);
	Transtensor initialguess(NORB norb, NELEC nelec);
	double Energy(Densitytensor P, Htensor ONE, Focktensor Fock);
private:
	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	Index<'l'> l;
};




#endif /* RHF_EQUATIONS_H_ */
