/*
 * vLong.cpp
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#include "vLong.h"
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
vRef* vLong::operator= (const long& s){
	vLongData = s;
	setVObjectData((void*)&vLongData);
	setVObjectType(Constants::TYPE_LONG);
	vRef* refe =vHeap::getInstancia()->vMalloc(40,Constants::TYPE_LONG);
	this->setID(refe->getID());
	return refe;

}
 vLong::vLong(){

}



