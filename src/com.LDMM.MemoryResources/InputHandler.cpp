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

/*
 * Método que inicializa el InputHandler, permite
 * obtener por primera vez las instancias de la
 * clase constants y del vHeap.
 */
void InputHandler::start(){
	Constants* constants;
	constants->getInstance();

	vHeap* y = vHeap::getInstancia();
	std::cout << "Memory Manager Initialized" << std::endl;
}

/*
 * Método encargado de obtener los inputs del usuario
 * ya sea para crear, borrar objetos o desfragmentar
 */
void InputHandler::handleEvents(){
	while(true){
		std::cout << ">>> ";

		std::string pCommand = "";
		std::string pNumberOfObj= "";
		std::string pType = "";
		std::string pValue = "";
		int pNUMBER;

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

			std::cout << "Enter number of vObjects: ";
			std::cin >> pNumberOfObj;
			if(checkInput(pNumberOfObj)== false){
				std::cout << "Bad input" << std::endl;
				return;
			}
			if(pNumberOfObj == "1"){
				pNUMBER = 1;
				std::cout << "Enter Value: ";
				std::cin >> pValue;
			}
			else{
				pNUMBER = atoi(pNumberOfObj.c_str());
			}



		}
		else if(pCommand == "defrag"){
			manageData(pCommand,pType,pValue,0);
			continue;
		}
		else{
			std::cout << "Enter ID: ";
			std::cin >> pValue;
		}


		manageData(pCommand,pType,pValue,pNUMBER);
	}
}

/*
 * Método encargado de ejecutar la creación de objetos
 * interpretando las entradas del usuario.
 *
 * @param pCommand: comando inicial debug,create o remove
 * @param pType: tipo de dato a crear
 * @param pValue: valor del dato a crear o id para eliminar
 */
void InputHandler::manageData(std::string pCommand, std::string pType, std::string pValue,int number){
	if(pCommand == "create"){
		if(pType == "vInt"){
			if(checkInput(pValue)== false){
				std::cout << "Bad input" << std::endl;
				return;
			}
			int value = atoi(pValue.c_str());
			createInteger(value,number);

		}
		else if(pType == "vFloat"){
			float value = atof(pValue.c_str());
			createFloat(value,number);
		}
		else if(pType == "vBool"){
			bool pBool;
			if(checkBool(pValue)==false){
				std::cout << "Bad input" << std::endl;
				return;
			}
			if(pValue == "true") pBool = true;
			else if(pValue=="false") pBool = false;
			int ref = createBool(pBool, number);
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

/*
 * Método para la creacion de un Int
 */
int InputHandler::createInteger(const int &pData, int number){
	for(int i = 0; i < number; i++){
		vInt* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vInt();
		vRef* referencia = *num = i;
		std::cout<< "Object created with ID: " << referencia->getID() << std::endl;
		usleep(200000);
	}
	return 0;
}

/*
 * Método para la creacion de un Float
 */
int InputHandler::createFloat(const float &pData,int number){
	for(int i = 0; i < number; i++){
		vFloat* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vFloat();
		vRef* referencia = *num = pData;
		std::cout<< "Object created with ID: " << referencia->getID() << std::endl;
	}
	return 0;
}

/*
 * Método para la creacion de un bool
 */
int InputHandler::createBool(bool pData,int number){
	for(int i = 0; i < number; i++){
		vBool* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vBool();

		vRef* referencia;
		if(i % 2 == 0){
			referencia = *num = true;
		}
		else{
			referencia = *num = false;
		}
		std::cout<< "Object created with ID: " << referencia->getID() << std::endl;
	}
	return 0;
}

/*
 * Método para la creacion de String
 */
int InputHandler::createString(std::string pData){
	vString* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vString();
	vRef* referencia = *num = pData;

	return referencia->getID();
}

/*
 * Método para la creacion de un char
 */
int InputHandler::createChar(const char* pData){
	vChar* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vChar();
	vRef* referencia = *num = pData;

	return referencia->getID();
}

/*
 * Método para crear un long
 */
int InputHandler::createLong(long pData){
	vLong* num = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vLong();
	vRef* referencia = *num = pData;

	return referencia->getID();
}

/*
 * Método que permite verificar el input realizado
 * por el usuario. Ya que permite verificar si lo
 * ingresado corresponde unicamente a numeros de la
 * forma correcta para crear un int.
 *
 * @param pValue: input
 */
bool InputHandler::checkInput(std::string pValue){
	for (int i = 0; i < pValue.length(); i++){
		if(!isdigit(pValue[i])){
			return false;
		}
	}
	return true;
}

/*
 * Método que permite verificar el input realizado
 * por el usuario para verificar que al ingresar un
 * valor de verdad para una variable bool tenga un valor
 * adecuado.
 *
 * @param pValue: input
 */
bool InputHandler::checkBool(std::string pValue){

	if(pValue != "false" && pValue != "true"){
		return false;
	}
	return true;
}

void InputHandler::remove(int ref){
	vRef* temp = new vRef();
	temp->setID(ref);
	vHeap::getInstancia()->vFree(temp);
	free(temp);
}

