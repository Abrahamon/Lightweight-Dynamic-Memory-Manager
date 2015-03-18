/*
 * singletone.h
 *
 *  Created on: Mar 17, 2015
 *      Author: abraham
 */

#ifndef SRC_SINGLETONE_H_
#define SRC_SINGLETONE_H_

#include "vHeap.h"

class singletone{

private:
	static vHeap* instancia;

public:

	static vHeap* getInstancia()
	{
		if( instancia != 0)
		{
			return instancia;
		}else{
			instancia = new vHeap(200,200);

			return instancia;
		}
	};

};

vHeap* singletone::instancia = 0;

#endif /* SRC_SINGLETONE_H */

