/*
 * vChar.cpp
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#include "vChar.h"

void vChar::operator= (const char& s){
	vCharData = s;
	setVObjectData((void*)&vCharData);
	setVObjectType(TYPE_CHAR);
	return ;
}
 vChar::vChar(){

}