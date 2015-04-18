/*
 * vHeap.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: abrahamon
 */

#include "../com.LDMM.MemoryManager/vHeap.h"
#include <stdio.h>

vHeap* vHeap::HEAP = 0;

/**
 * Construtor
 * @param pSize tamaño que solicita el vHeap para guardar datos
 * @param pOverweight	sobrecarga, para la paginacion
 */
vHeap::vHeap(int pSize, int pOverweight)
{
	if(Constants::vDEBUG == "true"){
		std::cout << "vHeap.vHeap	creo un vHeap de : "<<pSize<<" bytes"<<"\n";
	}
	this->_overweight= pOverweight;
	this->_tamanoMemoriaPaginadaUsada = 0;
	this->_tamanovHeap = pSize;
	this->_encoder = new Encoder();
	this->_ptrInicioMemoria = calloc(1,pSize);
	this->_ptrUltimaMemoriaLibre = _ptrInicioMemoria;
	this->_tablaMetadatos = xTable::getInstance();
	this->_estaEnZonaCritica = 0;
	if(Constants::vGUI == "true"){
		_encoder->connectToMemoryViewer();
		_encoder->sendMessage("xStart",pSize,8);
	}
};

/**
 * Destructor de la clase
 */
vHeap::~vHeap(){
	_ptrUltimaMemoriaLibre = 0;
	_ptrInicioMemoria=0;
	_tablaMetadatos->getList()->vaciar();
	_estaEnZonaCritica = false;
	_tamanoMemoriaPaginadaUsada =0;
	_overweight = 0;
	_tamanovHeap =0;
};

/**
 * Metodo para cumplir con singletone
 * @return retorna la unica instancia de este objeto
 */
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

/**
 * Libera toda la memoria dentro del manejador de memoria
 */
void vHeap::vFreeAll(){
	while(_estaEnZonaCritica){			// en caso de que otro hilo esta tratando el vHeap
		usleep(Constants::medioDeSegundoMili);
	}
	_estaEnZonaCritica = true;

	char* tmpPtr = (char*)_ptrInicioMemoria;
	for(int i=0; i<=_tamanovHeap;i++){ *(tmpPtr+i)=0; }
	_tablaMetadatos->getList()->vaciar();

	fstream myfile;
	myfile.open ("vHeap.bin", ios::out | ios::app | ios::trunc);
	myfile.seekg(0);
	myfile.write("0",_tamanoMemoriaPaginadaUsada);
    myfile.close();
    _tamanoMemoriaPaginadaUsada=0;

	if (Constants::vDEBUG == "true")
	{
		cout<<"vHeap.vFreeAll 	vacie el vHeap por completo \n";
	}
	_estaEnZonaCritica = false;
};

/**
 * Escribe la memoria que tenga en un archivo .txt
 */
void vHeap::dumpMemory(){
	while(_estaEnZonaCritica)
	{
		//usleep(medioDeSegundoMili);
	}
	_estaEnZonaCritica = true;
	stringstream stream;
	int numero = _contador;
	char palabra = (char)numero;
	fstream dump;

	dump.open ("dump.bin", ios::out | ios::app | ios::binary);

	if(dump.is_open()){
		for(vNode<xEntry*>* i = _tablaMetadatos->getList()->getHead(); i !=0 ; i = i->getNext())
		{
			dump.write((char*)(_ptrInicioMemoria+i->getData()->getOffset()),i->getData()->getSize());
		}
		_contador=_contador+1;
	}
	else{
		cout<<"Error al abrir el archivo vHeap.bin \n";
	}

	if(Constants::vDEBUG=="true"){
		cout<<"vHeap.dumpMemory() 	DUMP de memoria \n";
	}
	_estaEnZonaCritica = false;
};

/**
 * Desfragmentador de memoria
 */
void vHeap::desfragmentar()
{
	while(_estaEnZonaCritica)
	{
		//usleep(medioDeSegundoMili);
	}
	_estaEnZonaCritica = true;
	_estaEnZonaCritica = false;
	int contador=0;
	for(vNode<xEntry*>* i = _tablaMetadatos->getList()->getHead(); i !=0 ; i = i->getNext())
		{
		void* posiciones=_ptrInicioMemoria;
		int dato=i->getData()->getOffset();
		if(dato!=contador) {
			i->getData()->setOffset(contador);
			memmove(posiciones+contador,posiciones+dato,i->getData()->getSize());
			contador=contador+i->getData()->getSize();
		}
		else
		{
			contador=contador+i->getData()->getSize();
		}
		}
	char* temp =(char*)(_ptrInicioMemoria+contador);

	for(int i=contador; i <_tamanovHeap ; i++)				//colocar la memoria en ceros
	{
		*(temp+i) = 0;
	}
};

/**
 * Metodo control del manejador de memoria
 * LLama a el colector de basura, desfragmentador y vaciar la memoria
 */
void vHeap::control()			//hilo para metodo de control
{
	while(_estaEnZonaCritica){			// en caso de que otro hilo esta tratando el vHeap
		//usleep(medioDeSegundoMili);
	}							//cada metodo siguiente tiene zonas criticas individuales
	this->garbageCollector();
	this->desfragmentar();
	this->dumpMemory();
}


/**
 * Cuando se le solicita memoria al manejador de codigo se hacer por este metodo
 * @param pSize tamaño deseado
 * @param pType tipo del objeto a almacenar
 * @return retorna un vRef objeto que abstrae el puntero
 */
vRef* vHeap::vMalloc(int pSize, std::string pType)
{

	while(_estaEnZonaCritica){				//esperar hasta que se libere de zona critica
		usleep(Constants::medioDeSegundoMili);
		//sleep(1);
	}
	this->_estaEnZonaCritica = true;
	long ptrInicioDecimal = reinterpret_cast<long>(_ptrInicioMemoria);
	long ptrUltimaPosicioLibreDecimal = reinterpret_cast<long>(_ptrUltimaMemoriaLibre);
	int memLibre = _tamanovHeap-(ptrUltimaPosicioLibreDecimal-ptrInicioDecimal);

	if(Constants::vDEBUG == "true"){
		std:: cout<< "vHeap.vMalloc	llamada a vMaloc por "<<pSize<<" bytes" <<"\n";
		cout<<"vHeap.vMalloc	ptr Inicio de memoria :"<<ptrInicioDecimal<<"\n";
		cout<<"vHeap.vMalloc	ptr Fin de memoria :"<<ptrUltimaPosicioLibreDecimal<<"\n";
		cout<<"vHeap.vMalloc	"<< memLibre	<<" bytes de memoria libre  \n";

		cout<<"ingreso: "<<""<<"dato ingresado, leido de memoria: "<<*(int*)(_ptrUltimaMemoriaLibre-4)<<"\n";

	}

	if(memLibre >= pSize)
	{
		if(Constants::vDEBUG == "true"){
			cout <<"vHeap.vMalloc	Si hay espacio suficiente para un "<<pType<<"\n";
			cout<< "\n";

		}
		int id =_tablaMetadatos->getInstance()->addEntry(pSize, ptrUltimaPosicioLibreDecimal-ptrInicioDecimal,pType);
		vRef* referencia = new vRef(id);

		if(Constants::vGUI=="true"){
			int pStart = (ptrUltimaPosicioLibreDecimal-ptrInicioDecimal)/8;
			int pEnd = (pStart) + pSize/8;
			cout <<"Valores: "<<pStart<<"  "<<pEnd << endl;
			_encoder->sendMessage("true",pStart,pEnd);
		}

		this->_ptrUltimaMemoriaLibre = _ptrUltimaMemoriaLibre+pSize;

		this->_estaEnZonaCritica = false;

		return referencia;

	}else{	//no cabe el dato, ahora tratemos de paginar.
		if(Constants::vDEBUG == "true")
		{
			cout<< "Los "<<pSize<<" bytes solicitados no caben en: "<<_tamanovHeap<< ". Hay que paginar\n";
		}
		this->_estaEnZonaCritica = false;
		if(paginar(pSize))				//tratamos de paginar un tamaño mayor al pedido en vMalloc
		{
			if(Constants::vDEBUG =="true")
			{
				cout<<"vHeap.vMalloc 	paginamos con exito\n";
			}
			this->desfragmentar();		//para asegurarnos que quepa
			long d = reinterpret_cast<long>(_ptrUltimaMemoriaLibre);
			int id =_tablaMetadatos->addEntry(pSize, d-ptrInicioDecimal,pType);
			vRef* referencia = new vRef(id);
			this->_ptrUltimaMemoriaLibre = _ptrUltimaMemoriaLibre+pSize;
			this->_estaEnZonaCritica = false;
			return referencia;
		}
		else							// el objeto no cabe en ningun lugar
			if(Constants::vDEBUG=="true")
				cout<<"vHeap.vMalloc() 	No se logro la paginacion \n";
	}
};

/**
 * Cuando no hay suficiente memoria tratamos de escribir algunos objetos en un archivo .bin en binario
 * con tal de liberar espacio para otros objetos
 * @param pSize tamaño necesario para realizar la paginacion
 * @return
 */
bool vHeap::paginar(int pSize)
{
	if((_tamanovHeap*_overweight)-_tamanoMemoriaPaginadaUsada-Constants::MAX_SIZE_OF_ANY_OBJECT < pSize)
	{
		//el tamaño que se requiere escribir en memoria no cabe. No hay paginacion disponible
		//menos MAX_SIZE_OF_ANY_OBJECT ya que siempre queremos el tamaño maximo disponible para
		//guardar el objeto mas grande en memoria en caso de que debamos guardar uno para traer otro
		if(Constants::vDEBUG=="true"){
			cout<<"El tamaño de datos que se desea paginar es mayor al disponible para la paginacion\n";
		}
		return false;
	}
	else			//si hay espacio suficiente solo hay que hacer paginacion
	{
		//seleccionar un grupo de objetos que juntos sean igual o mas grandes que el tamaño requerido
		//pero que no sobre pasen el tamaño de la paginacion posible

		vNode<xEntry*>* nodetmp = xTable::getInstance()->getList()->getHead();

		fstream archivoBinario;
		archivoBinario.open ("vHeap.bin", ios::out | ios::app | ios::binary);

		if(archivoBinario.is_open()){
			for(int it = 0; it < pSize; it = it+0){	// en este punto tenemos la lista de seleccionados para paginar.
				if(nodetmp == 0){					// si nodetmp es nulo, no hay suficientes para paginar
					if(Constants::vDEBUG == "true"){
						cout<<"no hay datos libres suficientes para paginar lo solicitado\n";
					}
					return false; 					//no hay datos suficientes para paginar y guardar la memoria deseada;
				}
				xEntry* tmpXentry = nodetmp->getData();

				stringstream convertir;			//convertir los atributos del xentre en binario
				convertir << tmpXentry->getID();
				string pID = convertir.str();
				stringstream pconvertir;
				pconvertir << tmpXentry->getOffset();
				string pOffset = pconvertir.str();

				cout<<_ptrInicioMemoria<<"\n";
				cout<<_ptrInicioMemoria+tmpXentry->getSize()<<"\n";

				std::string pData = "#"+ tmpXentry->getType()+"#"+pID+"#"+pOffset+"#"+"#";
				if(Constants::vDEBUG=="true"){
					cout<<"vHeap.Paginar	Pagino un dato de la forma: "<<pData<<"  ( # type # ID # Offset # Data #)\n";
				}
				archivoBinario.write((char*)(&pData),sizeof(string));

				_tamanoMemoriaPaginadaUsada = _tamanoMemoriaPaginadaUsada+(nodetmp->getData()->getSize());
				xTable::getInstance()->getList()->deleteData(nodetmp->getData());
				nodetmp=nodetmp->getNext();

				it = it+nodetmp->getData()->getSize();

				string b;
//				string a = archivoBinario.read(b,sizeof(string));
				cout<<"leyendo : "<<b<<" \n";
			};

			archivoBinario.close();
			return true;
		}
		else{
			if(Constants::vDEBUG =="true"){
				cout<<"Error al abrir el archivo vHeap.bin \n";
			}
		}
		return false;
	}
}

/**
 * controlador de referencias
 * si algun objeto no tiene alguna
 * este es inaccesible
 * por lo tanto se descarta
 */
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
			vFree(iterador->getData());
		}
	}
	_estaEnZonaCritica = false;
};

/**
 * Este metodo privado funciona dentro de la clase
 * @param pEntry recibe este argumento a eliminar
 */
void vHeap::vFree(xEntry* pEntry)
{
	char* temp =(char*)( _ptrInicioMemoria + (pEntry->getOffset()));

	for(int i=0; i < pEntry->getSize(); i++)				//colocar la memoria en ceros
	{
		*(temp+i) = 0;
	}
	_tablaMetadatos->getList()->deleteData(pEntry);

	int pStart = pEntry->getOffset()/8;
	int pEnd = (pEntry->getOffset()+pEntry->getSize())/8;
	_encoder->sendMessage("false",pStart,pEnd);


	if(Constants::vDEBUG == "true")
	{
		cout<<"Elemento eliminado de la xTable \n";
	}

}

/**
 * Metodo publico que recibe un Puntero vRef
 * lo asocia con un xEntry y utiliza el metodo privado  vFreef(xEntry*)
 * @param pRef
 */
void vHeap::vFree(vRef* pRef)
{
	bool borre = false;
	for(vNode<xEntry*>* i = _tablaMetadatos->getList()->getHead(); i !=0 ; i = i->getNext())
	{
		if (i->getData()->getID()==pRef->getID())
		{
			borre = true;
			return vFree(i->getData());
		}
	}
	if (Constants::vDEBUG=="true")
	{
		if(borre)
			cout<<"vHeap.vFree	Borre un dato con ID: "<<pRef->getID()<<"\n";
		else
			cout<<"vHeap.vFree	no pude borrar un dato con ID: "<<pRef->getID()<<"\n";
	}
	vNode<xEntry*>* tempEn = _tablaMetadatos->getList()->getHead();
	for (int i = 0; i < pRef->getID(); i++){
		tempEn->getNext();
	}
	xEntry* pEntry = tempEn->getData();

	int pStart = pEntry->getOffset()/8;
	int pEnd = (pEntry->getOffset()+pEntry->getSize())/8;
	_encoder->sendMessage("false",pStart,pEnd);
}




