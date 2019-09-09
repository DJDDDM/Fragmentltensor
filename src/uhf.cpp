#include "uhf.h"

UHF::UHF(string name, int electronadd){
	Name = name;
	Electronadd = electronadd;
	computed = false;
	maxIters = 50;
}

void UHF::compute(){
	read();
	obtainconstants();
	print();
	double oldEnergy = 0;
	for (int Iteration = 1; Iteration < maxIters; Iteration++){
		updateEnergy();
		cout << std::setw(5) << Iteration << std::setw(19) << Energy
				<< std::setw(15) << abs(Energy-oldEnergy) << endl;
		if (abs(Energy - oldEnergy) < pow(10, -6)){
			break;
		}
		if (Iteration == maxIters){
			cout << "did not converged after " << Iteration << " Iterations";
			break;
		}
		oldEnergy = Energy;
	}
	computed = true;
}

double UHF:: getEnergy(){
	assert(computed);
	return Energy;
}

void UHF::updateEnergy(){
	Densitytensor Alphadensity = rhfeqs.Density(AlphaAOtoCO, Alphanelec);
	Densitytensor Betadensity= rhfeqs.Density(BetaAOtoCO, Betanelec);
	Densitytensor Totaldensity = uhfeqs.Totaldensity(Alphadensity, Betadensity);
	Densitytensor Spindensity = uhfeqs.Spindensity(Alphadensity, Betadensity);

	Gtensor Gcs = rhfeqs.G(Totaldensity, two);
	Focktensor Fockcs = rhfeqs.Fock(ONE, Gcs);
	Focktensor Deltauhf = uhfeqs.Delta(Spindensity, ERI);
	Focktensor Alphafock = uhfeqs.Alphafock(Fockcs, Deltauhf);
	Focktensor Betafock = uhfeqs.Betafock(Fockcs, Deltauhf);

	AlphaAOtoCO = rhfeqs.AOtoCO(Alphafock);
	BetaAOtoCO = rhfeqs.AOtoCO(Betafock);

	Energy = uhfeqs.Henergy(Totaldensity, ONE)
			+ uhfeqs.Fockenergy(Alphadensity, Alphafock)
			+ uhfeqs.Fockenergy(Betadensity, Betafock)
			+ Nuclearenergy;
}

void UHF::obtainconstants(){
	if (Totalnelec % 2 == 0){
		Alphanelec = Totalnelec /2;
		Betanelec = Totalnelec /2;
	}
	else {
		Alphanelec = (Totalnelec + 1) / 2;
		Betanelec = (Totalnelec -1) / 2;
	}

	AlphaAOtoCO = rhfeqs.initialguess(Norb, Alphanelec);
	BetaAOtoCO = rhfeqs.initialguess(Norb, Betanelec);
	two = rhfeqs.two(ERI);
}

void UHF::read(){
	ReadFCIDUMP reader = ReadFCIDUMP();
	reader.openfile(Name);
	reader.fillarrays();

	ERI = reader.gettwo();
	ONE = reader.getONE();
	Norb = reader.getNORB();
	Totalnelec = reader.getNELEC() + Electronadd ;
	Nuclearenergy = reader.getNuclearenergy();
}

void UHF::print(){
	cout << "Number of total Electrons: " << Totalnelec << endl;
	cout << "Number of alpha Electrons: " << Alphanelec << endl;
	cout << "Number of beta Electrons: " << Betanelec << endl;
	cout << "Number of Orbitals: " << Norb << endl;
	cout << "Nuclearenergy: " << Nuclearenergy << endl;
	cout << "Iteration" << std::setw(10) << "Energy" << std::setw(15) << "Ediff" << endl;
}

