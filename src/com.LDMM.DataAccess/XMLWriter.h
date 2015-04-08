/*
 * XMLWriter.h
 *
 *  Created on: Apr 8, 2015
 *      Author: abrahamon
 */

#ifndef SRC_COM_LDMM_DATAACCESS_XMLWRITER_H_
#define SRC_COM_LDMM_DATAACCESS_XMLWRITER_H_

#include "../com.LDMM.DataAccess/lib.tinyxml/tinyxml.h"

class XMLWriter {
private:
	TiXmlDocument documento;
	TiXmlElement* root;

public:
	XMLWriter();
	void XMLWrite();
	virtual ~XMLWriter();
};

#endif /* SRC_COM_LDMM_DATAACCESS_XMLWRITER_H_ */
