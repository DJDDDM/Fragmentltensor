#include <iostream>
#include <fstream>
#include "Tensorclasses.h"
using namespace std;

#ifndef READFCIDUMP_H_
#define READFCIDUMP_H_

class ReadFCIDUMP{
public:
	void setname(string name);
	string getname();
	string getcurrentline();
	double getintegral();
	int getindize(int number);
	int getNORB();
	int getNELEC();
	ERItensor gettwo();
	Htensor getONE();
	double getNuclearenergy();
	void openfile();
	void openfile(string name);
	void closefile();
	void readnextline();
	void skipnamelist();
	void readintegral();
	void readindizes();
	void readnamelist();
	void fillarrays();
	void initarrays();

	void setElectronadd(int Electronadd);
private:
	string stringbetween(string key1, string key2);
	void progressnextline();
	string name;
	string currentline = "";
	ifstream FCIDUMP;
	string defaultname = "FCIDUMP";
	double integral;
	int first;
	int second;
	int third;
	int fourth;
	int NORB;
	int NELEC;
	double Nuclearenergy;
	//Marray<double, 4> two;
	ERItensor two;
	Htensor ONE;
	int Electronadd;
};




#endif /* READFCIDUMP_H_ */
