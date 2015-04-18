/*
 * XMLWriter.h
 *
 *  Created on: Apr 8, 2015
 *      Author: abrahamon el mas bananon
 */

#ifndef SRC_COM_LDMM_DATAACCESS_XMLWRITER_H_
#define SRC_COM_LDMM_DATAACCESS_XMLWRITER_H_

#include "../com.LDMM.DataAccess/lib.tinyxml/tinyxml.h"
#include "string"
using namespace std;
class XMLWriter {
private:
	TiXmlDocument documento;
	TiXmlElement* root;

public:
	XMLWriter();
	virtual ~XMLWriter();
	void XMLWrite(string pType, string Data);

};

#endif /* SRC_COM_LDMM_DATAACCESS_XMLWRITER_H_ */
