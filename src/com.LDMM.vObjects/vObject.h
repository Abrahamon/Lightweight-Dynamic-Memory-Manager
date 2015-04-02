/*
 * vObject.h
 *
 *  Created on: 15/3/2015
 *      Author: tvlenin
 */
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;
#ifndef VOBJECT_H_
#define VOBJECT_H_

class vObject{
public:
	vObject(); //Constructor de vObject
	void getVObjectData(); //metodo para obtener el dato almacenado
	void setVObjectData(void * pData); //metodo para asignar el dato amacenado
	string getVObjectType(); //Metodo para obtener el tipo de dato almacenado
	void setVObjectType(string pType); //metodo para asignar
private:

	string vObjectType ; // Variable de texto que almacena el tipo de dato
	void * vObjectData;	//Variable void * que almacena el valor asigando







};






#endif /* VOBJECT_H_ */
