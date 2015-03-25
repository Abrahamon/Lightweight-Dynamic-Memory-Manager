/*
 * Constants.h
 *
 *  Created on: Mar 17, 2015
 *      Author: fabian
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
#include <string>

const int SIZE = 200; //size for the vHeap
const int OVERWEIGHT = 0;
const int DUMP_FRECUENCY= 0;
const int DUMP_PATH= 0;
const int vDEBUG= true;
const int vDEBUG_PATH= 0;
const int GC_FRECUENCY= 0;


//Constants VObjects
const std::string TYPE_INT = "Int";
const std::string TYPE_STRING = "String";
const std::string TYPE_CHAR = "Char";
const std::string TYPE_LONG = "Long";
const std::string TYPE_FLOAT = "Float";
const std::string TYPE_ARRAY = "Array";
const std::string TYPE_BOOL = "Bool";


const int cuartoDeSegundoMili =250000;
const int medioDeSegundoMili =500000;
const int SegundoMili =1000000;


#endif /* SRC_CONSTANTS_H_ */
