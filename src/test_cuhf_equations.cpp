#include "cuhf_equations.h"
#include "rhf_equations.h"
#include "testhelpers.h"
#include "main.h"
#include <iostream>
using namespace std;



void test_CUHFAOtoNO(){
	rhf_equations rhf = rhf_equations();
	cuhf_equations op = cuhf_equations();

	Densitytensor Totaldensity(2,2);
	Totaldensity(1,0) = 1;
	Totaldensity(0,1) = 1;

	Transtensor AOtoNO = op.AOtoNO(Totaldensity);

	Transtensor C_exp(2,2);
	C_exp(0,0) = 0.70711;
	C_exp(1,0) = 0.70711;
	C_exp(0,1) = -0.70711;
	C_exp(1,1) = 0.70711;

	Focktensor F(2,2);
	F(1,0) = 1;
	F(0,1) = 1;
	Transtensor D = rhf.AOtoCO(F);
	assert(AOtoNO(0,0) == D(0,1));
	assert(AOtoNO(1,0) == D(1,1));
	assert(AOtoNO(0,1) == D(0,0));
	assert(AOtoNO(1,1) == D(1,0));


	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	Index<'l'> l;
	Marray<double, 2> J(2,2);
	J(i,l) = AOtoNO(j,i)*Totaldensity(j,k)*AOtoNO(k,l);
	assert(isequal(J(0,0), 1, 0.000001));
	assert(isequal(J(1,0), 0, 0.000001));
	assert(isequal(J(0,1), 0, 0.000001));
	assert(isequal(J(1,1), -1, 0.000001));

	Densitytensor Big(13,13);
	Big(0,0) = 1;
	Big(1,1) = 1;
	Big(2,2) = 1;
	Big(3,3) = 1;
	Big(4,4) = 1;
	Transtensor BigAOtoNO = op.AOtoNO(Big);
	Marray<double,2> K(13,13);
	K(i,l) = BigAOtoNO(j,i)*Big(j,k)*BigAOtoNO(k,l);

	assert(isequal(K,Big,0.0001));

	assert(isequal(AOtoNO, C_exp, 0.00001));
}


void test_CUHFtransform(){
	cuhf_equations op = cuhf_equations();

	Transtensor C(2,2);
	C(0,0) = 0.70711;
	C(1,0) = 0.70711;
	C(0,1) = -0.70711;
	C(1,1) = 0.70711;


	Focktensor FockCS(2,2);
	FockCS(0,0) = 1;
	FockCS(1,1) = -1;

	Focktensor FockCSNO = op.transform(FockCS,C);

	Focktensor FockCSNO_exp(2,2);
	FockCSNO_exp(1,0) = -1;
	FockCSNO_exp(0,1) = -1;

	assert(isequal(FockCSNO, FockCSNO_exp, 0.00001));

	C(0,0) = 0;
	C(1,0) = 1;
	C(0,1) = 1;
	C(1,1) = 0;

	FockCSNO = op.transform(FockCS,C);

	Focktensor FockCSNO_exp2(2,2);
	FockCSNO_exp2(0,0) = -1;
	FockCSNO_exp2(1,1) = 1;

	assert(isequal(FockCSNO, FockCSNO_exp2, 0.00001));
}

void test_FockCUHF(){
	cuhf_equations op = cuhf_equations();
	NORB norb;
	norb = 5;
	NELEC active;
	active = 3;
	NELEC closed;
	closed = 2;
	Focktensor FockCSNO = fillmatrix(5,5);
	Focktensor FockelecNO(5,5);

	Focktensor FockCUHF = op.FockCUHF(FockelecNO, FockCSNO, active, closed);

	Focktensor FockCUHF_exp(5,5);
	FockCUHF_exp(0,3) = 4;
	FockCUHF_exp(0,4) = 5;
	FockCUHF_exp(1,3) = 9;
	FockCUHF_exp(1,4) = 10;
	FockCUHF_exp(3,0) = 16;
	FockCUHF_exp(3,1) = 17;
	FockCUHF_exp(4,0) = 21;
	FockCUHF_exp(4,1) = 22;

	assert(FockCUHF == FockCUHF_exp);
}

void test_transformback(){
	cuhf_equations ops = cuhf_equations();
	Transtensor AOtoNO = fillmatrix(2,2);
	Transtensor NOtoCO= fillmatrix(2,2);
	NOtoCO(0,0) = 5;


	Transtensor AOtoCO = ops.transformback(AOtoNO, NOtoCO);
	Transtensor AOtoCO_exp(2,2);
	AOtoCO_exp(0,0) = 11;
	AOtoCO_exp(0,1) = 10;
	AOtoCO_exp(1,0) = 27;
	AOtoCO_exp(1,1) = 22;

	assert(AOtoCO == AOtoCO_exp);
}


void test_cuhf_equations(){
	test_CUHFAOtoNO();
	test_CUHFtransform();
	test_FockCUHF();
	test_transformback();
	cout << "passed cuhf equations" << endl;
}
