#include "cuhf_control.h"

cuhf_control::cuhf_control(){
	FCIDUMP FCIdump;
	this->FCI = FCIdump;
}

cuhf_control::cuhf_control(FCIDUMP FCIdump){
	this->FCI = FCIdump;
}

void cuhf_control::doCUHF(){
	cout << "NORB= " << FCI.Norb << " Alphanelec= " << FCI.Alphanelec << " Betanelec= " << FCI.Betanelec << endl;
	activespace();
	for (int Iteration = 1; Iteration < Maxiterations+2; Iteration++){
		doDensity();
		FockAO();
		FockNO();
		FockCUHF();
		AOtoCOupdate();
		Energycalculation();
		if(Loopcontrol(Iteration)) break;
	}
}

double cuhf_control::getEnergy(){
	return Energy;
}

bool cuhf_control::hasconverged(){
	return converged;
}

void cuhf_control::activespace(){
	assert(FCI.CUHFnelec % 2 == 0);
	if (FCI.CUHFnelec > FCI.Betanelec) FCI.CUHFnelec = FCI.Betanelec;
	closed = FCI.Betanelec - FCI.CUHFnelec/2;
	active = FCI.Alphanelec;
}

void cuhf_control::doDensity(){
	Density Densitycontainer = Density(FCI);
	Spindensity = Densitycontainer.Spindensity;
	Totaldensity = Densitycontainer.Totaldensity;
	AOtoNO = Densitycontainer.AOtoNO;
	Alphadensity = Densitycontainer.Alphadensity;
	Betadensity = Densitycontainer.Betadensity;
}

void cuhf_control::FockAO(){
		TWOtensor two = rhfeqs.two(FCI.ERI);
		Gtensor Gcs = rhfeqs.G(Totaldensity, two);
		Focktensor Deltauhf = uhfeqs.Delta(Spindensity, FCI.ERI);
		FockCSAO = rhfeqs.Fock(FCI.ONE, Gcs);
		FockalphaAO = uhfeqs.Alphafock(FockCSAO, Deltauhf);
		FockbetaAO = uhfeqs.Betafock(FockCSAO, Deltauhf);
}

void cuhf_control::FockNO(){
		FockCSNO = cuhfeqs.transform(FockCSAO,AOtoNO);
		FockalphaNO = cuhfeqs.transform(FockalphaAO,AOtoNO);
		FockbetaNO = cuhfeqs.transform(FockbetaAO,AOtoNO);
}

void cuhf_control::FockCUHF(){
		FockalphaCUHF = cuhfeqs.FockCUHF(FockalphaNO,FockCSNO,active,closed);
		FockbetaCUHF = cuhfeqs.FockCUHF(FockbetaNO,FockCSNO,active,closed);
}

void cuhf_control::AOtoCOupdate(){
		Transtensor NOtoCOalpha = rhfeqs.AOtoCO(FockalphaCUHF);
		Transtensor NOtoCObeta = rhfeqs.AOtoCO(FockbetaCUHF);
		FCI.AlphaAOtoCO = cuhfeqs.transformback(AOtoNO,NOtoCOalpha);
		FCI.BetaAOtoCO = cuhfeqs.transformback(AOtoNO,NOtoCObeta);
}

void cuhf_control::Energycalculation(){
		Energy  = uhfeqs.Henergy(Totaldensity, FCI.ONE);
		Energy += uhfeqs.Fockenergy(Alphadensity, FockalphaAO);
		Energy += uhfeqs.Fockenergy(Betadensity, FockbetaAO);
		Energy += FCI.Nuclearenergy;
}

bool cuhf_control::Loopcontrol(int Iteration){
		std::cout << std::setw(5) << Iteration
				<< std::setw(19) << Energy
				<< std::setw(15) << abs(Energy-oldEnergy) << std::endl;
		if (abs(Energy - oldEnergy) < pow(10, -7)){
			cout << "CUHF converged" << endl;
			converged = true;
			return true;
		}
		if (Iteration > Maxiterations){
			cout << "CUHF not converged" << endl;
			converged = false;
			return true;
		}
		oldEnergy = Energy;
		return false;
}


Density::Density(FCIDUMP FCI){
	Alphadensity = rhfeqs.Density(FCI.AlphaAOtoCO, FCI.Alphanelec);
	Betadensity= rhfeqs.Density(FCI.BetaAOtoCO, FCI.Betanelec);
	Totaldensity = uhfeqs.Totaldensity(Alphadensity, Betadensity);
	Spindensity = uhfeqs.Spindensity(Alphadensity, Betadensity);
	AOtoNO = cuhfeqs.AOtoNO(Totaldensity);
}

