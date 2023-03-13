

#include <string>
#include "Interface.h"
#include "Data.h"
#include "Stack.h"
#include "ErrorController.h"

static std::string options[] = {
	"0 - push to stack",			 //INTERF_PUSH
	"1 - pop from stack",			 //INTERF_POP
	"2 - clear stack",		 //INTERF_CLEAR
	"3 - find in stack", //INTERF_FIND_LASTNAME
	"4 - list stack",	 //INTERF_LIST
	"5 - save to file",  //INTERF_SAVE
	"6 - read from file",  //INTERF_SAVE
	"7 - finish"         //INTERF_STOP
}; 

#ifdef DEBUG
void addDEBUG() {
	int num = 10000; 
	for (int i = 0; i < num; i++) {
		void* pData = DataPush((char*)"test", 1, (KIERUNKI)1);
		if (!StackPush(pData))
			ErrorLog({ "StackPush error", 1 });
	}
	printf_s("Added %d to stack\n", num);
}

void testPopDEBUG() {
	int num = 10000;
	for (int i = 0; i < num; i++) {
		void* pData = DataPush((char*)"test", 1, (KIERUNKI)1);
		if (!StackPush(pData))
			ErrorLog({ "StackPush error", 1 });
	}
	printf_s("Added %d to stack\n", num);
	for (int i = 0; i < num; i++) {
		pop();
	}
	printf_s("Popped %d from stack\n", num);
}

void testPopOnlyDEBUG() {
	int num = 10000;
	for (int i = 0; i < num; i++) {
		pop();
	}
	printf_s("Popped %d from stack\n", num);
}
#endif //DEBUG




void menu() {
	size_t it; 
	for (auto it : options)
		printf_s("%s\n", it.c_str());
}

#pragma warning (disable : 4996)
void push() {
	size_t year;
	KIERUNKI major;
	char *lastname = (char *)malloc(50 * sizeof(char));

	printf_s("nazwisko, rok, kierunek(0-4)\n");
	scanf("%s", lastname);
	scanf_s("%zd", &year);
	scanf_s("%d", &major);

	void* pData = DataPush(lastname, year, major);
	if (!StackPush(pData))
		ErrorLog({ "StackPush error", 1 });

}

void pop() {
	STACK_ELEM tmp = StackPop();

	if (tmp.pData) {
		DataPrint(tmp.pData);
		DataFree(tmp.pData);
	}
}


#pragma warning (disable : 4996)
void find() {
	char param[50], str[50];

	printf_s("Which parameter to find? \n");
	scanf_s("%s", param, 50);

	printf_s("Query %s:\n", param);
	scanf_s("%s", str, 50);

	param[49] = '\0';
	str[49] = '\0';

	MY_STUDENT searchData;
	memset(&searchData, 0, sizeof(MY_STUDENT));

	if (strcmp(param, StudentParams[LASTNAME]) == 0) {
		searchData.nazwisko = str;
	}else if (strcmp(param, StudentParams[YEAR]) == 0) {
		searchData.rok = std::atoi(str);
	}else if (strcmp(param, StudentParams[MAJOR]) == 0) {
		searchData.kierunek = (KIERUNKI)KierunkiStringToEnum(str);
	}
	else {
		ErrorLog({ "Wrong param for query", 1 });
	}
	

	void* pData = StackSearch(&searchData, DataSearch, param);

	if (pData) {
		printf_s("\n============*============\nFound: \n");
		DataPrint(pData);
	}
	else {
		printf_s("NOT found. \n");
	}

}

void saveToFile()
{
	if (!StackSave())
		printf("IO error during write to file\n");
	else
		printf("Stack saved to binary file.");

}

void readFromFile() {
	if (!StackRead())
		printf("IO error during read to file\n");
	else
		printf("Stack read from binary file.");
}

void list() {
	StackList( DataPrint );
}

void clear() {
	StackFree();
}

