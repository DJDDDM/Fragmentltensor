
#include "uhf_equations.h"

Densitytensor uhf_equations::Totaldensity(Densitytensor Alphadensity, Densitytensor Betadensity){
	Densitytensor Total(Alphadensity.size[0],Alphadensity.size[1]);
	Total(i,j) = (Alphadensity(i,j) + Betadensity(i,j)) / 2;
	return Total;
}

Densitytensor uhf_equations::Spindensity(Densitytensor Alphadensity, Densitytensor Betadensity){
	Densitytensor Spin(Alphadensity.size[0],Alphadensity.size[1]);
	Spin(i,j) = (Alphadensity(i,j) - Betadensity(i,j))/2;
	return Spin;
}

Focktensor uhf_equations::Delta(Densitytensor Spindensity, ERItensor ERI){
	Focktensor Delta(Spindensity.size[0],Spindensity.size[1]);
	Delta(i,j) = ERI(i,k,l,j) * Spindensity(k,l);
	return Delta;
}

Focktensor uhf_equations::Alphafock(Focktensor Fockcs, Focktensor Delta){
	Focktensor Falpha(Fockcs.size[0], Fockcs.size[1]);
	Falpha(i,j) = Fockcs(i,j) - Delta(i,j);
	return Falpha;
}

Focktensor uhf_equations::Betafock(Focktensor Fockcs, Focktensor Delta){
	Focktensor Fbeta(Fockcs.size[0], Fockcs.size[1]);
	Fbeta(i,j) = Fockcs(i,j) + Delta(i,j);
	return Fbeta;
}

double uhf_equations::Henergy(Densitytensor Totaldensity, Htensor ONE){
	double E = 0;
	for (int i = 0; i < Totaldensity.size[0]; i++){
		for (int j = 0; j < Totaldensity.size[1]; j++){
			E += Totaldensity(i,j)*ONE(j,i);
		}
	}
	return E;
}

double uhf_equations::Fockenergy(Densitytensor Density, Focktensor Fock){
	double E = 0;
	for (int i = 0; i < Density.size[0]; i++){
		for (int j = 0; j < Density.size[1]; j++){
			E += Density(i,j)*Fock(j,i)/2;
		}
	}
	return E;
}
