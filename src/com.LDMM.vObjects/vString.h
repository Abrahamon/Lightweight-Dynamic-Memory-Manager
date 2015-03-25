/*
 * vString.h
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#ifndef COM_LDMM_VOBJECTS_VSTRING_H_
#define COM_LDMM_VOBJECTS_VSTRING_H_

#include "../Constants.h"
#include "vObject.h"
#include <iostream>
using namespace std;
class vString: public vObject {
public:
	vString();
	void operator = (const string& s);
	string vStringData;
};



#endif /* COM_LDMM_VOBJECTS_VSTRING_H_ */
