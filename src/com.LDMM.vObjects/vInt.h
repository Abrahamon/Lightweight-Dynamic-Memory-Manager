/*
 * vInt.h
 *
 *  Created on: 15/3/2015
 *      Author: tvlenin
 */

#ifndef VINT_H_
#define VINT_H_

#include "../Constants.h"
#include "vObject.h"
#include <iostream>
#include "../com.LDMM.MemoryResources/vRef.h"
#include "../com.LDMM.MemoryManager/vHeap.h"

using namespace std;

class vInt: public vRef {
public:
	vInt();
	void operator = (const int& s); //era vRef*

	int vIntData;

	void* operator new(size_t sz, void *v){
		//sz = size_t(vHeap::getInstancia()->ptrUltimaMemoriaLibre);

		this->_ID = vHeap::getInstancia()->vMalloc(4,TYPE_INT);
		cout<<"Me invocaron al metodo del .h, con id: "<<_ID<<endl;
		return v;
	}
};


#endif /* VINT_H_ */
