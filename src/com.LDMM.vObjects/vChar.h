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
#include "../com.LDMM.MemoryResources/vRef.h"
#include "../com.LDMM.MemoryManager/vHeap.h"
using namespace std;
class vChar: public vRef {
public:
	vChar();
	vRef* operator = (const char& s);
	char vCharData;
	/*
	 *
	 * placement new
	 * Se sobreescribe el new, ahora en lugar de esperar solo la llamada al
	 * constructor de la clase, recibe un primer parametro que es la direccion
	 * del espacio de memoria donde se desea almacenar el objeto a crear
	 *
	 */
	void* operator new(size_t sz, void *pvObject){
		return pvObject;
	}
};



#endif /* COM_LDMM_VOBJECTS_VCHAR_H_ */
