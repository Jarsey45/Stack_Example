#pragma once

#include <stdio.h>

typedef bool (*IO_Object)(void** pdat, FILE* pf);
typedef void (*FreeData)(void* pData);
typedef void (*Print)(void* pData);
typedef int (CompareData)(void* pcurData, void* pSearchData, char* query);

struct STACK_ELEM {
	void * pData;
	STACK_ELEM* next;
	IO_Object pSave;
	IO_Object pRead;
	static int no_items;
};


void StackInit(FreeData pFreeData);
void StackFree();
STACK_ELEM* StackPeek();
STACK_ELEM* StackPush(void* pData);
STACK_ELEM StackPop();
void StackList(Print pPrintFunction);
void* StackSearch(void* pSearchData, CompareData pCompareFunction, char* query);
bool StackSave();
bool StackRead();
