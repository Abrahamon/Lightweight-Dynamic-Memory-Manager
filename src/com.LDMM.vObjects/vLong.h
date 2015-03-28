/*
 * vLong.h
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#ifndef COM_LDMM_VOBJECTS_VLONG_H_
#define COM_LDMM_VOBJECTS_VLONG_H_

#include "../Constants.h"
#include "vObject.h"
#include <iostream>
using namespace std;
class vLong: public vObject {
public:
	vLong();
	void operator = (const long& s);
	long vLongData;
};




#endif /* COM_LDMM_VOBJECTS_VLONG_H_ */
