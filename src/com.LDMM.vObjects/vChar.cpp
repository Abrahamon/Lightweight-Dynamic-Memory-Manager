/*
 * vChar.cpp
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#include "vChar.h"
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
vRef*  vChar::operator= (const char& s){
	vCharData = s;
	setVObjectData((void*)&vCharData);
	setVObjectType(Constants::TYPE_CHAR);
	return vHeap::getInstancia()->vMalloc(32,"Char");
	//return ;
}
 vChar::vChar(){

}
