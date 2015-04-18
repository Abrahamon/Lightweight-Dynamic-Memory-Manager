/*
 * xTable.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: fabian
 */
#include <stdlib.h>
#include "xTable.h"
#include "xEntry.h"
#include "../com.LDMM.DataStructures/vLinkedList.h"
#include "../Constants.h"


xTable::xTable() {}
xTable::~xTable() {}

xTable* xTable::_xHashTable = 0;
vLinkedList<xEntry*>* xTable::_ObjectsList;

/*
 * Método que permite obtener la instancia
 * actual del xTable. Al ser una clase singleton
 * debe existir una única instancia.
 */
xTable* xTable::getInstance(){
	if(_xHashTable == 0){
		static xTable self;

		_xHashTable = &self;
		_ObjectsList = new vLinkedList<xEntry*>;
	}
	return _xHashTable;
}

/*
 * Método que retorna un xEntry con toda la
 * información de un objeto específico.
 *
 * @param pID: id asociado al objeto.
 */
xEntry* xTable::getObjectInfo(int pID){
	vNode<xEntry*>* tmpEntry = _ObjectsList->getHead();
	for(int i = 0; i < pID; i++){
		tmpEntry = tmpEntry->getNext();
	}
	return tmpEntry->getData();
}

/*
 * Método que permite obtener el Offset
 * de un xEntry específico dentro de la tabla.
 *
 * @param pID: id del xEntry a buscar
 */
int xTable::getOffSetDelXEntry(int pID){
	for(vNode<xEntry*>* tmpEntry = _ObjectsList->getHead(); tmpEntry != 0 ; tmpEntry = tmpEntry->getNext()){
		if(tmpEntry->getData()->getID() == pID)
		{
			return tmpEntry->getData()->getOffset();
		}
	}
	return -1;
}

/*
 * Método que permite añadir un xEntry a la tabla, esto
 * es necesario cada vez que se crea un nuevo objeto.
 * Pues en el xEntry se almacena toda la información
 * del nuevo objeto.
 *
 * @param pSize :Tamaño del nuevo dato
 * @param pOffset:Offset del nuevo dato
 * @param pType: tipo del nuevo dato
 */
int xTable::addEntry(int pSize,int pOffset,string pType){
	int pID;
	if( _ObjectsList->isEmpty() ){

		pID=1;
	}
	else{
		pID = (_ObjectsList->getTail()->getData()->getID())+1;
	}
	xEntry* temp = new xEntry(pID,pSize,pOffset,pType);
	_ObjectsList->insertTail(temp);
	return pID;
}

/*
 * Método que permite obtener la lista de objetos
 * actuales del xTable. De esta forma se puede
 * buscar un xEntry específico
 */
vLinkedList<xEntry*>* xTable::getList(){
	return this->_ObjectsList;
}

xEntry* xTable::getXEntry(int pId){
	vNode<xEntry*>* node = _ObjectsList->getHead();
	for(vNode<xEntry*>* i =0; i<_ObjectsList->getLength();i++){
		if(node->getData()->getID()==pId){
			return node->getData();
		}else
		{
			node = node->getNext();
		}
	}
}
