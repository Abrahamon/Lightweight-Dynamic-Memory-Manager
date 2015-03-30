/*
 * vString.h
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#ifndef COM_LDMM_VOBJECTS_VSTRING_H_
#define COM_LDMM_VOBJECTS_VSTRING_H_

#include "../Constants.h"
#include "vObject.h"
#include <iostream>
#include "../com.LDMM.MemoryResources/vRef.h"
using namespace std;
class vString: public vRef {
public:
	vString();
	void operator = (const string& s);
	string vStringData;
};



#endif /* COM_LDMM_VOBJECTS_VSTRING_H_ */
