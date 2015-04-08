/*
 * XMLReader.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: fabian
 */

#include "XMLReader.h"
#include "../com.LDMM.DataAccess/XMLReader.h"
#include <string>
#include <iostream>

/**
 * El constructor inicializa root a 0
 */
XMLReader::XMLReader() { root = 0; }
XMLReader::~XMLReader() {}

/**
 * Carga el archivo config.xml, para poder leer sus datos
 */
void XMLReader::loadXMLFile(){
	/*bool loadOkay = documento.LoadFile("src/config.xml");
	if (!loadOkay){
		std::cout << "*XML* Failed to load file. File not found" << std::endl;
	}*/

	//PRUEBAS
	bool loadOkay = documento.LoadFile("src/config_pbs.xml");
	if (!loadOkay){
		std::cout << "*XML* Failed to load file. File not found" << std::endl;
	}
}

/**
 * Retorna el valor del parámetro que se busca en el archivo XML
 * El tipo de entrada y retorno es únicamente un const char*
 */
const char* XMLReader::getParameter(const char* pParameter){
	TiXmlElement* pElem;
	root = documento.FirstChildElement("root"); //Se mueve hacia el Nodo raíz del .xml
	if(root == 0){
		std::cout<<"*XML* Failed to search param: No root element" <<std::endl;
		documento.Clear(); //Si ese nodo no exite con ese nombre, limpia el documento.
	}
	pElem = root->FirstChildElement(pParameter); //Ingresa al nodo del Dato que se busca (pParameter)
	const char* output = pElem->Attribute("value");//Obtiene el valor del Dato que se busca

	std::cout << "*XML* "<<"<<<Param: " << pParameter << " * Value: " << output << " >>>" << std::endl;

	return output; //Retorna el valor encontrado
}
