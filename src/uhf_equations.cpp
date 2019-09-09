
#include "uhf_equations.h"

Densitytensor uhf_equations::Totaldensity(Densitytensor Alphadensity, Densitytensor Betadensity){
	Densitytensor Total(Alphadensity.size[0],Alphadensity.size[1]);
	Total(i,j) = Alphadensity(i,j) + Betadensity(i,j);
	return Total;
}

Densitytensor uhf_equations::Spindensity(Densitytensor Alphadensity, Densitytensor Betadensity){
	Densitytensor Spin(Alphadensity.size[0],Alphadensity.size[1]);
	Spin(i,j) = Alphadensity(i,j) - Betadensity(i,j);
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

