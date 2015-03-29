/*
 * vRef.h
 *
 *  Created on: Mar 18, 2015
 *      Author: fabian
 */

#ifndef SRC_VREF_H_
#define SRC_VREF_H_
#include "xEntry.h"
#include "../com.LDMM.vObjects/vObject.h"

class vRef :public vObject{
private:
	int _ID;
//	xEntry* _xReference;
public:
	vRef();
	vRef(int pID);
	virtual ~vRef();

	void setID(int pID);
	int getID();
	int* getMemPos();
};

#endif /* SRC_VREF_H_ */
