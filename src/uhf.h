#include "uhf_equations.h"
#include "rhf_equations.h"
#include "ReadFCIDUMP.h"

#ifndef UHF_H_
#define UHF_H_

class UHF{
public:
	UHF();
	UHF(string name, int Electronadd=0);
	void compute();
	double getEnergy();
private:
	void obtainconstants();
	void read();
	void print();
	void updateEnergy();
	double Energy;
	rhf_equations rhfeqs;
	uhf_equations uhfeqs;
	NORB Norb;
	NELEC Totalnelec;
	NELEC Alphanelec;
	Transtensor AlphaAOtoCO;
	NELEC Betanelec;
	Transtensor BetaAOtoCO;
	ERItensor ERI;
	TWOtensor two;
	Htensor ONE;
	double Nuclearenergy;
	string Name;
	int Electronadd;
	bool computed;
	int maxIters;

};




#endif /* UHF_H_ */
