/*
 * vObject.h
 *
 *  Created on: 15/3/2015
 *      Author: tvlenin
 */
#include <string>
#include <stdlib.h>
using namespace std;
#ifndef VOBJECT_H_
#define VOBJECT_H_

class vObject{
public:
	vObject();
	void getVObjectData();
	string getVObjectType();
private:

	string vObjectType ;
	void *vObjectData;// = NULL;
	//void *pData;



};






#endif /* VOBJECT_H_ */
