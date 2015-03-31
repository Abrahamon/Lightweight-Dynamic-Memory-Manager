/*
 * vHeap.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: abrahamon
 */

#include "../com.LDMM.MemoryManager/vHeap.h"
#include <stdio.h>

vHeap* vHeap::HEAP = 0;

vHeap::vHeap(int pSize, int pOverweight)
{
	if(Constants::vDEBUG == "TRUE"){
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
		HEAP = new vHeap(Constants::SIZE,0);
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
		void* tmpPtr = ptrInicioMemoria + iterador->getData()->getOffset();
		string type = iterador->getData()->getType();
		void* erase;
		if(type=="vInt"){ int* erase = (int*)tmpPtr; }
		else if(type=="vChar"){ int* erase = (int*)tmpPtr; }
		else if(type=="vBool"){ bool* erase = (bool*)tmpPtr; }
		else if(type=="vLong"){ long* erase = (long*)tmpPtr; }
		else if(type=="vFloat"){ float* erase = (float*)tmpPtr; }
		else if(type=="vString"){ if(Constants::vDEBUG == "TRUE"){cout<<"vHeap::vFreeAll		Eliminado de memoria para string no implementado aun";} }
		else{
			if(Constants::vDEBUG == "TRUE")
			{
				cout<<"vHeap::vFreeAll 	Error en el tipo de dato a eliminar";
				return;
			}
		}
		free(erase);
		tablaMetadatos->getList()->deleteData(iterador->getData());
	}
	if (Constants::vDEBUG == "TRUE")
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
			free(ptrInicioMemoria+(iterador->getData()->getOffset()));
			tablaMetadatos->getList()->deleteData(iterador->getData());
			if(Constants::vDEBUG == "TRUE")
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
		//sleep(1);

	}

	this->zonaCritica = true;

	long b = reinterpret_cast<long>(ptrInicioMemoria);
	long a = reinterpret_cast<long>(ptrUltimaMemoriaLibre);
	int memLibre = tamanovHeap-(a-b);

	if(Constants::vDEBUG == "TRUE"){
		std:: cout<< "vHeap.vMalloc	llamada a vMaloc por "<<pSize<<" bytes" <<"\n";
		cout<<"vHeap.vMalloc	ptr Inicio de memoria :"<<b<<"\n";
		cout<<"vHeap.vMalloc	ptr Fin de memoria :"<<a<<"\n";
		cout<<"vHeap.vMalloc	"<< memLibre	<<" bytes de memoria libre  \n";

		cout<<"ingreso: "<<""<<"dato ingresado, leido de memoria: "<<*(int*)(ptrUltimaMemoriaLibre-4)<<"\n";
	}

	if(memLibre >= pSize)
	{
		if(Constants::vDEBUG == "TRUE"){
			cout <<"vHeap.vMalloc	Si hay espacio suficiente para un "<<pType<<"\n";
			cout<< "\n";
		}

		int id =tablaMetadatos->addEntry(pSize, a-b,pType);
		cout<<"SI \n";
		vRef* referencia = new vRef(id);
		this->ptrUltimaMemoriaLibre = ptrUltimaMemoriaLibre+pSize;

		this->zonaCritica = false;

		return referencia;

	}else{
		if(Constants::vDEBUG == "TRUE")
		{
			cout<< "Los "<<pSize<<" bytes solicitados no caben en: "<<tamanovHeap<< "\n";
		}
		this->zonaCritica = false;
	};

	this->zonaCritica = false;
};

void vHeap::vWrite(int pID, void* pData)
{

}

void vHeap::vFree(vRef* pRef)
{
	if(Constants::vDEBUG == "TRUE"){
		cout << "vfree en vHeap no implementado aun --------- \n";
	}
}




