#ifndef CUHF_EQUATIONS_H_
#define CUHF_EQUATIONS_H_

#include "Tensorclasses.h"
#include "diagonalizer.h"

class cuhf_equations{
public:
	Transtensor AOtoNO(Densitytensor Totaldensity);
	Focktensor transform(Focktensor original, Transtensor Transmatrix);
	Focktensor FockCUHF(Focktensor FockelecNO, Focktensor FockCSNO, NELEC active, NELEC closed);
	Transtensor transformback(Transtensor AOtoNO, Transtensor NOtoCO);
private:
	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	Index<'l'> l;


};




#endif /* CUHF_EQUATIONS_H_ */
