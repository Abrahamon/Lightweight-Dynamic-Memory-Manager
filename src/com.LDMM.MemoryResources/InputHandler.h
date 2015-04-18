/*
 * InputHandler.h
 *
 *  Created on: Apr 17, 2015
 *      Author: fabian
 */

#ifndef SRC_COM_LDMM_MEMORYRESOURCES_INPUTHANDLER_H_
#define SRC_COM_LDMM_MEMORYRESOURCES_INPUTHANDLER_H_
#include <string>

class InputHandler {
public:
	InputHandler();
	virtual ~InputHandler();

	void start();
	void handleEvents();
	void manageData(std::string pCommand, std::string pType, std::string pValue);

	int createInteger(const int &pData);
	int createFloat(const float &pData);
	void remove(int ref);
};

#endif /* SRC_COM_LDMM_MEMORYRESOURCES_INPUTHANDLER_H_ */
