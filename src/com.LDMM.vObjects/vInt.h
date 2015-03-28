/*
 * vInt.h
 *
 *  Created on: 15/3/2015
 *      Author: tvlenin
 */

#ifndef VINT_H_
#define VINT_H_

#include "../Constants.h"
#include "vObject.h"
#include <iostream>
using namespace std;
class vInt: public vObject {
public:
	vInt();
	void operator = (const int& s);
	int vIntData;
};

#endif /* VINT_H_ */
