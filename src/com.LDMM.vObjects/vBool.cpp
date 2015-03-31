/*
 * vBool.cpp
 *
 *  Created on: 25/3/2015
 *      Author: tvlenin
 */

#include "vBool.h"

void vBool::operator= (const bool& s){
	vBoolData = s;
	setVObjectData((void*)&vBoolData);
	setVObjectType(Constants::TYPE_BOOL);
	return ;
}
 vBool::vBool(){

}



