#include "main.h"
#include "ReadFCIDUMP.h"

#include <iostream>
#include <cassert>

using namespace std;

ReadFCIDUMP setup(string name){
	ReadFCIDUMP reader = ReadFCIDUMP();
	reader.setname(name);
	reader.openfile();
	return reader;
}

void testreference(){
	ReadFCIDUMP reader = ReadFCIDUMP();
	reader.openfile("FCIDUMP");
	reader.fillarrays();
	ERItensor Two1=reader.gettwo();
	Two1(0,0,0,0)=1234.0;
	ERItensor Two2=reader.gettwo();
	assert(Two1 == Two2);
}

void testname(){
	string name = "FCIDUMP";
	ReadFCIDUMP reader = setup(name);
	string actual = reader.getname();
	assert(name == actual);
	reader.closefile();
}

void testfile(){
	string name = "FCIDUMP";
	ReadFCIDUMP reader = setup(name);
	reader.openfile();
	reader.closefile();
}

void test_getnextline(){
	string expected = " &FCI NORB= 13,NELEC= 10,MS2= 0,";
	ReadFCIDUMP reader = setup("FCIDUMP");
	reader.readnextline();
	string line = reader.getcurrentline();
	assert(line == expected);
	reader.closefile();
}

void test_readnamelist(){
	ReadFCIDUMP reader = setup("FCIDUMP");
	reader.readnamelist();
	int NORB = reader.getNORB();
	int NELEC = reader.getNELEC();
	assert(NORB == 13);
	assert(NELEC == 10);
}

void test_skipnamelist(){
	string expected = "  0.4739562867406113E+01   1   1   1   1";
	ReadFCIDUMP reader = setup("FCIDUMP");
	reader.skipnamelist();
	reader.readnextline();
	string actual = reader.getcurrentline();
	assert (actual == expected);
}

void test_integral(){
	double expected = 0.4739562867406113E+01;
	double expected2 = -0.4275136930490248E+00;
	ReadFCIDUMP reader = setup("FCIDUMP");
	reader.skipnamelist();
	reader.readnextline();
	reader.readintegral();
	double actual = reader.getintegral();
	assert (actual == expected);
	reader.readnextline();
	reader.readintegral();
	double actual2 = reader.getintegral();
	assert (actual2 == expected2);
}

void test_indizes(){
	ReadFCIDUMP reader = setup("FCIDUMP");
	reader.skipnamelist();
	reader.readnextline();
	reader.readnextline();
	reader.readnextline();
	reader.readindizes();
	assert(2 == reader.getindize(1));
	assert(1 == reader.getindize(2));
	assert(2 == reader.getindize(3));
	assert(1 == reader.getindize(4));
}

void test_fillarrays(){
ReadFCIDUMP reader = ReadFCIDUMP();
	reader.openfile("FCIDUMP");
	reader.fillarrays();
	ERItensor Two = reader.gettwo();
	double Two_actual = Two(3,0,0,0);
	double Two_exp = 0.1512252327862014E+00;
	assert(Two_actual == Two_exp);

	Two_actual = Two(0,0,0,0);
	Two_exp = 0.4739562867406113E+01;
	assert(Two_actual == Two_exp);

	Htensor ONE = reader.getONE();
	double ONE_actual = ONE(0,0);
	double ONE_exp = -0.3303871576059193E+02;
	assert(ONE_actual == ONE_exp);

	ONE_actual =  ONE(5,0);
	ONE_exp = -0.1888406389774784E+00;
	assert(ONE_actual == ONE_exp);

	double E_Nucc = reader.getNuclearenergy();
	double E_Nucc_exp = 0.9300757771647021E+01;
	assert(E_Nucc == E_Nucc_exp);
}

void test_ReadFCIDUMP(){
	testname();
	testfile();
	test_getnextline();
	test_skipnamelist();
	test_integral();
	test_indizes();
	test_readnamelist();
	test_fillarrays();
	cout << "passed ReadFCIDUMP" << endl;
}
