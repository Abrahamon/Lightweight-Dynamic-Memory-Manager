/*
 * vInt.cpp
 *
 *  Created on: 15/3/2015
 *      Author: tvlenin
 */

#include "vInt.h"
#include "../com.LDMM.MemoryManager/vHeap.h"
#include <typeinfo>
/*
 *
 * Sobrecarga del operador =
 * Con la sobrecarga de este operador en lugar de esperar un dato del mismo dato,
 * recibe un dato de tipo al que envuelve, lo alamcena en una variable del tipo
 * correcto, llama a setVObjectData y setVObjectType para guardar el dato y el tipo
 * y devuelve un vRef, haciendo una llamada a la instancia de vHeap y llamando a vMalloc
 * que le guarda un valor en el vHeap.
 *
 */
vRef* vInt::operator= (const int& s){
	vIntData = s;
	setVObjectData((void*)&vIntData);
	setVObjectType(Constants::TYPE_INT);
	return vHeap::getInstancia()->vMalloc(32,Constants::TYPE_INT);

}

 vInt::vInt(){
	vIntData = 0;

}
