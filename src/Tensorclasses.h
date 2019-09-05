#ifndef Tensorclasses_H_
#define Tensorclasses_H_

#include <LTensor.h>

class NORB{
public:
	NORB operator=(int number){
		value = number;
		return *this;
	}
	operator int(){
		return value;
	};
	int value;
};

class NELEC {
public:
	NELEC operator+=(NELEC summand){
		value += summand.value;
	}
	NELEC operator=(int number){
		value = number;
		return *this;
	}
	operator int(){
		return value;
	};
private:
	int value;
};



class Transtensor: public Marray<double, 2>{
	public:
		Transtensor(int first, int second) : Marray<double, 2>(first, second){};
		Transtensor() : Marray<double, 2>(){};
		Transtensor(Marray<double, 2> Matrix) : Marray<double, 2>(Matrix){};
};

class Gtensor : public Marray<double, 2>{
	public:
		Gtensor(int first, int second) : Marray<double, 2>(first, second){};
		Gtensor() : Marray<double, 2>(){};
};

class Densitytensor : public Marray<double, 2>{
	public:
		Densitytensor(int first, int second) : Marray<double, 2>(first, second){};
		Densitytensor() : Marray<double, 2>(){};
};

class Focktensor : public Marray<double, 2>{
	public:
		Focktensor(int first, int second) : Marray<double, 2>(first, second){};
		Focktensor() : Marray<double, 2>(){};
};

class Htensor : public Marray<double, 2>{
	public:
		Htensor(int first, int second) : Marray<double, 2>(first, second){};
		Htensor() : Marray<double, 2>(){};
};

class ERItensor: public Marray<double, 4>{
	public:
		ERItensor(int first, int second, int third, int fourth) : Marray<double, 4>(first, second, third, fourth){};
		ERItensor() : Marray<double, 4>(){};
};

class TWOtensor: public Marray<double, 4>{
	public:
		TWOtensor(int first, int second, int third, int fourth) : Marray<double, 4>(first, second, third, fourth){};
		TWOtensor() : Marray<double, 4>(){};
};

#endif /*Tensorclasses_H_*/
