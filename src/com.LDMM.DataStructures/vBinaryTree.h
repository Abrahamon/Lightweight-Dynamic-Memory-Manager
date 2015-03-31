/*
 * BinaryTree.h
 *
 *  Created on: Mar 30, 2015
 *      Author: abrahamon
 */

#ifndef SRC_COM_LDMM_DATASTRUCTURES_VBINARYTREE_H_
#define SRC_COM_LDMM_DATASTRUCTURES_VBINARYTREE_H_

#include "vBinaryNode.h"
#include <iomanip>
#include <iostream>
#include <queue>
#include <utility>


using namespace std;

/**
 * Estructura de datos, tipo arbol binario template
 * */
template<class k>
class vBinaryTree{

private:
protected:
	vBinaryNode<k>* _root;

	void insertData(k pData, vBinaryNode<k>* pRoot);
	void imprimirArbol(vBinaryNode<k>* node);
	vBinaryNode<k>* encontrarPadreDe(k pData);
	vBinaryNode<k>* encontrarHijoMasDerecho(vBinaryNode<k>* pNode);

public:
	vBinaryTree();
	void insertar(k pData);
	vBinaryNode<k>* buscar(k pData);
	void eliminar(k pData);
	vBinaryNode<k>* getRaiz();
	void imprimirArbol();
};

/**
 *Constructor
 */
template<class k>
vBinaryTree<k>::vBinaryTree()
{
	this->_root = 0;
}

/**
 * Insertar nueva data al arbol
 * @param pData
 */
template<class k>
void vBinaryTree<k>::insertar(k pData)
{
	if(_root != 0)
	{
		this->insertData(pData,_root);
	}else{
		vBinaryNode<k>* tmp = new vBinaryNode<k>(pData);
		_root = tmp;
	}
}

/**
 * Metodo privado para insertar data
 * cuando no es el primer elemento
 * @param pData nuevo valor
 * @param pNodo, comenzar a buscar posicion correcta a partir de este nodo
 */
template<class k>
void vBinaryTree<k>::insertData(k pData,vBinaryNode<k>* pNodo)
{
	if(pData > pNodo->getData())//se va hacia hacia la derecha
	{
		if(pNodo->hasRight())
		{
			this->insertData(pData,pNodo->getRight());
		}else{
			vBinaryNode<k>* tmp = new vBinaryNode<k>(pData);
			pNodo->setRight(tmp);
		}
	}else						//de caso contrario a la izquierda
	{
		if(pNodo->hasLeft())
		{
			this->insertData(pData,pNodo->getLeft());
		}else{
			vBinaryNode<k>* tmp = new vBinaryNode<k>(pData);
			pNodo->setLeft(tmp);
		}

	}
}

/**
 * Retorna el nodo con la data buscada
 * @param pData a buscar
 * @return el nodo
 */
template<class k>
vBinaryNode<k>* vBinaryTree<k>::buscar(k key)
{
	vBinaryNode<k>* p =_root;
	while((p!=NULL)&&(p->getData()!=key)){
		if(key < p->getData())
		{
			p=p->getLeft();
		}else{
			p=p->getRight();
		}
	}
	return p;
}

/**
 * Metodo que retorna el padre de un nodo buscado
 * @param pData
 * @return
 */
template<class k>
vBinaryNode<k>* vBinaryTree<k>::encontrarPadreDe(k pData)
{
	vBinaryNode<k>* p =_root;
	vBinaryNode<k>* q = 0;
	while((p!=NULL)&&(p->getData() != pData)){
		q=p;
		if( pData < p->getData() )
		{
			p=p->getLeft();
		}
		else{
			p=p->getRight();
		};
	}
	return q;
}

/**
 * Encontrar el nodo mas a la derecha para hacerlo el nuevo padre
 * @param pNode es el node desde donde comienzo a buscar
 * @return nodo mas a la derecha
 */
template<class k>
vBinaryNode<k>* vBinaryTree<k>::encontrarHijoMasDerecho(vBinaryNode<k>* pNode){
	vBinaryNode<k>* righty=pNode;
	while(righty->getRight() != NULL)
		righty=righty->getRight();
	return righty;
}

/**
 * Metodo para eliminar data
 * @param val, es el dato a eliminar
 */
template<class k>
void vBinaryTree<k>::eliminar(k pData)
{
	vBinaryNode<k>* pNodetmp = buscar(pData);
	if(pNodetmp!=0){
		//if both of child of node are null(leaf node)
		if(pNodetmp->getLeft() == 0 && pNodetmp->getRight() == NULL){
			if(pNodetmp!=_root){
				vBinaryNode<k>* padre= encontrarPadreDe(pData);
				if(pData < padre->getData())
					padre->setLeft(NULL);
				else
					padre->setRight(NULL);
			}else
			{
				_root=NULL;
			};
		delete (pNodetmp);
		}
		else if(pNodetmp->getLeft() != NULL  && pNodetmp->getRight() == NULL){//cuando solo el hijo izquierdo no es nullo
			if(pNodetmp!=_root){
				vBinaryNode<k>* parent=encontrarPadreDe(pData);
				if(pData < parent->getData())
					parent->setLeft(pNodetmp->getLeft());
				else
					parent->setRight(pNodetmp->getLeft());
				}
			else _root=NULL;
			delete (pNodetmp);
		  }
		  //if only right child is not null
		  else if(pNodetmp->getLeft() == NULL  &&  pNodetmp->getRight() != NULL){
			   if(pNodetmp!=_root){
				   vBinaryNode<k>* padre=encontrarPadreDe(pData);
					if( pData < padre->getData())
						padre->setLeft(pNodetmp->getRight());
					else
						padre->setRight(pNodetmp->getRight());
			   }
			   else _root=NULL;
			   delete (pNodetmp);
		  }
		else{										//en caso de que ambos sean NO nulos
			vBinaryNode<k>* elMasDerecho = encontrarHijoMasDerecho(pNodetmp->getLeft());
			vBinaryNode<k>* padre=encontrarPadreDe(elMasDerecho->getData());
			pNodetmp->setData(elMasDerecho->getData());
			if(padre != pNodetmp)
				padre->setRight(elMasDerecho->getLeft());
			else
				pNodetmp->setLeft(elMasDerecho->getLeft());
		}
	}
}

/**
 * Auxiliar publico para llamar al print
 */
template <class k>
void vBinaryTree<k>::imprimirArbol()
{
	imprimirArbol(_root);
}

/**
 * Imprimir por niveles desde la raiz recibida
 * @param node comenzar a imprimir desde aca
 */
template <class k>
void vBinaryTree<k>::imprimirArbol(vBinaryNode<k>* node) {
    if (0 == node) {
        return;
    }
    int level = 0;

    // Use a queue for breadth-first traversal of the tree.  The pair is
    // to keep track of the depth of each node.  (Depth of root node is 1.)
    typedef std::pair< vBinaryNode<k>*,int> node_level;
    std::queue<node_level> q;
    q.push(node_level(node, 1));

    while (!q.empty()) {
        node_level nl = q.front();
        q.pop();
        if (0 != (node = nl.first)) {
            if (level != nl.second) {
                std::cout << " Nivel " << nl.second << ": ";
                level = nl.second;
            }
            std::cout << node->getData() << ' ';
            q.push(node_level(node->getLeft(),  1 + level));
            q.push(node_level(node->getRight(), 1 + level));
        }
    }
    std::cout << std::endl;
}


#endif /* SRC_COM_LDMM_DATASTRUCTURES_VBINARYTREE_H_ */
