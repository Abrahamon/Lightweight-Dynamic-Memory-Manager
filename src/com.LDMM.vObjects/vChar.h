/*
 * vChar.h
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#ifndef COM_LDMM_VOBJECTS_VCHAR_H_
#define COM_LDMM_VOBJECTS_VCHAR_H_


#include "../Constants.h"
#include "vObject.h"
#include <iostream>
using namespace std;
class vChar: public vObject {
public:
	vChar();
	void operator = (const char& s);
	char vCharData;
};



#endif /* COM_LDMM_VOBJECTS_VCHAR_H_ */
