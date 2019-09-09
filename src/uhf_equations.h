#ifndef UHF_EQUATIONS_H_
#define UHF_EQUATIONS_H_

#include "main.h"
#include "Tensorclasses.h"

class uhf_equations{
public:
	Densitytensor Totaldensity(Densitytensor Alphadensity, Densitytensor Betadensity);
	Densitytensor Spindensity(Densitytensor Alphadensity, Densitytensor Betadensity);
	Focktensor Delta(Densitytensor Spindensity, ERItensor ERI);
	Focktensor Alphafock(Focktensor Fockcs, Focktensor Delta);
	Focktensor Betafock(Focktensor Fockcs, Focktensor Delta);

private:
	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	Index<'l'> l;
};




#endif /* UHF_EQUATIONS_H_ */
