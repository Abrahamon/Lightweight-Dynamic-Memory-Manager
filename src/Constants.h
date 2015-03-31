/*
 * Constants.h
 *
 *  Created on: Mar 17, 2015
 *      Author: fabian
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
//#include "../src/com.LDMM.DataAccess/XMLReader.h"
#include <string>
<<<<<<< HEAD
using namespace std;

//class Constants{
	//static XMLReader *reader = new XMLReader();

//const std::string SIZE = reader->getParameter("Size") ;//200; //size for the vHeap
const int SIZE = 11000;
const int OVERWEIGHT = 0;
static const int DUMP_FRECUENCY= 0;
const int DUMP_PATH= 0;
const int vDEBUG= true;
const int vDEBUG_PATH= 0;
const int GC_FRECUENCY= 0;


//Constants VObjects
const std::string TYPE_INT = "Int";
const string TYPE_STRING = "String";
const std::string TYPE_CHAR = "Char";
const std::string TYPE_LONG = "Long";
const std::string TYPE_FLOAT = "Float";
const std::string TYPE_ARRAY = "Array";
const std::string TYPE_BOOL = "Bool";


const int cuartoDeSegundoMili =250000;
const int medioDeSegundoMili =500000;
const int SegundoMili =1000000;

=======
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
>>>>>>> afb3e631944bdaab3e814f023e11781d6956b503
#endif /* SRC_CONSTANTS_H_ */
