/*
 * XMLWriter.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: abrahamon el mas pero mas bananon
 */

#include "XMLWriter.h"

XMLWriter::XMLWriter() {
	this->root=0;
}

XMLWriter::~XMLWriter() {}

void XMLWriter::XMLWrite(string pType, string Data)
{
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );

	TiXmlElement* element = new TiXmlElement( "root" );
	doc.LinkEndChild( element );
	TiXmlElement* element2 = new TiXmlElement( "Type" );
	TiXmlElement* element3 = new TiXmlElement( "Value" );

	string ab = "vInt";
	element2->SetAttribute("value","");

	element3->SetAttribute("value","3");

	element->LinkEndChild( element2 );
	element->LinkEndChild( element3 );


	doc.SaveFile( "src/vHeap.xml" );

}
