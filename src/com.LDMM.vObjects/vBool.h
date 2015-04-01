/*
 * vBool.h
 *
 *  Created on: 25/3/2015
 *      Author: tvlenin
 */

#ifndef COM_LDMM_VOBJECTS_VBOOL_H_
#define COM_LDMM_VOBJECTS_VBOOL_H_


#include "../Constants.h"
#include "vObject.h"
#include <iostream>
#include "../com.LDMM.MemoryResources/vRef.h"
#include "../com.LDMM.MemoryManager/vHeap.h"
using namespace std;
class vBool: public vRef {
public:
	vBool();
	vRef* operator = (const bool& s);
	bool vBoolData;
	void * operator new (size_t sz, void* pvObject){
		return pvObject;
	}
};



#endif /* COM_LDMM_VOBJECTS_VBOOL_H_ */
