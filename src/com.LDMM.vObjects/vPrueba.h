/*
 * vPrueba.h
 *
 *  Created on: Apr 15, 2015
 *      Author: fabian
 */

#ifndef SRC_COM_LDMM_VOBJECTS_VPRUEBA_H_
#define SRC_COM_LDMM_VOBJECTS_VPRUEBA_H_
#include "../Constants.h"
#include "vObject.h"
#include <iostream>
#include "../com.LDMM.MemoryResources/vRef.h"
#include "../com.LDMM.MemoryManager/vHeap.h"

class vPrueba {
public:
	vPrueba();
	virtual ~vPrueba();
	int pData;
	vRef* operator= (const int &s);
	void* operator new(size_t sz, void *pvObject){
		return pvObject;
	}
};

#endif /* SRC_COM_LDMM_VOBJECTS_VPRUEBA_H_ */
