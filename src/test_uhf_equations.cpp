#include "uhf_equations.h"
#include <iostream>
using namespace std;

void test_Totaldensity(){
	uhf_equations op = uhf_equations();

	NORB Norb;
	Norb = 2;
	Densitytensor Alphadensity(Norb, Norb);
	Alphadensity(0,0) = 1;
	Alphadensity(0,1) = 2;
	Alphadensity(1,0) = 3;
	Alphadensity(1,1) = 4;

	Densitytensor Betadensity(Norb, Norb);
	Betadensity(0,0) = 5;
	Betadensity(0,1) = 6;
	Betadensity(1,0) = 7;
	Betadensity(1,1) = 8;

	Densitytensor Expected(Norb, Norb);
	Expected(0,0) = 3;
	Expected(0,1) = 4;
	Expected(1,0) = 5;
	Expected(1,1) = 6;

	Densitytensor Totaldensity = op.Totaldensity(Alphadensity, Betadensity);
	assert(Totaldensity == Expected);
}

void test_Spindensity(){
	uhf_equations op = uhf_equations();

	NORB Norb;
	Norb = 2;
	Densitytensor Betadensity(Norb, Norb);
	Betadensity(0,0) = 1;
	Betadensity(0,1) = 2;
	Betadensity(1,0) = 3;
	Betadensity(1,1) = 4;

	Densitytensor Alphadensity(Norb, Norb);
	Alphadensity(0,0) = 5;
	Alphadensity(0,1) = 7;
	Alphadensity(1,0) = 9;
	Alphadensity(1,1) = 11;

	Densitytensor Expected(Norb, Norb);
	Expected(0,0) = 2;
	Expected(0,1) = 2.5;
	Expected(1,0) = 3;
	Expected(1,1) = 3.5;

	Densitytensor Spindensity = op.Spindensity(Alphadensity, Betadensity);
	assert(Spindensity == Expected);
}

void test_Delta(){
	uhf_equations op = uhf_equations();
	ERItensor ERI(5,5,5,5);
	Densitytensor Spindensity(5,5);
	Focktensor Expected(5,5);

	ERI(0,0,0,1) = 1;
	Spindensity(0,0) = 1;
	ERI(0,1,2,3) = 2;
	Spindensity(1,2) = 3;

	Expected(0,3) = 6;
	Expected(0,1) = 1;

	Focktensor Delta = op.Delta(Spindensity, ERI);
	assert(Delta == Expected);
}

void test_Alphafock(){
	uhf_equations op = uhf_equations();

	NORB Norb;
	Norb = 2;
	Focktensor Delta(Norb, Norb);
	Delta(0,0) = 1;
	Delta(0,1) = 2;
	Delta(1,0) = 3;
	Delta(1,1) = 4;

	Focktensor Fock(Norb, Norb);
	Fock(0,0) = 5;
	Fock(0,1) = 7;
	Fock(1,0) = 9;
	Fock(1,1) = 11;

	Focktensor Expected(Norb, Norb);
	Expected(0,0) = 4;
	Expected(0,1) = 5;
	Expected(1,0) = 6;
	Expected(1,1) = 7;

	Focktensor Alphafock = op.Alphafock(Fock, Delta);
	assert(Alphafock == Expected);
}

void test_Betafock(){
	uhf_equations op = uhf_equations();

	NORB Norb;
	Norb = 2;
	Focktensor Delta(Norb, Norb);
	Delta(0,0) = 1;
	Delta(0,1) = 2;
	Delta(1,0) = 3;
	Delta(1,1) = 4;

	Focktensor Fock(Norb, Norb);
	Fock(0,0) = 5;
	Fock(0,1) = 7;
	Fock(1,0) = 9;
	Fock(1,1) = 11;

	Focktensor Expected(Norb, Norb);
	Expected(0,0) = 6;
	Expected(0,1) = 9;
	Expected(1,0) = 12;
	Expected(1,1) = 15;

	Focktensor Betafock = op.Betafock(Fock, Delta);
	assert(Betafock == Expected);
}

void test_Hernergy(){
	uhf_equations op = uhf_equations();

	NORB Norb;
	Norb = 2;
	Htensor ONE(Norb, Norb);
	ONE(0,0) = 1;
	ONE(0,1) = 2;
	ONE(1,0) = 3;
	ONE(1,1) = 4;

	Densitytensor total(Norb, Norb);
	total(0,0) = 5;
	total(0,1) = 6;
	total(1,0) = 7;
	total(1,1) = 8;

	double expected = 69;

	double Henergy = op.Henergy(total,ONE);
	assert(Henergy == expected);
}

void test_Fockenergy(){
	uhf_equations op = uhf_equations();

	NORB Norb;
	Norb = 2;
	Focktensor Fock(Norb, Norb);
	Fock(0,0) = 1;
	Fock(0,1) = 2;
	Fock(1,0) = 3;
	Fock(1,1) = 4;

	Densitytensor Density(Norb, Norb);
	Density(0,0) = 5;
	Density(0,1) = 6;
	Density(1,0) = 7;
	Density(1,1) = 8;

	double expected = 34.5;

	double Henergy = op.Fockenergy(Density,Fock);
	assert(Henergy == expected);
}

void test_uhf_equations(){
	test_Totaldensity();
	test_Spindensity();
	test_Delta();
	test_Alphafock();
	test_Betafock();
	test_Hernergy();
	test_Fockenergy();

	cout << "passed uhf equations" << endl;
}



