/*
 * vObject.cpp
 *
 *  Created on: 15/3/2015
 *      Author: tvlenin
 */
#include "vObject.h"
#include <typeinfo>

/*
 *
 * Clase vHeap
 * es la clase principal que se va a almacenar en el vHeap, de ella heredan
 * todas las clases envoltorio como vInt, vFloat, vString. El constructo esta vacio
 * ya que sus datos se asignan mediante otros metodos.
 *
 */
vObject::vObject() {


}
/*
 * getVObjectData es un metodo que imprime el valor del dato almacenado
 * se hace uso de un switch para elegir el tipo de dato. Una vez se sepa
 * el tipo de dato que es, se realiza un casteo y luego una desreferencia.
 *
 */
void vObject::getVObjectData() {
	string sOption = getVObjectType();
	switch(sOption[0]) // obtiene la primera letra del tipo de dato ingresado.
	{
	case 'I' :
		std::cout <<*(int*)vObjectData<<endl;
		break;
	case 'S' :
		std::cout <<*(string*)vObjectData<<endl;
		break;
	case 'C' :
		std::cout <<*(char*)vObjectData<<endl;
		break;
	case 'L' :
		std::cout <<*(long*)vObjectData<<endl;
		break;
	case 'F' :
		std::cout <<*(float*)vObjectData<<endl;
		break;
	case 'B' :
		std::cout<<*(bool*)vObjectData<<endl;
		break;



	}
}
/*
 *
 * Metodo setVObjectData
 * recibe como argunmento un void* que es la direccion de memoria del
 * dato ingresado, este argumento lo guarda en una variable para despues
 * obtener o imprimir el valor.
 *
 */
void vObject::setVObjectData(void* pData) {
	vObjectData = pData;

}
/*
 *
 * Metodo getVObjectType
 * Devuelve un string con el tipo de dato que almacena el vObject
 *
 */

string vObject::getVObjectType() {
	return vObjectType;
}

/*
 *
 * Metodo setVObjectType
 * recibe un string con el tipo de dato que almacena el vObject y
 * lo guarda en una variable.
 *
 */
void vObject::setVObjectType(string pType) {
	vObjectType = pType;
}
