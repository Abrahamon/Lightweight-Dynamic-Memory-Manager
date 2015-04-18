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
		if(pCommand != "create" && pCommand != "remove" && pCommand != "defrag"){
			std::cout << "Bad input" << std::endl;
			continue;
		}
		if(pCommand == "create"){
			std::cout << "Enter vType: ";
			std::cin >> pType;

			if(pType != "vChar" && pType != "vBool" && pType != "vFloat" &&
			   pType != "vInt"  && pType != "vLong" && pType != "vString"){
				std::cout << "Bad input" << std::endl;
				continue;
			}

			std::cout << "Enter Value: ";
			std::cin >> pValue;
		}
		else if(pCommand == "defrag"){
			manageData(pCommand,pType,pValue);
			continue;
		}
		else{
			std::cout << "Enter ID: ";
			std::cin >> pValue;
		}


		manageData(pCommand,pType,pValue);
	}
}

void InputHandler::manageData(std::string pCommand, std::string pType, std::string pValue){
	if(pCommand == "create"){
		if(pType == "vInt"){
			if(checkInput(pValue)== false){
				std::cout << "Bad input" << std::endl;
				return;
			}
			int value = atoi(pValue.c_str());
			int ref = createInteger(value);
			std::cout<< "Object created with ID: " << ref << std::endl;
		}
		else if(pType == "vFloat"){
			float value = atof(pValue.c_str());
			int ref = createFloat(value);
			std::cout<< "Object created with ID: " << ref << std::endl;
		}
		else if(pType == "vBool"){
			bool pBool;
			if(checkBool(pValue)==false){
				std::cout << "Bad input" << std::endl;
				return;
			}
			if(pValue == "true") pBool = true;
			else if(pValue=="false") pBool = false;
			int ref = createBool(pBool);
			std::cout<< "Object created with ID: " << ref << std::endl;
		}
		else if(pType == "vString"){
			int ref = createString(pValue);
			std::cout<< "Object created with ID: " << ref << std::endl;
		}
		else if(pType == "vChar"){
			int ref = createChar(pValue.c_str());
			std::cout<< "Object created with ID: " << ref << std::endl;
		}
		else if(pType == "vLong"){
			long pLong = atol(pValue.c_str());
			int ref = createLong(pLong);
			std::cout<< "Object created with ID: " << ref << std::endl;
		}
	}
	else if(pCommand == "remove"){
		int value = atoi(pValue.c_str());
		remove(value);
	}
	else if(pCommand == "defrag"){
		vHeap::getInstancia()->desfragmentar();
		std::cout<< "Memory defrag" <<std::endl;
		pCommand = "";
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

int InputHandler::createBool(bool pData){
	vBool* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vBool();
	vRef* referencia = *num = pData;

	return referencia->getID();
}

int InputHandler::createString(std::string pData){
	vString* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vString();
	vRef* referencia = *num = pData;

	return referencia->getID();
}

int InputHandler::createChar(const char* pData){
	vChar* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vChar();
	vRef* referencia = *num = pData;

	return referencia->getID();
}

int InputHandler::createLong(long pData){
	vLong* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vLong();
	vRef* referencia = *num = pData;

	return referencia->getID();
}

bool InputHandler::checkInput(std::string pValue){
	for (int i = 0; i < pValue.length(); i++){
		if(!isdigit(pValue[i])){
			return false;
		}
	}
	return true;
}

bool InputHandler::checkBool(std::string pValue){

	if(pValue != "false") return false;
	else if(pValue != "true") return false;
	return true;
}

void InputHandler::remove(int ref){
	vRef* temp = new vRef();
	temp->setID(ref);
	vHeap::getInstancia()->vFree(temp);
	free(temp);
}

