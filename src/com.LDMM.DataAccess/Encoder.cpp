/*
 * Encoder.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: fabian
 */

#include "Encoder.h"


Encoder::Encoder() { socket = new SocketCliente(); }

Encoder::~Encoder() {}

/*
 * Método que permite conectar el Memory Manager con el
 * monitor de memoria, pero sin inicializarlo, es decir,
 * solo establece la conexión
 */
bool Encoder::connectToMemoryViewer(){
	const char* pIP = Constants::TARGET_IP.c_str();
	int pPORT = Constants::TARGET_PORT;
	socket->connect(pIP,pPORT);
	return true;
}

/*
 * Método que permite el envío de mensajes hacia el monitor
 * de memoria. Ya sea para inicializarlo mediante ("xStart",vHeapSize,MemDivision),
 * o para el envío de mensajes de actualización de las posiciones de memoria.
 *
 * @param pSet: comando inicial del mensaje puede tomar valores (xStart,true,false)
 * @param pRangeStart: incio del bloque de memoria a editar
 * @param pRangeEnd: fin del bloque de memoria a editar
 */
bool Encoder::sendMessage(std::string pSet,int pRangeStart, int pRangeEnd){
	if(pSet.compare("true") !=0 && pSet.compare("false") !=0 && pSet.compare("xStart")){
		std::cout << "*Encoder* Check entry -> ";
		std::cout << pSet;
		std::cout << " <- is not a valid parameter"<<std::endl;
		return false;
	}
	else{
		stringstream start_output;
		stringstream end_output;
		start_output<<(pRangeStart);
		end_output<<(pRangeEnd);

		std::string pStart = start_output.str();
		std::string pEnd = end_output.str();

		std::string output = pSet + "#" + pStart + "#" + pEnd;
		socket->sendMessage(output.c_str());
		return true;
	}


}
