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
#include "../com.LDMM.MemoryManager/vHeap.h"
using namespace std;
class vString: public vRef {
public:
	vString();
	vRef *operator = (const string& s);
	string vStringData;
	void* operator new(size_t sz, void *pvObject){
		return pvObject;
	}
};



#endif /* COM_LDMM_VOBJECTS_VSTRING_H_ */
