/*
 * XMLReader.h
 *
 *  Created on: Mar 20, 2015
 *      Author: fabian
 */

#ifndef SRC_COM_LDMM_DATAACCESS_XMLREADER_H_
#define SRC_COM_LDMM_DATAACCESS_XMLREADER_H_
//#include <src/tinyxml.h>
#include <tinyxml.h>
#include <string>

/**
 * XMLReader
 * Clase que permite la lectura de archivos XML simples.
 *
 * @author Fabian Solano Madriz
 * @date 03/20/2015
 */
class XMLReader {
private:
	/**
	 * TiXmlDocument documento: carga el documento XML especificado
	 * TiXmlElement* root: Nodo XML cargado inicialmente
	 */
	TiXmlDocument documento;
	TiXmlElement* root;
public:
	XMLReader();
	virtual ~XMLReader();
	void loadFile();
	static std::string getParameter(std::string pParameter);
};

#endif /* SRC_COM_LDMM_DATAACCESS_XMLREADER_H_ */
