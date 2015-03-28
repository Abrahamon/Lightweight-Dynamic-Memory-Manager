/*
 * vObject.cpp
 *
 *  Created on: 15/3/2015
 *      Author: tvlenin
 */
#include "vObject.h"
#include <typeinfo>


vObject::vObject() {


}

void vObject::getVObjectData() {
	string sOption = getVObjectType();
	switch(sOption[0]){
	case 'I' :
		std::cout <<*(int*)vObjectData<<endl;
		break;
	case 'S' :
		std::cout <<*(string*)vObjectData<<endl;
		break;
	case 'C' :
		std::cout <<*(char*)vObjectData<<endl;
		break;
	case 'L' :
		std::cout <<*(long*)vObjectData<<endl;
		break;
	case 'F' :
		std::cout <<*(float*)vObjectData<<endl;// No lo puedo convertir a float
		break;
	case 'B' :
		std::cout<<*(bool*)vObjectData<<endl;
		break;



	}
}

void vObject::setVObjectData(void* pData) {
	vObjectData = pData;

}

string vObject::getVObjectType() {
	return vObjectType;
}

void vObject::setVObjectType(string pType) {
	vObjectType = pType;
}
