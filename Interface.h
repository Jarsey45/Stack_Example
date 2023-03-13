#pragma once
#include "debug.h"

enum INTERFACE_ENUM
{
	INTERF_PUSH,
	INTERF_POP,
	INTERF_CLEAR,
	INTERF_FIND_LASTNAME,
	INTERF_LIST,
	INTERF_SAVE,
	INTERF_READ,
	INTERF_STOP,
	INTERF_TOT
};

void push();
void pop();
void clear();
void menu();
void list();
void find();
void saveToFile();
void readFromFile();

#ifdef DEBUG
	void addDEBUG();
	void testPopDEBUG();
	void testPopOnlyDEBUG();
#endif //DEBUG
