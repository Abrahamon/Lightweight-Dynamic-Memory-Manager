/*
 * vHeap.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: abrahamon
 */

#include "../com.LDMM.MemoryManager/vHeap.h"

vHeap* vHeap::HEAP = 0;

vHeap::vHeap(int pSize, int pOverweight)
{
	if(vDEBUG){
		std::cout << "creo un vHeap de : "<<pSize<<" bytes"<<"\n";
		std:: cout <<"\n";
	}
	this->tamanovHeap = pSize;
	this->ptrInicioMemoria = calloc(1,pSize);
	this->ptrUltimaMemoriaLibre = ptrInicioMemoria;
	this->tablaMetadatos = new xTable();
	this->ColectorDeBasura = new garbageCollector();
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
		HEAP = new vHeap(SIZE,0);

		return HEAP;
	}
};

vRef* vHeap::vMalloc(int pSize, std::string pType)
{
	while(zonaCritica){				//esperar hasta que se libere de zona critica
		usleep(medioDeSegundoMili);
	}
	this->zonaCritica = true;

	long b = reinterpret_cast<long>(ptrInicioMemoria);
	long a = reinterpret_cast<long>(ptrUltimaMemoriaLibre);
	int memLibre = tamanovHeap-b+a;

	if(vDEBUG){
		std:: cout<< "  llamada a vMaloc:" <<"\n";
		cout<<"ptr Inicio de memoria :"<<b<<"\n";
		cout<<"ptr Fin de memoria :"<<a<<"\n";
		cout<<memLibre <<" bytes de memoria libre  \n";
	}

	if(memLibre >= pSize)
	{
		if(vDEBUG){
			cout <<"hay espacio suficiente para un "<<pType<<"\n";
		}
		tablaMetadatos->addEntry(pSize,ptrUltimaMemoriaLibre,pType);
	}

	if(pType == "vInt"){}
	else if(pType == "vChar"){}
	else if(pType == "vFloat"){}
	else if(pType == "vLong"){}
	else{std::cout <<"vHeap.vMalloc con pType erroneo";};
//	tabla->addEntry(pSize,   , pType);
	this->zonaCritica = false;

};

void vHeap::vFree(){};
void vHeap::vFreeAll(){};

void vHeap::dumpMemory()
{

}



