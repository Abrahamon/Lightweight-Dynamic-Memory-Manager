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

