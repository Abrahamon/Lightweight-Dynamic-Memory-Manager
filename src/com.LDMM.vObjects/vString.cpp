/*
 * vString.cpp
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */
#include "vString.h"
void vString::operator= (const string& s){
	vStringData = s;
	setVObjectData((void*)&vStringData);
	setVObjectType(Constants::TYPE_STRING);
	return ;
}
 vString::vString(){

}

