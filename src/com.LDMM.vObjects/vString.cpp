/*
 * vString.cpp
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */
#include "vString.h"
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
vRef* vString::operator= (const string& s){
	vStringData = s;
	setVObjectData((void*)&vStringData);
	setVObjectType(Constants::TYPE_STRING);
	vRef* refe =vHeap::getInstancia()->vMalloc(40,Constants::TYPE_STRING);
	this->setID(refe->getID());
	return refe;
}
 vString::vString(){

}

