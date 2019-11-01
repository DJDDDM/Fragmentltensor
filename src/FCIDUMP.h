#include "Tensorclasses.h"
#include "rhf_equations.h"
#include "ReadFCIDUMP.h"

#ifndef FCIDUMP_H_
#define FCIDUMP_H_

class FCIDUMP{
public:
	FCIDUMP();
	FCIDUMP(std::string filename);
	FCIDUMP(const FCIDUMP&);
	NORB Norb;
	NELEC Nelec;
	ERItensor ERI;
	Htensor ONE;
	double Nuclearenergy;
	NELEC Alphanelec;
	NELEC Betanelec;
	NELEC CUHFnelec;
	Transtensor AOtoCO;
	Transtensor AlphaAOtoCO;
	Transtensor BetaAOtoCO;
};


#endif /* FCIDUMP_H_ */
