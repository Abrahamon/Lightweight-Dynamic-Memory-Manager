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


	static const int SIZE = 25;
	static const int OVERWEIGHT = 0;
	static const int DUMP_FRECUENCY= 0;
	static const int DUMP_PATH= 0;
	static const int vDEBUG= true;
	static const int vDEBUG_PATH= 0;
	static const int GC_FRECUENCY= 0;
	static const int cuartoDeSegundoMili =250000;
	static const int medioDeSegundoMili =500000;
	static const int SegundoMili =1000000;

	//Constants VObjects
	const std::string TYPE_INT = "Int";
	const std::string TYPE_STRING = "String";
	const std::string TYPE_CHAR = "Char";
	const std::string TYPE_LONG = "Long";
	const std::string TYPE_FLOAT = "Float";
	const std::string TYPE_ARRAY = "Array";
	const std::string TYPE_BOOL = "Bool";

#endif /* SRC_CONSTANTS_H_ */
