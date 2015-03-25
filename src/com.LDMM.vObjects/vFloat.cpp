/*
 * vFloat.cpp
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#include "vFloat.h"

void vFloat::operator= (const float& s){
	vFloatData = s;
	setVObjectData((void*)&vFloatData);
	setVObjectType(TYPE_FLOAT);
	return ;
}
 vFloat::vFloat(){

}




