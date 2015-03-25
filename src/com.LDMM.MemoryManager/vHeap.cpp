/*
 * vHeap.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: abrahamon
 */

#include "../com.LDMM.MemoryManager/vHeap.h"
#include <stdio.h>

vHeap* vHeap::HEAP = 0;
bool vHeap::vDEBUG = true;
vHeap::vHeap(int pSize, int pOverweight)
{
	if(vDEBUG){
		std::cout << "vHeap.vHeap	creo un vHeap de : "<<pSize<<" bytes"<<"\n";
		std:: cout <<"\n";
	}
	this->tamanovHeap = pSize;
	this->ptrInicioMemoria = calloc(1,pSize);
	this->ptrUltimaMemoriaLibre = ptrInicioMemoria;
	this->tablaMetadatos = xTable::getInstance();
	this->zonaCritica = 0;
};


vHeap::~vHeap(){
	this->ptrUltimaMemoriaLibre = 0;
	free(this->ptrInicioMemoria);
};

vHeap* vHeap::getInstancia()
{
	if( HEAP != 0)
	{
		return HEAP;
	}else{
		//HEAP = new vHeap(SIZE,0);

		return HEAP;
	}
};

void vHeap::vFreeAll(){
	while(zonaCritica){			// en caso de que otro hilo esta tratando el vHeap
			//usleep(medioDeSegundoMili);
	}
	zonaCritica = true;
	for(Node<xEntry*>* iterador=this->tablaMetadatos->getList()->getHead(); iterador != 0; iterador=iterador->getNext())
	{
		void* erase = iterador->getData()->getOffset();
		free(erase);
		tablaMetadatos->getList()->deleteData(iterador->getData());
	}
	if (vDEBUG)
	{
		cout<<"vHeap.vFreeAll 	vacie el vHeap por completo \n";
	}

	zonaCritica = false;
};
void vHeap::dumpMemory(){};
void vHeap::desfragmentar(){};

void vHeap::garbageCollector()
{
	while(zonaCritica)
	{
		//usleep(medioDeSegundoMili);
	}
	zonaCritica = true;
	for(Node<xEntry*>* iterador=this->tablaMetadatos->getList()->getHead(); iterador != 0; iterador=iterador->getNext())
	{
		if(iterador->getData()->getReferenceCounter() == 0)
		{
			free(iterador->getData()->getOffset());
			tablaMetadatos->getList()->deleteData(iterador->getData());
			if(vDEBUG)
			{
				cout<<"Borre un elemento de la xTable \n";
			}
		}
	}
	zonaCritica = false;
};

void vHeap::control()			//hilo para metodo de control
{
	while(zonaCritica){			// en caso de que otro hilo esta tratando el vHeap
		//usleep(medioDeSegundoMili);
	}							//cada metodo siguiente tiene zonas criticas individuales
	this->garbageCollector();
	this->desfragmentar();
	this->dumpMemory();


}


vRef* vHeap::vMalloc(int pSize, std::string pType)
{
	while(zonaCritica){				//esperar hasta que se libere de zona critica
		//usleep(medioDeSegundoMili);
	}
	this->zonaCritica = true;

	long b = reinterpret_cast<long>(ptrInicioMemoria);
	long a = reinterpret_cast<long>(ptrUltimaMemoriaLibre);
	int memLibre = tamanovHeap-b+a;

	if(vDEBUG){
		std:: cout<< "vHeap.vMalloc	llamada a vMaloc por "<<pSize<<" bytes" <<"\n";
		cout<<"vHeap.vMalloc	ptr Inicio de memoria :"<<b<<"\n";
		cout<<"vHeap.vMalloc	ptr Fin de memoria :"<<a<<"\n";
		cout<<"vHeap.vMalloc	"<< memLibre	<<" bytes de memoria libre  \n";
	}

	if(memLibre >= pSize)
	{
		if(vDEBUG){
			cout <<"vHeap.vMalloc	Si hay espacio suficiente para un "<<pType<<"\n";
		}

		int id =tablaMetadatos->addEntry(pSize,ptrUltimaMemoriaLibre,pType);

		cout<<"No hay flujo hasta este pt \n";// <|-----------------------------*

		vRef* referencia = new vRef(id);
		this->ptrUltimaMemoriaLibre = ptrUltimaMemoriaLibre+pSize;

		this->zonaCritica = false;
		return referencia;

	}else{
		if(vDEBUG)
		{
			cout<< "Los "<<pSize<<" bytes solicitados no caben en: "<<tamanovHeap<< "\n";
		}
		this->zonaCritica = false;
		return 0;
	}

	this->zonaCritica = false;
};

void vHeap::vFree(vRef* pRef)
{
	if(vDEBUG){
		cout << "vfree en vHeap no implementado aun --------- \n";
	}
};




