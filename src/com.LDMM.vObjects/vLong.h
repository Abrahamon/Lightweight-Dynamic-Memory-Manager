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
#include "../com.LDMM.MemoryResources/vRef.h"
using namespace std;
class vLong: public vRef {
public:
	vLong();
	void operator = (const long& s);
	long vLongData;
};




#endif /* COM_LDMM_VOBJECTS_VLONG_H_ */
