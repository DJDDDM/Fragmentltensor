#include "test_cuhf_control.h"
#include "testhelpers.h"
#include "main.h"
#include <iostream>
using namespace std;

void Test_cuhf_control::FockAO(){
	rhf_equations rhf = rhf_equations();
	FCIDUMP fci;
	fci.Norb = 5;
	fci.Alphanelec = 3;
	fci.Betanelec = 2;
	fci.ERI = ERItensor(fci.Norb, fci.Norb, fci.Norb, fci.Norb);
	fci.ERI(1,2,2,2) = 3;
	fci.ONE = Htensor(fci.Norb, fci.Norb);
	fci.ONE(1,2) = 1.5;
	Transtensor AlphaAOtoCO = rhf.initialguess(fci.Norb, fci.Alphanelec);
	Transtensor BetaAOtoCO = rhf.initialguess(fci.Norb, fci.Betanelec);
	fci.AlphaAOtoCO = AlphaAOtoCO;
	fci.BetaAOtoCO = BetaAOtoCO;


	cuhf_control ops = cuhf_control(fci);

	ops.doDensity();
	ops.FockAO();

	Focktensor FockalphaAO = ops.FockalphaAO;
	Focktensor FockbetaAO = ops.FockbetaAO;
	Focktensor FockCSAO = ops.FockCSAO;

	Focktensor FockalphaAO_exp(fci.Norb, fci.Norb);
	FockalphaAO_exp(1,2) = 1.5;

	Focktensor FockbetaAO_exp(fci.Norb, fci.Norb);
	FockbetaAO_exp(1,2) = 4.5;

	Focktensor FockCSAO_exp(fci.Norb, fci.Norb);
	FockCSAO_exp(1,2) = 3;

	assert(FockalphaAO_exp == FockalphaAO);
	assert(FockbetaAO_exp== FockbetaAO);
	assert(FockCSAO_exp == FockCSAO);
}

void Test_cuhf_control::transform(){
	rhf_equations rhf = rhf_equations();
	FCIDUMP FCI;
	FCI.Norb = 2;
	FCI.Alphanelec = 2;
	FCI.Betanelec = 2;
	Transtensor AlphaAOtoCO = rhf.initialguess(FCI.Norb, FCI.Alphanelec);
	Transtensor BetaAOtoCO = rhf.initialguess(FCI.Norb, FCI.Betanelec);
	FCI.AlphaAOtoCO = AlphaAOtoCO;
	FCI.BetaAOtoCO = BetaAOtoCO;

	Focktensor FockCS(2,2);
	FockCS(0,0) = 1;
	FockCS(1,1) = -1;

	Focktensor Fockalpha(2,2);
	Fockalpha(0,0) = 1;
	Fockalpha(1,1) = -1;


	Focktensor FockCSNO_exp(2,2);
	FockCSNO_exp(0,0) = -1;
	FockCSNO_exp(1,1) = 1;

	cuhf_control ops = cuhf_control(FCI);
	ops.doDensity();
	ops.FockAO();
	ops.FockCSAO = FockCS;
	ops.FockalphaAO = Fockalpha;
	ops.FockNO();

	assert(isequal(ops.FockCSNO, FockCSNO_exp, 0.00001));
	assert(isequal(ops.FockalphaNO, FockCSNO_exp, 0.00001));
}

void Test_cuhf_control::FockCUHF(){
	FCIDUMP fci;
	rhf_equations rhf = rhf_equations();
	fci.Norb = 5;
	fci.Alphanelec = 3;
	fci.Betanelec = 2;
	fci.CUHFnelec = 2;
	Transtensor AlphaAOtoCO = rhf.initialguess(fci.Norb, fci.Alphanelec);
	Transtensor BetaAOtoCO = rhf.initialguess(fci.Norb, fci.Betanelec);
	fci.AlphaAOtoCO = AlphaAOtoCO;
	fci.BetaAOtoCO = BetaAOtoCO;


	cuhf_equations eqs = cuhf_equations();
	Focktensor FockCSNO = fillmatrix(5,5);

	Focktensor FockalphaNO(5,5);
	FockalphaNO(1,3) = 2;
	FockalphaNO(2,1) = 3;
	FockalphaNO(1,1) = 4;


	cuhf_control ops = cuhf_control(fci);
	ops.activespace();
	ops.doDensity();
	ops.FockAO();
	ops.FockNO();
	ops.FockbetaNO = FockalphaNO;
	ops.FockalphaNO = FockalphaNO;
	ops.FockCSNO = FockCSNO;
	ops.FockCUHF();
	Focktensor FockalphaCUHF = ops.FockalphaCUHF;
	NELEC active;
	active = 3;
	NELEC closed;
	closed = 1;
	Focktensor FockalphaCUHF_exp = eqs.FockCUHF(ops.FockalphaNO,ops.FockCSNO,active,closed);
	assert(FockalphaCUHF == FockalphaCUHF_exp);
	assert(FockalphaCUHF(1,1) = 4);
	assert(FockalphaCUHF(0,4) = 5);
}

void Test_cuhf_control::Loopcontrol(){
	FCIDUMP fci;
	cuhf_control ops = cuhf_control(fci);
	ops.Energy = 5;
	ops.oldEnergy = 5;
	int Iteration = 5;
	assert(ops.Loopcontrol(Iteration));

	ops.Energy = 4;
	assert(!ops.Loopcontrol(Iteration));

	ops.Energy = 4;
	Iteration = ops.Maxiterations+1;
	assert(ops.Loopcontrol(Iteration));

	ops.Energy = 5;
	Iteration = ops.Maxiterations+1;
	assert(ops.Loopcontrol(Iteration));
}

void Test_cuhf_control::testDensity(){
	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	Index<'l'> l;
	rhf_equations rhfeqs;
	cuhf_equations cuhfeqs;
	FCIDUMP fci("FCIDUMP");
	fci.Nelec = 8;
	fci.Alphanelec = 4;
	fci.Betanelec = 4;
	fci.AlphaAOtoCO = rhfeqs.initialguess(fci.Norb,fci.Alphanelec);
	fci.BetaAOtoCO = rhfeqs.initialguess(fci.Norb,fci.Betanelec);

	cuhf_control ops = cuhf_control(fci);
	ops.activespace();
	ops.doDensity();
	ops.FockAO();
	ops.FockNO();
	ops.FockCUHF();
	ops.AOtoCOupdate();
	ops.Energycalculation();
	ops.Loopcontrol(1);

	Density Dens = Density(ops.FCI);
	Transtensor AOtoNO = cuhfeqs.AOtoNO(Dens.Totaldensity);
	Densitytensor Totaldensity = Dens.Totaldensity;

	diagonalizer diag = diagonalizer();
	diag.compute(Totaldensity);
	Marray<double,2> Eigenvectors = diag.Eigenvectors;
	Marray<double,2> Eigenvalues = diag.Eigenvalues;
	Marray<double,2> Eigenvaluesordered(fci.Norb,fci.Norb);
	Marray<double,2> Eigenvectorsordered(fci.Norb,fci.Norb);

	Marray<double,2> K(fci.Norb,fci.Norb);
	K(i,j) = Eigenvectors(k,i)*Dens.Totaldensity(k,l)*Eigenvectors(l,j);
	cout << K << endl;
	cout << Eigenvalues << endl;

	int dim1 = fci.Norb;
	int dim2 = fci.Norb;
	double value = 0;
	for (int i = 0; i < dim1; i++){
		for (int j = 0; j < dim2; j++){
			value = Eigenvalues(i,j);
			Eigenvaluesordered(dim1-1-i,dim1-1-j) = value;
			Eigenvectorsordered(i,j) = Eigenvectors(i,dim1-1-j);
		}
	}

	Marray<double,2> J(fci.Norb,fci.Norb);
	J(i,j) = Eigenvectorsordered(k,i)*Dens.Totaldensity(k,l)*Eigenvectorsordered(l,j);
	cout << J << endl;
	cout << Eigenvaluesordered << endl;
}



void test_cuhf_control(){
	Test_cuhf_control test;
	test.FockAO();
	test.transform();
	test.FockCUHF();
	test.Loopcontrol();
	test.testDensity();
	cout << "passed test cuhf control" << endl;
}


