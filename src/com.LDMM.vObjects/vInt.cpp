/*
 * vInt.cpp
 *
 *  Created on: 15/3/2015
 *      Author: tvlenin
 */

#include "vInt.h"
//vInt::

int vInt::getData() {
	std::cout<<"Hola soy un dato"<<endl;

//	int *num = int(*(vObjectData));
	return 5;
}

void vInt::operator= (const int& s){
	//vIntData = &s;//
	setVObjectData((void*)vIntData);
	std::cout<<*vIntData<<endl;
	return ;
}
 vInt::vInt(){

}
