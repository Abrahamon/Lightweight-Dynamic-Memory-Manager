/*
 * vInt.cpp
 *
 *  Created on: 15/3/2015
 *      Author: tvlenin
 */

#include "vInt.h"

void vInt::operator= (const int& s){
	vIntData = s;
	setVObjectData((void*)&vIntData);
	setVObjectType(TYPE_INT);
	return ;
}
 vInt::vInt(){

}


