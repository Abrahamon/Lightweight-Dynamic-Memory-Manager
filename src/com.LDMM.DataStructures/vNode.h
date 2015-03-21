/*
 * vNode.h
 *
 *  Created on: Mar 16, 2015
 *      Author: fabian
 */

#ifndef SRC_VNODE_H_
#define SRC_VNODE_H_

/**
 * Clase Node para la lista doblemente enlazada
 */
template<class k>
class Node{

private:
	k _data;
	Node* _next;
	Node* _previous;
public:
	Node(k pData);
	void setData(k);
	void setNext(Node<k>*);
	void setPrevious(Node<k>*);

	k getData();
	Node<k>* getNext();
	Node<k>* getPrevious();
};

template<class k>
Node<k>::Node(k pData){
	_data = pData;
	_next = 0;
	_previous = 0;
}

/**
 * Método Constructor de la clase, en el que se establece el dato
 * y se apuntan _next y _previous a un puntero nulo.
 *//*
template<class k>
Node<k>::Node(k pData){
	_data = pData;
	_next = 0;
	_previous = 0;
}*/
/**
 * Método para definir el dato del nodo.
 */
template<class k>
void Node<k>::setData(k pData){
	_data = pData;
}
/**
 * Método para definir el nodo siguiente del nodo actual
 */
template<class k>
void Node<k>::setNext(Node<k>* pNext){
	_next = pNext;
}
/**
 * Método para definir el nodo previo del nodo actual
 */
template<class k>
void Node<k>::setPrevious(Node<k>* pPrevious){
	_previous = pPrevious;
}
/**
 * Método para obtener el dato del Nodo
 */
template<class k>
k Node<k>::getData(){
	return _data;
}
/**
 * Método para obtener el nodo siguiente del nodo actual
 */
template<class k>
Node<k>* Node<k>::getNext(){
	return _next;
}
/**
 * Método para obtener el nodo previo del nodo actual
 */
template<class k>
Node<k>* Node<k>::getPrevious(){
	return _previous;
}


#endif /* SRC_VNODE_H_ */
