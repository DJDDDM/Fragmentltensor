#include "uhf.h"
#include "main.h"

void test_uhf_Water(){
	string name = "FCIDUMP";
	UHF uhf = UHF(name);
	uhf.compute();
	double E_actual = uhf.getEnergy();
	double E_exp = -75.9839254;
	assert(abs(E_actual-E_exp) < pow(10,-6));
}

void test_uhf_Water1plus(){
	string name = "FCIDUMP";
	UHF uhf = UHF(name,-1);
	uhf.compute();
	double E_actual = uhf.getEnergy();
	double E_exp = -75.5788511;
	assert(abs(E_actual-E_exp) < pow(10,-6));
}

void test_uhf_Water2plus(){
	string name = "FCIDUMP";
	UHF uhf = UHF(name,-2);
	uhf.compute();
	double E_actual = uhf.getEnergy();
	double E_exp = -74.5379478;
	assert(abs(E_actual-E_exp) < pow(10,-6));
}

void test_uhf(){
	test_uhf_Water();
	test_uhf_Water1plus();
	test_uhf_Water2plus();
	cout << "passed uhf" << endl;
}



