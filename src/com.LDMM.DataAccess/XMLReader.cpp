/*
 * XMLReader.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: fabian
 */

#include "XMLReader.h"
#include <string>

using namespace std;

XMLReader::XMLReader() { root = 0; }

XMLReader::~XMLReader() {}

void XMLReader::loadFile(){
	if(!documento.LoadFile("src/config.xml")){
		std::cout << "404 XML Not Found" << std::endl;
	}

}
string XMLReader::getParameter(string pParameter){
	TiXmlHandle hDoc(&documento);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);
	root = documento.FirstChildElement();
	if(root == NULL){
		cout <<"Failed to load file: No root element"<< endl;
		documento.Clear();
	}
	pElem = root->FirstChildElement(pParameter);
	return pElem->GetText();
}
