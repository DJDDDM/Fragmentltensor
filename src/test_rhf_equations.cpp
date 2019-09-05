#include "main.h"
#include "rhf_equations.h"
#include <iostream>
#include "testhelpers.h"
using namespace std;

void test_Fock(){
	rhf_equations op = rhf_equations();
	int NORB = 5;
	Htensor H(NORB,NORB);
	Gtensor G(NORB,NORB);
	Focktensor Fexp(NORB,NORB);
	H(2,3) = 5;
	G(2,3) = 3;
	H(3,1) = 2;
	G(1,3) = 4;
	Fexp(2,3) = 8;
	Fexp(3,1) = 2;
	Fexp(1,3) = 4;
	Focktensor F = op.Fock(H, G);
	assert (Fexp == F);
};

void test_G(){
	rhf_equations op = rhf_equations();
	int NORB = 5;
	Densitytensor P(NORB,NORB);
	TWOtensor two(NORB,NORB,NORB,NORB);
	Gtensor Gexp(NORB,NORB);

	P(4,3) = 5;
	two(1,2,3,4) = 2;
	Gexp(1,2) = 10;
	two(3,2,4,1) = 3;
	P(4,1) = 4;
	Gexp(3,2) = 0;

	Gtensor G = op.G(P,two);
	assert (G == Gexp);
}

void test_two(){
	rhf_equations op = rhf_equations();
	int NORB = 5;
	TWOtensor twoexp(NORB,NORB,NORB,NORB);
	ERItensor eri(NORB,NORB,NORB,NORB);

	eri(1,2,3,4) = 5;
	eri(1,4,3,2) = 3;
	twoexp(1,2,3,4) = 7;
	twoexp(1,4,3,2) = 1;
	eri(2,3,1,4) = 6;
	twoexp(2,3,1,4) = 12;
	twoexp(2,4,1,3) = -6;

	TWOtensor two = op.two(eri);
	assert (two == twoexp);
}

void test_density(){
	rhf_equations op = rhf_equations();
	int NORB = 5;
	NELEC nelec;
	nelec = 3;
	Densitytensor Pexp(NORB,NORB);
	Transtensor AOtoCO(NORB, NORB);

	AOtoCO(1,2) = 3;
	AOtoCO(1,4) = 4;
	AOtoCO(0,1) = 2;
	Pexp(1,1) = 9;
	Pexp(0,0) = 4;

	Densitytensor P = op.Density(AOtoCO, nelec);
	assert (P == Pexp);
}

void test_AOtoCO(){
	//because phasefactors the assertion is not allways valid
	rhf_equations op = rhf_equations();

	Focktensor Fock(2,2);
	Fock(1,0) = 1;
	Fock(0,1) = 1;

	Transtensor C = op.AOtoCO(Fock);

	Transtensor C_exp(2,2);
	C_exp(0,0) = -0.70711;
	C_exp(1,0) = 0.70711;
	C_exp(0,1) = 0.70711;
	C_exp(1,1) = 0.70711;

	assert(isequal(C, C_exp, 0.00001));
}

void test_initialguess(){
	rhf_equations op = rhf_equations();
	NELEC nelec;
	nelec = 3;
	NORB norb;
	norb = 5;

	Transtensor C = op.initialguess(norb, nelec);
	Transtensor C_exp(norb, norb);
	C_exp(0,0) = 1;
	C_exp(1,1) = 1;
	C_exp(2,2) = 1;
	assert(C==C_exp);
}

void test_Energy(){
	rhf_equations op = rhf_equations();
	int NORB = 2;

	Densitytensor P(NORB, NORB);
	P(0,0) = 2;
	P(1,1) = 2;


	Htensor H(NORB, NORB);
	H(0,1) = 1;
	H(1,0) = 1;

	Focktensor F(NORB, NORB);
	F(0,1) = 2;
	F(1,1) = 3;

	double E = op.Energy(P,H,F);
	assert(E == 6);

}



void test_rhf_equations(){
	test_Fock();
	test_G();
	test_two();
	test_density();
	test_AOtoCO();
	test_initialguess();
	test_Energy();
	cout << "passed rhf_equations" << endl;
}
