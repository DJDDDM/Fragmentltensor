#include "cuhf.h"

void cuhf::calc(FCIDUMP FCI){
	ops  = cuhf_control(FCI);
	ops.doCUHF();
	converged = ops.hasconverged();
}

double cuhf::getEnergy(){
	assert(converged);
	return ops.getEnergy();
}



