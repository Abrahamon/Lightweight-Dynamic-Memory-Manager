/*
 * vBool.cpp
 *
 *  Created on: 25/3/2015
 *      Author: tvlenin
 */

#include "vBool.h"
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
vRef* vBool::operator= (const bool& s){
	vBoolData = s;
	setVObjectData((void*)&vBoolData);
	setVObjectType(Constants::TYPE_BOOL);
	return vHeap::getInstancia()->vMalloc(32,Constants::TYPE_BOOL);;
}
 vBool::vBool(){

}



