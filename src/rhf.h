#include <string>
#include <iomanip>
#include <iostream>
#include "rhf_equations.h"
#include "ReadFCIDUMP.h"

#ifndef RHF_H_
#define RHF_H_

class rhf{
public:
	rhf();
	rhf(std::string FCIDUMP,int Electronadd=0);
	void compute();
	double getEnergy();
private:
	void print();
	void init();
	void read();
	void loop();
	void cycle();
	int Electronadd;
	std::string FCIDUMP;
	double Energy;
	ERItensor ERI;
	Htensor ONE;
	Transtensor AOtoCO;
	TWOtensor two;
	Densitytensor Density;
	Focktensor Fock;
	Gtensor G;
	rhf_equations equations;
	double oldEnergy;
	int maxIters;
	NELEC nelec;
	NORB norb;
	double Nuclearenergy;
};



#endif /* RHF_H_ */
