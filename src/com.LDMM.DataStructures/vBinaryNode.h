/*
 * BinaryNode.h
 *
 *  Created on: Mar 30, 2015
 *      Author: abrahamon
 */

#ifndef SRC_COM_LDMM_DATASTRUCTURES_VBINARYNODE_H_
#define SRC_COM_LDMM_DATASTRUCTURES_VBINARYNODE_H_

using namespace std;

/**
 * Nodo para el arbol binario, template
 * */
template<class k>
class vBinaryNode {

private:
	k _data;

protected:
	vBinaryNode<k>* _left;
	vBinaryNode<k>* _right;

public:
	vBinaryNode(k pData);
	k getData();
	vBinaryNode<k>* getLeft();
	vBinaryNode<k>* getRight();
	void setLeft(vBinaryNode<k>* pNode);
	void setRight(vBinaryNode<k>* pNode);
	void setData(k pData);
	bool hasLeft();
	bool hasRight();
};

/**
 * Constructor para los nodos del arbol
 * @param pData
 */
template<class k>
vBinaryNode<k>::vBinaryNode(k pData)
{
	this->_data = pData;
	this->_left = 0;
	this->_right = 0;
}

/**
 * Obtener nuestra data del nodo
 * @return data
 */
template<class k>
k vBinaryNode<k>::getData()
{
	return this->_data;
}

/**
 * obtener el hijo izquierdo
 * @return
 */
template<class k>
vBinaryNode<k>* vBinaryNode<k>::getLeft(){ return this->_left;}

/**
 * obtener el hijo derecho
 * @return
 */
template<class k>
vBinaryNode<k>* vBinaryNode<k>::getRight(){return this->_right;}

/**
 * setter para el hijo izquierdo
 * @param pNode
 */
template<class k>
void vBinaryNode<k>::setLeft(vBinaryNode<k>* pNode){ this->_left=pNode;}

/**
 * setter para el hijo derecho
 * @param pNode
 */
template<class k>
void vBinaryNode<k>::setRight(vBinaryNode<k>* pNode){ this->_right=pNode;}

/**
 * Configurar la data del nodo
 * @param pData data
 */
template<class k>
void vBinaryNode<k>::setData(k pData){ this->_data = pData;}

/**
 * responde: Tiene hijo izquierdo?
 * @return
 */
template<class k>
bool vBinaryNode<k>::hasLeft()
{
	if(_left==0){ return false; }
	else{ return true; }
}

/**
 * responde: Tiene hijo derecho?
 */
template<class k>
bool vBinaryNode<k>::hasRight()
{
	if(_right==0){ return false; }
	else{ return true; }
}


#endif /* SRC_COM_LDMM_DATASTRUCTURES_VBINARYNODE_H_ */
