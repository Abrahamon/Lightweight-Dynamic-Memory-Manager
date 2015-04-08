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
//#include "../com.LDMM.MemoryManager/vHeap.h"


using namespace std;

class vHeap;

class vInt : public vRef {

private:

public:
	vHeap *heap;



	vInt();
	vRef* operator = (const int& s); //era vRef*

	int vIntData;
	/*
	 *
	 * placement new
	 * Se sobreescribe el new, ahora en lugar de esperar solo la llamada al
	 * constructor de la clase, recibe un primer parametro que es la direccion
	 * del espacio de memoria donde se desea almacenar el objeto a crear
	 *
	 */
//	void* operator new(size_t sz, void *pvObject){
//		return pvObject;
//	}


	void * allocate(size_t);
	void* operator new(vInt & pvObject){

		vHeap* a = vHeap::getInstancia();
		long a = reinterpret_cast<long>(heap->getInstancia()->_ptrUltimaMemoriaLibre);
		return pvObject.allocate(a);
	}

};


#endif /* VINT_H_ */
