/*
 * InputHandler.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: fabian
 */

#include "InputHandler.h"
#include "../com.LDMM.MemoryManager/vHeap.h"
#include "../com.LDMM.vObjects/vBool.h"
#include "../com.LDMM.vObjects/vChar.h"
#include "../com.LDMM.vObjects/vFloat.h"
#include "../com.LDMM.vObjects/vInt.h"
#include "../com.LDMM.vObjects/vLong.h"
#include "../com.LDMM.vObjects/vString.h"
#include "../Constants.h"
#include <string>
#include <stdlib.h>

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::start(){
	Constants* constants;
	constants->getInstance();

	vHeap* y = vHeap::getInstancia();
	std::cout << "Memory Manager Initialized" << std::endl;
}

void InputHandler::handleEvents(){
	while(true){
		std::cout << ">>> ";

		std::string pCommand = "";
		std::string pType = "";
		std::string pValue = "";

		std::cin >> pCommand;
		//continue
		std::cout << "Enter vType: ";
		std::cin >> pType;
		if(pType == ""){
			continue;
		}
		std::cout << "Enter Value: ";
		std::cin >> pValue;

		manageData(pCommand,pType,pValue);
	}
}

void InputHandler::manageData(std::string pCommand, std::string pType, std::string pValue){
	if(pCommand == "create"){
		if(pType == "vInt"){
			int value = atoi(pValue.c_str());
			int ref = createInteger(value);
			std::cout<< "Object created with ID: " << ref << std::endl;
		}
		else if(pType == "vFloat"){
			float value = atof(pValue.c_str());
			int ref = createFloat(value);
			std::cout<< "Object created with ID: " << ref << std::endl;
		}
	}
	else if(pCommand == "remove"){

	}
}

int InputHandler::createInteger(const int &pData){
	vInt* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vInt();
	vRef* referencia = *num = pData;

	return referencia->getID();
}

int InputHandler::createFloat(const float &pData){
	vFloat* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vFloat();
	vRef* referencia = *num = pData;

	return referencia->getID();
}

void InputHandler::remove(int ref){
	vRef* temp = new vRef();
	temp->setID(ref);
	vHeap::getInstancia()->vFree(temp);
	free(temp);
}

