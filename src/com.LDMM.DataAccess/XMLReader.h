/*
 * XMLReader.h
 *
 *  Created on: Mar 27, 2015
 *      Author: fabian
 */

#ifndef SRC_COM_LDMM_DATAACCESS_XMLREADER_H_
#define SRC_COM_LDMM_DATAACCESS_XMLREADER_H_

#include "../com.LDMM.DataAccess/lib.tinyxml/tinyxml.h"
#include <string>

class XMLReader {
private:
	TiXmlDocument documento;
	TiXmlElement* root;
public:
	XMLReader();
	virtual ~XMLReader();
	void loadXMLFile(std::string pData);
	const char* getParameter(const char* pParameter);

};

#endif /* SRC_COM_LDMM_DATAACCESS_XMLREADER_H_ */
