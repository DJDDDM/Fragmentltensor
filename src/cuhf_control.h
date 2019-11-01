#include "cuhf_equations.h"
#include "uhf_equations.h"
#include "rhf_equations.h"
#include "FCIDUMP.h"

#ifndef CUHF_CONTROL_H_
#define CUHF_CONTROL_H_

class Density{
public:
	Density();
	Density(FCIDUMP FCI);
	Densitytensor Spindensity;
	Densitytensor Totaldensity;
	Densitytensor Alphadensity;
	Densitytensor Betadensity;
	Transtensor AOtoNO;
private:
	rhf_equations rhfeqs;
	uhf_equations uhfeqs;
	cuhf_equations cuhfeqs;
};

class Test_cuhf_control;
class cuhf_control{
	friend Test_cuhf_control;
public:
	cuhf_control();
	cuhf_control(FCIDUMP FCI);
	void doCUHF();
	bool hasconverged();
	double getEnergy();
protected:
	FCIDUMP FCI;

	Densitytensor Spindensity;
	Densitytensor Totaldensity;
	Densitytensor Alphadensity;
	Densitytensor Betadensity;
	Transtensor AOtoNO;

	Focktensor FockCSAO;
	Focktensor FockalphaAO;
	Focktensor FockbetaAO;

	Focktensor FockCSNO;
	Focktensor FockalphaNO;
	Focktensor FockbetaNO;

	Focktensor FockalphaCUHF;
	Focktensor FockbetaCUHF;

	double Energy = 0;
	double oldEnergy = 1;
	NELEC active;
	NELEC closed;
	int Maxiterations = 50;

	void activespace();
	void doDensity();
	void FockAO();
	void FockNO();
	void FockCUHF();
	void AOtoCOupdate();
	void Energycalculation();
	bool Loopcontrol(int Iteration);

	rhf_equations rhfeqs;
	uhf_equations uhfeqs;
	cuhf_equations cuhfeqs;
	bool converged = false;
};





#endif /* CUHF_CONTROL_H_ */
