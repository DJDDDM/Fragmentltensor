#include "cuhf_equations.h"

Transtensor cuhf_equations::AOtoNO(Densitytensor Totaldensity){
	int dim1 = Totaldensity.size[0];
	int dim2 = Totaldensity.size[1];
	for (int i = 0; i < dim1; i++){
		for (int j = 0; j < dim2; j++){
			if (abs(Totaldensity(i,j)) < 0.000001){
				Totaldensity(i,j) = 0;
			}
		}
	}
	for (int i = 0; i < dim1; i++){
		for (int j = 0; j < i; j++){
			Totaldensity(i,j) = Totaldensity(j,i);
		}
	}

	diagonalizer diag = diagonalizer();
	diag.compute(Totaldensity);
	Transtensor wrongorder = diag.Eigenvectors;
	Transtensor correctorder(dim1, dim2);
	for (int i = 0; i < dim1; i++){
		for (int j = 0; j < dim2; j++){
			correctorder(i,j) = wrongorder(i,dim1-1-j);
		}
	}


	bool wrong = false;
	Marray<double,2> J(dim1,dim2);
	J(i,l) = correctorder(j,i)*Totaldensity(j,k)*correctorder(k,l);
	for (int i = 0; i < dim1; i++){
		if(wrong) break;
		for (int j = 0; j < dim2; j++){
			if(wrong) break;
			if(abs(J(i,j)) > 0.00001) {
				if(i == j) continue;
				//std::cout << J << std::endl;
				//std::cout << Totaldensity << std::endl;
				//assert(false);
				wrong = true;
				break;
			}
			if(wrong) break;
		}
		if(wrong) break;
	}
	return correctorder;
}

Focktensor cuhf_equations::transform(Focktensor original, Transtensor Transmatrix){
	Focktensor transformed(original.size[0],original.size[1]);
	transformed(i,j) = Transmatrix(k,i)*original(k,l)*Transmatrix(l,j);
	return transformed;
}

Focktensor cuhf_equations::FockCUHF(Focktensor FockelecNO, Focktensor FockCSNO, NELEC active, NELEC closed){
	int virt = FockCSNO.size[0];
	Focktensor Fockcuhf(virt,virt);
	Fockcuhf = FockelecNO;
	for(int activetovirt = active; activetovirt< virt; activetovirt++){
		for (int zerotoclosed = 0; zerotoclosed < closed; zerotoclosed++){
			Fockcuhf(activetovirt,zerotoclosed) = FockCSNO(activetovirt,zerotoclosed);
			Fockcuhf(zerotoclosed,activetovirt) = FockCSNO(zerotoclosed,activetovirt);
		}
	}
	return Fockcuhf;
}

Transtensor cuhf_equations::transformback(Transtensor AOtoNO, Transtensor NOtoCO){
	Transtensor AOtoCO(AOtoNO.size[0],AOtoNO.size[1]);
	AOtoCO(i,j) = AOtoNO(i,k) * NOtoCO(k,j);
	return AOtoCO;
}
