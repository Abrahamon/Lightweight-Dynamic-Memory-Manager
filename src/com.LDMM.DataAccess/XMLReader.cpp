/*
 * XMLReader.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: fabian
 */

#include "XMLReader.h"
#include <string>

using namespace std;

XMLReader::XMLReader() { root = 0;}

XMLReader::~XMLReader() {}

/*
 * loadFile()
 * Carga el archivo config.xml que se encuentra en
 * la carpeta raíz del programa
 */
void XMLReader::loadFile(){
	if(!documento.LoadFile("src/config.xml")){
		std::cout << "404 XML Not Found" << std::endl;
	}

}
/*
 * getParameter()
 * TiXmlHandle hDoc(&documento), permite manejar el documento XML
 * por medio de los elementos (nodos XML), moviendose con un
 * puntero "pElem".
 *
 * Retorna un string con el valor del parámetro especificado. Si
 * el parámetro ingresado no existe, indica esto mostrando en
 * consola el error asociado.
 */
 string XMLReader::getParameter(string pParameter){
	//loadFile();
	TiXmlHandle hDoc(&documento);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);
	root = documento.FirstChildElement();
	if(root == NULL){
		cout <<"Failed to load file: No root element"<< endl;
		documento.Clear();
	}
	if(pElem = root->FirstChildElement(pParameter)){
		return pElem->GetText();
	}
	else{
		return "Error: Not such parameter. Please check your entry";
	}


}
