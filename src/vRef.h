/*
 * vRef.h
 *
 *  Created on: Mar 18, 2015
 *      Author: fabian
 */

#ifndef SRC_VREF_H_
#define SRC_VREF_H_
#include "src/xEntry.h"

class vRef {
private:
	int _ID;
	xEntry* _xReference;
public:
	vRef(int pID, xEntry* pRef);
	virtual ~vRef();

	void setID(int pID);
	int getID();
	int* getMemPos();
};

#endif /* SRC_VREF_H_ */
