/*
 * Constants.h
 *
 *  Created on: Mar 17, 2015
 *      Author: fabian
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
#include "../src/com.LDMM.DataAccess/XMLReader.h"
#include <string>
#include <stdlib.h>

class Constants{
public:
	static Constants* _Constants;
	static int SIZE;
	static int OVERWEIGHT;
	static int DUMP_FRECUENCY;
	static std::string DUMP_PATH;
	static std::string vDEBUG;
	static std::string vDEBUG_PATH;
	static int GC_FRECUENCY;
	static int cuartoDeSegundoMili;
	static int medioDeSegundoMili;
	static int SegundoMili;

	//Constants VObjects
	static std::string TYPE_INT;
	static std::string TYPE_STRING;
	static std::string TYPE_CHAR;
	static std::string TYPE_LONG;
	static std::string TYPE_FLOAT;
	static std::string TYPE_ARRAY;
	static std::string TYPE_BOOL;

	Constants* getInstance();

private:
	Constants();
};
#endif /* SRC_CONSTANTS_H_ */
