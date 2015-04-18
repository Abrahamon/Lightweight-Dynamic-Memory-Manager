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
	int createBool(bool pData);
	int createString(std::string pData);
	int createChar(const char* pData);
	int createLong(long pData);
	bool checkInput(std::string pValue);
	bool checkBool(std::string pValue);
	void remove(int ref);
};

#endif /* SRC_COM_LDMM_MEMORYRESOURCES_INPUTHANDLER_H_ */
