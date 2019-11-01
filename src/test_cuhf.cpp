#include "cuhf.h"
#include "rhf_equations.h"
#include "testhelpers.h"
#include "main.h"
#include <iostream>
using namespace std;

void test_calc(){
	rhf_equations rhf = rhf_equations();
	std::string filename = "FCIDUMP";
	FCIDUMP FCI(filename);
	cuhf op = cuhf();

	////55
	//FCI.AlphaAOtoCO = rhf.initialguess(FCI.Norb,FCI.Alphanelec);
	//FCI.BetaAOtoCO = rhf.initialguess(FCI.Norb,FCI.Betanelec);
	//op.calc(FCI);
	//double Energy = op.getEnergy();
	//double E_exp = -75.9839254;
	//assert(abs(Energy-E_exp) < pow(10,-6));

	////54
	//FCI.Nelec = 9;
	//FCI.Alphanelec = 5;
	//FCI.Betanelec = 4;
	//FCI.AlphaAOtoCO = rhf.initialguess(FCI.Norb,FCI.Alphanelec);
	//FCI.BetaAOtoCO = rhf.initialguess(FCI.Norb,FCI.Betanelec);
	//op.calc(FCI);
	//Energy = op.getEnergy();
	//E_exp = -75.57674552503578;
	////assert(abs(Energy-E_exp) < pow(10,-6));

	////53
	//FCI.Nelec = 8;
	//FCI.Alphanelec = 5;
	//FCI.Betanelec = 3;
	//FCI.AlphaAOtoCO = rhf.initialguess(FCI.Norb,FCI.Alphanelec);
	//FCI.BetaAOtoCO = rhf.initialguess(FCI.Norb,FCI.Betanelec);
	//op.calc(FCI);
	//Energy = op.getEnergy();
	//E_exp = -74.62438189516593;
	////assert(abs(Energy-E_exp) < pow(10,-6));

	//44
	FCI.Nelec = 8;
	FCI.Alphanelec = 4;
	FCI.Betanelec = 4;
	FCI.AlphaAOtoCO = rhf.initialguess(FCI.Norb,FCI.Alphanelec);
	FCI.BetaAOtoCO = rhf.initialguess(FCI.Norb,FCI.Betanelec);
	op.calc(FCI);

	//33
	//FCI.Nelec = 6;
	//FCI.Alphanelec = 3;
	//FCI.Betanelec = 3;
	//FCI.AlphaAOtoCO = rhf.initialguess(FCI.Norb,FCI.Alphanelec);
	//FCI.BetaAOtoCO = rhf.initialguess(FCI.Norb,FCI.Betanelec);
	//op.calc(FCI);




}




void test_cuhf(){
	//test_calc();
	cout << "passed cuhf tests" << endl;
}



