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
	this->_overweight= pOverweight;
	this->tamanoMemoriaPaginadaUsada = 0;
	this->tamanovHeap = pSize;
	this->ptrInicioMemoria = calloc(1,pSize);
	this->ptrUltimaMemoriaLibre = ptrInicioMemoria;
	this->tablaMetadatos = xTable::getInstance();
	this->estaEnZonaCritica = 0;
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
		HEAP = new vHeap(Constants::SIZE,Constants::OVERWEIGHT);
		return HEAP;
	}
};

void vHeap::vFreeAll(){
	while(estaEnZonaCritica){			// en caso de que otro hilo esta tratando el vHeap
			//usleep(medioDeSegundoMili);
	}
	estaEnZonaCritica = true;
	for(vNode<xEntry*>* iterador=this->tablaMetadatos->getList()->getHead(); iterador != 0; iterador=iterador->getNext())
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
	estaEnZonaCritica = false;
};

void vHeap::dumpMemory(){
	while(estaEnZonaCritica)
	{
		//usleep(medioDeSegundoMili);
	}
	estaEnZonaCritica = true;
	void* posiciones=ptrInicioMemoria;
	for(int i=0;i< tamanovHeap;i++){
		char* tmp=(char*)(posiciones+i);
		string s;
		int decimal=(char)(*tmp+0);
		ofstream fs("dump.txt");
		if (decimal!=0){
			while(decimal>1)
			{
				int resto=decimal%2;
				if(resto==1)s+="1";
				else s+="0";
				decimal/=2;
			}
			s+="1";
			reverse(s.begin(),s.end());
			for(int i=0;i< 8-s.length();i++){
				fs << 0;
			}
			fs << s;
		}
		else{
			fs << 0;
		}
	}
	estaEnZonaCritica = false;
};

void vHeap::desfragmentar()
{
	while(estaEnZonaCritica)
	{
		//usleep(medioDeSegundoMili);
	}
	estaEnZonaCritica = true;
	estaEnZonaCritica = false;
};

void vHeap::garbageCollector()
{
	while(estaEnZonaCritica)
	{
		//usleep(medioDeSegundoMili);
	}
	estaEnZonaCritica = true;
	for(vNode<xEntry*>* iterador=this->tablaMetadatos->getList()->getHead(); iterador != 0; iterador=iterador->getNext())
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
	estaEnZonaCritica = false;
};

void vHeap::control()			//hilo para metodo de control
{
	while(estaEnZonaCritica){			// en caso de que otro hilo esta tratando el vHeap
		//usleep(medioDeSegundoMili);
	}							//cada metodo siguiente tiene zonas criticas individuales
	this->garbageCollector();
	this->desfragmentar();
	this->dumpMemory();


}


vRef* vHeap::vMalloc(int pSize, std::string pType)
{

	while(estaEnZonaCritica){				//esperar hasta que se libere de zona critica
		//usleep(medioDeSegundoMili);
		//sleep(1);
	}
	this->estaEnZonaCritica = true;

	long b = reinterpret_cast<long>(ptrInicioMemoria);
	long a = reinterpret_cast<long>(ptrUltimaMemoriaLibre);
	int memLibre = tamanovHeap-(a-b);

	if(0 == "TRUE"){
		std:: cout<< "vHeap.vMalloc	llamada a vMaloc por "<<pSize<<" bytes" <<"\n";
		cout<<"vHeap.vMalloc	ptr Inicio de memoria :"<<b<<"\n";
		cout<<"vHeap.vMalloc	ptr Fin de memoria :"<<a<<"\n";
		cout<<"vHeap.vMalloc	"<< memLibre	<<" bytes de memoria libre  \n";

		cout<<"ingreso: "<<""<<"dato ingresado, leido de memoria: "<<*(int*)(ptrUltimaMemoriaLibre-4)<<"\n";
	}

	if(memLibre >= pSize)
	{
		if(0 == "TRUE"){
			cout <<"vHeap.vMalloc	Si hay espacio suficiente para un "<<pType<<"\n";
			cout<< "\n";
		}

		int id =tablaMetadatos->addEntry(pSize, a-b,pType);
		vRef* referencia = new vRef(id);
		this->ptrUltimaMemoriaLibre = ptrUltimaMemoriaLibre+pSize;

		this->estaEnZonaCritica = false;

		return referencia;

	}else{	//no cabe el dato, ahora tratemos de paginar.
		if(0 == "TRUE")
		{
			cout<< "Los "<<pSize<<" bytes solicitados no caben en: "<<tamanovHeap<< ". Hay que paginar\n";
		}
		this->estaEnZonaCritica = false;
		if(paginar(pSize))				//tratamos de paginar un tamaño mayor al pedido en vMalloc
		{
			this->desfragmentar();		//para asegurarnos que quepa

		}else							// el objeto no cabe en ningun lugar
			if(0=="TRUE")
				cout<<"No hay espacio para la paginacion, ni espacio en la memoria \n";
	};


};

bool vHeap::paginar(int pSize)
{
	if((tamanovHeap*_overweight)-tamanoMemoriaPaginadaUsada < pSize)//el tamaño que se requiere escribir en memoria no cabe. No hay paginacion disponible
	{
		return false;
	}else			//si hay espacio suficiente solo hay que hacer paginacion
	{

		//seleccionar un grupo de objetos que juntos sean igual o mas grandes que el tamaño requerido
		//pero que no sobre pasen el tamaño de la paginacion posible

		vLinkedList<xEntry*>* seleccionados = new vLinkedList<xEntry*>();
		vNode<xEntry*>* node = xTable::getInstance()->getList()->getHead();

		for(int it = 0; it < pSize; it = it+0)
		{
			seleccionados->insertTail(node->getData());
			node=node->getNext();
			it = it+node->getData()->getSize();
			if(node == 0)
				return false; 					//no hay datos suficientes para paginar y guardar la memoria deseada;
		};
		// en este punto tenemos la lista de seleccionados para paginar.


		fstream file("vHeap.bin", ios::binary | ios::in | ios::out | ios::trunc);
		file.write("a",1);
		file.close();
	}
}


void vHeap::vWrite(int pID, void* pData)
{

}

void vHeap::vFree(vRef* pRef)
{
	if(Constants::vDEBUG == "TRUE"){
		cout << "vfree en vHeap no implementado aun --------- \n";
	}
}




