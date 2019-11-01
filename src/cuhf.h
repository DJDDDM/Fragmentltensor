#include "cuhf_control.h"

#ifndef CUHF_H_
#define CUHF_H_

class cuhf{
public:
	void calc(FCIDUMP FCI);
	double getEnergy();
private:
	cuhf_control ops;
	bool converged;
};




#endif /* CUHF_H_ */
