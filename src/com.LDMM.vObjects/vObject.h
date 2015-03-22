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
	vObject();
	void getVObjectData();
	void setVObjectData(void * pData);
	string getVObjectType();
private:

	string vObjectType ;
	void* vObjectData;// = NULL;
	//void *pData;






};






#endif /* VOBJECT_H_ */
