#include "FCIDUMP.h"

FCIDUMP::FCIDUMP(){

}

FCIDUMP::FCIDUMP(std::string filename){
	ReadFCIDUMP Reader = ReadFCIDUMP();
	Reader.openfile(filename);
	Reader.fillarrays();

	Norb = Reader.getNORB();
	Nelec = Reader.getNELEC();
	ERI = Reader.gettwo();
	ONE = Reader.getONE();
	Nuclearenergy = Reader.getNuclearenergy();

	if (Nelec % 2 == 0){
		Alphanelec = Nelec/2;
		Betanelec = Nelec/2;
	}
	else {
		Alphanelec = (Nelec+1)/2;
		Betanelec = (Nelec-1)/2;
	}
	CUHFnelec = 0;

	rhf_equations rhf = rhf_equations();
	AOtoCO = rhf.initialguess(Norb, Nelec);
	AlphaAOtoCO = rhf.initialguess(Norb, Alphanelec);
	BetaAOtoCO = rhf.initialguess(Norb, Nelec);
}

FCIDUMP::FCIDUMP(const FCIDUMP& FCI){
	Norb = FCI.Norb;
	Nelec = FCI.Nelec;
	ERI = FCI.ERI;
	ONE = FCI.ONE;
	Nuclearenergy = FCI.Nuclearenergy;
	Alphanelec = FCI.Alphanelec;
	AlphaAOtoCO = FCI.AlphaAOtoCO;
	BetaAOtoCO = FCI.BetaAOtoCO;
	Betanelec = FCI.Betanelec;
	CUHFnelec = FCI.CUHFnelec;
	AOtoCO = FCI.AOtoCO;
}




