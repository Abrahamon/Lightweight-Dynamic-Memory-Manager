/*
 * xEntry.h
 *
 *  Created on: Mar 16, 2015
 *      Author: fabian
 */

#ifndef SRC_XENTRY_H_
#define SRC_XENTRY_H_
#include <string>

using namespace std;

class xEntry {
private:
	int _ID;
	int _Size;
	void* _Offset;
	int _RefCounter;
	bool _UseFlag;
	string _Type;


public:
	xEntry(int pID, int pSize, void* pOffset, string pType);
	virtual ~xEntry();

	int getMemPos();

	int getSize();
	void* getOffset();
	int getReferenceCounter();
	bool isBeingUsed();
	string getType();

	void IncreaseRef();
	void DecreaseRef();

	void setSize(int pSize);
	void setOffset(void* pOffset);
	void setUseFlag(bool pFlag);
	void setType(string pType);
};

#endif /* SRC_XENTRY_H_ */
