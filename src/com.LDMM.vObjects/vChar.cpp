/*
 * vChar.cpp
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#include "vChar.h"

vRef*  vChar::operator= (const char& s){
	vCharData = s;
	setVObjectData((void*)&vCharData);
	setVObjectType(Constants::TYPE_CHAR);
	return vHeap::getInstancia()->vMalloc(32,Constants::TYPE_CHAR);
	//return ;
}
 vChar::vChar(){

}
