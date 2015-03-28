/*
 * vFloat.h
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#ifndef COM_LDMM_VOBJECTS_VFLOAT_H_
#define COM_LDMM_VOBJECTS_VFLOAT_H_

#include "../Constants.h"
#include "vObject.h"
#include <iostream>
using namespace std;
class vFloat: public vObject {
public:
	vFloat();
	void operator = (const float& s);
	float vFloatData;
};



#endif /* COM_LDMM_VOBJECTS_VFLOAT_H_ */
