#include "uhf.h"
#include "rhf.h"

void UHF::cycle(){
	//rhf_equations rhfeqs = rhf_equations();
	//uhf_equations uhfeqs = uhf_equations();

	//NORB Norb;
	//NELEC Alphanelec;
	//NELEC Betanelec;
	//ERItensor ERI;


	//Transtensor AlphaAOtoCO = rhfeqs.initialguess(Norb, Alphanelec);
	//Transtensor BetaAOtoCO = rhfeqs.initialguess(Norb, Betanelec);
	//TWOtensor two = rhfeqs.two(ERI);



	//Densitytensor Alphadensity = rhfeqs.Density(AlphaAOtoCO, Alphanelec);
	//Densitytensor Betadensity= rhfeqs.Density(BetaAOtoCO, Betanelec);
	//Densitytensor Totaldensity = uhfeqs.Totaldensity(Alphadensity, Betadensity);
	//Densitytensor Spindensity = uhfeqs.Spindensity(Alphadensity, Betadensity);

	//Gtensor Gcs = rhfeqs.G(Totaldensity, two);

	//Focktensor Fockcs = rhfeqs.Fock(ONE, Gcs);
	//Focktensor Deltauhf = uhfeqs.Delta(Spindensity, ERI);
	//Focktensor Alphafock = uhfeqs.Alphafock(Fockcs, Deltauhf);
	//Focktensor Betafock = uhfeqs.Betafock(Fockcs, Deltauhf);

	//AlphaAOtoCO = rhfeqs.AOtoCO(Alphafock);
	//BetaAOtoCO = rhfeqs.AOtoCO(Betafock);

	//double Energy = uhfeqs.Henergy(Totaldensity, ONE)
	//		+ uhfeqs.Fockenergy(Alphadensity, Alphafock)
	//		+ uhfeqs.Fockenergy(Betadensity, Betafock);



}




