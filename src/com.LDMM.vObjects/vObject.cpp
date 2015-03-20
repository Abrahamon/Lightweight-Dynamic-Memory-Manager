/*
 * vObject.cpp
 *
 *  Created on: 15/3/2015
 *      Author: tvlenin
 */
#include "vObject.h"

//void* vObject::vObjectData=0;
vObject::vObject() {

	vObjectData=0;
}

void vObject::getVObjectData() {
	//return *vObjectData;
}

void vObject::setVObjectData(void* pData) {
	std::cout<<"entra al metodo"<<endl;
	vObjectData = pData;
	std::cout<<"el dato ingresado es "<< vObjectData<<endl;
}

string vObject::getVObjectType() {
	return "hola";
}
