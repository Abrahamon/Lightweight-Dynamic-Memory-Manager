/*
 * logWriter.h
 *
 *  Created on: Apr 18, 2015
 *      Author: fabian
 */

#ifndef SRC_COM_LDMM_DATAACCESS_LOGWRITER_H_
#define SRC_COM_LDMM_DATAACCESS_LOGWRITER_H_
#include <string>
/*
 * Clase para escribir
 * en un archivo .log la
 * cofiguracion de nuestro debug
 */
class logWriter {
public:
	logWriter(){};
	virtual ~logWriter();
	static void write(std::string pData);

};

#endif /* SRC_COM_LDMM_DATAACCESS_LOGWRITER_H_ */
