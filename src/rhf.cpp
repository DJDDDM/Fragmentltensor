#include "rhf.h"


rhf::rhf(std::string name, int electronadd){
	FCIDUMP = name;
	Electronadd = electronadd;
	Energy = 1;
}


void rhf::compute(){
	read();
	init();
	print();
	loop();
}

void rhf::print(){
	cout << "Number of Orbitals: " << norb << endl;
	cout << "Number of occupied Orbitals: " << nelec << endl;
	cout << "Iteration" << std::setw(10) << "Energy" << std::setw(15) << "Ediff" << endl;
}

void rhf::init(){
	oldEnergy = 0;
	maxIters = 50;
	equations = rhf_equations();
	AOtoCO = equations.initialguess(norb, nelec);
	two = equations.two(ERI);
}

void rhf::read(){
	ReadFCIDUMP reader = ReadFCIDUMP();
	reader.openfile(FCIDUMP);
	reader.fillarrays();

	ERI = reader.gettwo();
	ONE = reader.getONE();
	norb = reader.getNORB();
	nelec = (reader.getNELEC() + Electronadd) / 2;
	Nuclearenergy = reader.getNuclearenergy();
}



void rhf::loop(){
	for (int Iteration = 1; Iteration < maxIters; Iteration++){
		cycle();
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

}

void rhf::cycle(){
		Density = equations.Density(AOtoCO,nelec);
		G = equations.G(Density, two);
		Fock = equations.Fock(ONE,G);
		AOtoCO = equations.AOtoCO(Fock);
		Energy = equations.Energy(Density, ONE, Fock) + Nuclearenergy;
}

double rhf::getEnergy(){
	return Energy;
}
