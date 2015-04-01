/*
 * Encoder.h
 *
 *  Created on: Apr 1, 2015
 *      Author: fabian
 */

#ifndef SRC_COM_LDMM_DATAACCESS_ENCODER_H_
#define SRC_COM_LDMM_DATAACCESS_ENCODER_H_
#include "socketcliente.h"
#include "../Constants.h"
#include <string>
#include <sstream>

class Encoder {
private:
	SocketCliente* socket;
public:
	Encoder();
	virtual ~Encoder();
	bool connectToMemoryViewer();
	bool sendMessage(std::string pSet,int pRangeStart, int pRangeEnd);
};

#endif /* SRC_COM_LDMM_DATAACCESS_ENCODER_H_ */
