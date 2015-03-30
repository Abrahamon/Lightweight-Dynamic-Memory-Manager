/*
 * XMLReader.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: fabian
 */

#include "../com.LDMM.DataAccess/XMLReader.h"
#include <string>

XMLReader::XMLReader() { root = 0; }
XMLReader::~XMLReader() {}

void XMLReader::loadXMLFile(){
	if(!documento.LoadFile("src/config.xml")){
		std::cout << "404 File not found" << std::endl;
	}
}

std::string XMLReader::getParameter(std::string pParameter){
	TiXmlHandle hDoc(&documento);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);
	root = documento.FirstChildElement();
	if(root == NULL){
		std::cout<<"Failed to load file: No root element" <<std::endl;
		documento.Clear();
	}
	std::cout << "pParameter " << pParameter << std::endl;
	pElem = root->FirstChildElement(pParameter);
	const char* tell = pElem->GetText();
	std::cout << "Ob " << tell << std::endl;
	return "Hey";
}
