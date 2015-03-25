/*
 * vLong.cpp
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#include "vLong.h"

void vLong::operator= (const long& s){
	vLongData = s;
	setVObjectData((void*)&vLongData);
	setVObjectType(TYPE_LONG);
	return ;
}
 vLong::vLong(){

}



