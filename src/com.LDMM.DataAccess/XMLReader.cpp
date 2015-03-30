/*
 * XMLReader.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: fabian
 */

#include "../com.LDMM.DataAccess/XMLReader.h"
#include <string>
using namespace std;

XMLReader::XMLReader() { root = 0; }
XMLReader::~XMLReader() {}

void XMLReader::loadXMLFile(){
	if(!documento.LoadFile("src/config.xml")){
		cout << "404 File not found" << endl;
	}
}

string XMLReader::getParameter(std::string pParameter){
	TiXmlHandle hDoc(&documento);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);
	root = documento.FirstChildElement();
	if(root == NULL){
		cout<<"Failed to load file: No root element" <<endl;
		documento.Clear();
	}
	cout << "pParameter " << pParameter << endl;
	pElem = root->FirstChildElement(pParameter);
	const char* tell = pElem->GetText();
	cout << "Ob " << tell << endl;
	return "Hey";
}
