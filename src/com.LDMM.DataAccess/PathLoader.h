/*
 * PathLoader.h
 *
 *  Created on: Mar 30, 2015
 *      Author: fabian
 */

#ifndef SRC_COM_LDMM_DATAACCESS_PATHLOADER_H_
#define SRC_COM_LDMM_DATAACCESS_PATHLOADER_H_
#include <string.h>

class PathLoader{
private:
	long path_max;
	size_t size;
	char* buf;
	char* ptr;
	char command[8];
public:
	PathLoader();
	virtual ~PathLoader();

	char* getProgramPath(){

		path_max = pathconf(".", _PC_PATH_MAX);
		if (path_max == -1)
			size = 1024;
		else if (path_max > 10240)
			size = 10240;
		else
			size = path_max;
		for (buf = ptr = 0; ptr == 0; size *= 2){
			ptr = getcwd(buf, size);
		}
		free (buf);

		strcpy(command, "python ");
		char file_name[14];
		strcpy(file_name, "/src/RRold.py");
		strcat(ptr, file_name);
		strcat(command,ptr);

		return command;
	}
};



#endif /* SRC_COM_LDMM_DATAACCESS_PATHLOADER_H_ */
