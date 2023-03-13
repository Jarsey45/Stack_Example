#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>
#include "ErrorController.h"
#include "Data.h"

//deklaracje
void Exit(FILE* pFile, __int64* file_desc);

static STACK_ELEM* first = nullptr;//top 
static STACK_ELEM* last = nullptr;//last
int STACK_ELEM::no_items = 0;
const char *MyFileName = "my_data.bin";
FreeData pFreeFun;


bool StackEmpty() {
	if (first == nullptr) return true;
	return false;
}

void StackInit(FreeData pFreeData)
{
	first = nullptr;
	last = nullptr;
	pFreeFun = pFreeData;
}

void StackFree()
{
	//definiujemy pierwszy element stosu, oraz pomocniczy wskaznik
	STACK_ELEM* p = first, *temp = nullptr;

	//jezeli p nie jest nullptr, wtedy nasz stos nie jest pusty
	while (p) {
		(*pFreeFun)(p->pData);
		temp = p;
		p = p->next;
		free(temp);
	}
	first->no_items = 0;
	first = nullptr;
	last = nullptr;
}

STACK_ELEM* StackPeek()
{
	return first;
}

STACK_ELEM * StackPush(void* pData)
{
	STACK_ELEM* newElem = (STACK_ELEM*)malloc(sizeof(STACK_ELEM));
	STACK_ELEM* p = first;
	
	//if newElem is nullptr, error
	if (!newElem) {
		ErrorLog({"StackPush error\n", 1});
		return nullptr;
	}

	newElem->next = nullptr;
	newElem->pData = pData;
	newElem->pSave = DataSave;

	if (StackEmpty()) {
		last = first = newElem;
		return newElem;
	}

	//if stack is not empty;
	newElem->next = first;

	
	first = newElem;
	first->no_items++;

	return newElem;

}

STACK_ELEM StackPop()
{
	STACK_ELEM del;

	if ( first == nullptr ) {
		del.next = nullptr;
		del.pData = nullptr;
		ErrorLog({ "Stack is already empty\n", 1 });
		return del;
	}

	STACK_ELEM* prev = first->next;

	del.pData = first->pData;
	del.next = prev;

	free(first);
	
	if (prev == nullptr) {
		first = last = nullptr;
		return del;
	} 

	first = prev;
	first->no_items--;

	return del;
}

void StackList(Print pPrintFunction) {

	if (StackEmpty()) {
		printf_s("Stack is empty\n");
		return;
	}

	STACK_ELEM* p = first;

	//jezeli p nie jest nullptr, wtedy nasz stos nie jest pusty
	//wyswietl p->pData
	while (p) {
		printf_s("=============*=============\n");
		(*pPrintFunction)(p->pData);
		p = p->next;
	}
	printf_s("=============*=============\n");
}

void* StackSearch(void* pSearchData, CompareData pCompareFunction, char* query)
{

	STACK_ELEM* p = first; 

	while (p) {
		if (!(*pCompareFunction)(p->pData, pSearchData, query)) p = p->next;
		else return p->pData;
	}

	return nullptr;
}

#pragma warning (disable : 4996)

bool StackSave() {

	unsigned int no_items = first->no_items + 1;
	size_t iterator = 0;

	STACK_ELEM* pCurr = first;
	if (!pCurr)
		Exit(NULL, NULL);

	__int64* file_desc = (__int64*)malloc((no_items) * sizeof(__int64));
	if (!file_desc)
		Exit(NULL, file_desc);

	FILE* pf;
	fopen_s(&pf ,MyFileName, "wb");
	if (!pf)
		Exit(pf, file_desc);

	if (fwrite(&no_items, sizeof(unsigned int), 1, pf) != 1)
		Exit(pf, file_desc);

	//rezerwuje miejsce dla file descriptora
	_fseeki64(pf, no_items * sizeof(__int64), SEEK_CUR);

	while (pCurr) {

		//aktualna pozycja wskaŸnika pliku
		file_desc[iterator] = (__int64)ftell(pf);
		
		//call save function of current object
		if (!(*pCurr->pSave)(&pCurr->pData, pf))
			Exit(pf, file_desc);

		pCurr = pCurr->next;
		iterator++;
	}

	file_desc[iterator] = _ftelli64(pf);

	//zmieniamy wskaznik na poczatek pliku
	_fseeki64(pf, sizeof(unsigned int), SEEK_SET);
	//zapisuje file_desc na pocztek pliku
	if (fwrite(file_desc, sizeof(__int64), no_items, pf) != no_items)
		Exit(pf, file_desc);


	//zwalnianie pamiêci
	if(pf)
		fclose(pf);
	pf = NULL;

	if (file_desc)
		free(file_desc); //TODO: NAPRAWIÆ 
	file_desc = NULL;

	return true;
}

bool StackRead() //TODO: dokonczyc odczyt
{
	size_t no_items;
	STACK_ELEM tmp;
	__int64* file_desc = NULL;
	memset((void*)&tmp, 0, sizeof(STACK_ELEM));

	FILE* pf;
	fopen_s(&pf, MyFileName, "rb");
	if (!pf)
		Exit(pf, file_desc);

	fclose(pf);

	//PrintArray(*arr);

	return true;
}


void Exit(FILE* pFile, __int64* file_desc) {
	if (pFile) // jezeli plik jest otwarty to go zamykam
		fclose(pFile);

	StackFree();

	if (file_desc) // jezeli deskryptor pliku istnieje to zwalniam pamiec
		free(file_desc);

	ErrorLog({ "Fatal error\n", 1 });
	system("pause");
	exit(1);

}

