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
	this->_tamanoMemoriaPaginadaUsada = 0;
	this->_tamanovHeap = pSize;
	this->_ptrInicioMemoria = calloc(1,pSize);
	this->_ptrUltimaMemoriaLibre = _ptrInicioMemoria;
	this->_tablaMetadatos = xTable::getInstance();
	this->_estaEnZonaCritica = 0;
};


vHeap::~vHeap(){
	_ptrUltimaMemoriaLibre = 0;
	_ptrInicioMemoria=0;
	_tablaMetadatos->getList()->vaciar();
	_estaEnZonaCritica = false;
	_tamanoMemoriaPaginadaUsada =0;
	_overweight = 0;
	_tamanovHeap =0;
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
	while(_estaEnZonaCritica){			// en caso de que otro hilo esta tratando el vHeap
			//usleep(medioDeSegundoMili);
	}
	_estaEnZonaCritica = true;
	for(vNode<xEntry*>* iterador=this->_tablaMetadatos->getList()->getHead(); iterador != 0; iterador=iterador->getNext())
	{
		void* tmpPtr = _ptrInicioMemoria + iterador->getData()->getOffset();
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
		_tablaMetadatos->getList()->deleteData(iterador->getData());
	}
	if (Constants::vDEBUG == "TRUE")
	{
		cout<<"vHeap.vFreeAll 	vacie el vHeap por completo \n";
	}
	_estaEnZonaCritica = false;
};

void vHeap::dumpMemory(){
	while(_estaEnZonaCritica)
	{
		//usleep(medioDeSegundoMili);
	}
	_estaEnZonaCritica = true;
	void* posiciones=_ptrInicioMemoria;
	for(int i=0;i< _tamanovHeap;i++){
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
	_estaEnZonaCritica = false;
};

void vHeap::desfragmentar()
{
	while(_estaEnZonaCritica)
	{
		//usleep(medioDeSegundoMili);
	}
	_estaEnZonaCritica = true;
	_estaEnZonaCritica = false;
};

void vHeap::garbageCollector()
{
	while(_estaEnZonaCritica)
	{
		//usleep(medioDeSegundoMili);
	}
	_estaEnZonaCritica = true;
	for(vNode<xEntry*>* iterador=this->_tablaMetadatos->getList()->getHead(); iterador != 0; iterador=iterador->getNext())
	{
		if(iterador->getData()->getReferenceCounter() == 0)
		{
			free(_ptrInicioMemoria+(iterador->getData()->getOffset()));
			_tablaMetadatos->getList()->deleteData(iterador->getData());
			if(Constants::vDEBUG == "TRUE")
			{
				cout<<"Borre un elemento de la xTable \n";
			}
		}
	}
	_estaEnZonaCritica = false;
};

void vHeap::control()			//hilo para metodo de control
{
	while(_estaEnZonaCritica){			// en caso de que otro hilo esta tratando el vHeap
		//usleep(medioDeSegundoMili);
	}							//cada metodo siguiente tiene zonas criticas individuales
	this->garbageCollector();
	this->desfragmentar();
	this->dumpMemory();


}


vRef* vHeap::vMalloc(int pSize, std::string pType)
{

	while(_estaEnZonaCritica){				//esperar hasta que se libere de zona critica
		//usleep(medioDeSegundoMili);
		//sleep(1);
	}
	this->_estaEnZonaCritica = true;

	long b = reinterpret_cast<long>(_ptrInicioMemoria);
	long a = reinterpret_cast<long>(_ptrUltimaMemoriaLibre);
	int memLibre = _tamanovHeap-(a-b);

		std:: cout<< "vHeap.vMalloc	llamada a vMaloc por "<<pSize<<" bytes" <<"\n";
		cout<<"vHeap.vMalloc	ptr Inicio de memoria :"<<b<<"\n";
		cout<<"vHeap.vMalloc	ptr Fin de memoria :"<<a<<"\n";
		cout<<"vHeap.vMalloc	"<< memLibre	<<" bytes de memoria libre  \n";


		cout<<"ingreso: "<<""<<"dato ingresado, leido de memoria: "<<*(int*)(_ptrUltimaMemoriaLibre-4)<<"\n";

	if(memLibre >= pSize)
	{
		if(Constants::vDEBUG == "TRUE"){
			cout <<"vHeap.vMalloc	Si hay espacio suficiente para un "<<pType<<"\n";
			cout<< "\n";
		}

		int id =_tablaMetadatos->addEntry(pSize, a-b,pType);
		vRef* referencia = new vRef(id);
		this->_ptrUltimaMemoriaLibre = _ptrUltimaMemoriaLibre+pSize;

		this->_estaEnZonaCritica = false;

		return referencia;

	}else{	//no cabe el dato, ahora tratemos de paginar.
		if(0 == "TRUE")
		{
			cout<< "Los "<<pSize<<" bytes solicitados no caben en: "<<_tamanovHeap<< ". Hay que paginar\n";
		}
		this->_estaEnZonaCritica = false;
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
	if((_tamanovHeap*_overweight)-_tamanoMemoriaPaginadaUsada < pSize)//el tamaño que se requiere escribir en memoria no cabe. No hay paginacion disponible
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




