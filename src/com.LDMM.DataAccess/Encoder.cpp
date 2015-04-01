/*
 * Encoder.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: fabian
 */

#include "Encoder.h"


Encoder::Encoder() { socket = new SocketCliente(); }

Encoder::~Encoder() {}

bool Encoder::connectToMemoryViewer(){
	const char* pIP = Constants::TARGET_IP.c_str();
	int pPORT = Constants::TARGET_PORT;
	socket->connect(pIP,pPORT);
	return true;
}

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
