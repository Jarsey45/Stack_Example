// Queue.cpp : Defines the entry point for the console application.
//



#include <stdio.h>
#include <tchar.h>
#include "Interface.h"
#include "Stack.h"
#include "Data.h"


#pragma warning (disable : 4996)

int _tmain(int argc, _TCHAR* argv[])
{

	StackInit(DataFree);


	int op = 0;
	while (1)
	{
		menu();
		scanf_s("%d", &op);
		switch (op)
		{
			case INTERF_PUSH: push();
				break;
			case INTERF_POP: pop();
				break;
			case INTERF_CLEAR: clear();
				break;
			case INTERF_FIND_LASTNAME: find();
				break;
			case INTERF_LIST: list();
				break;
			case INTERF_SAVE: saveToFile();
				break;
			case INTERF_READ: readFromFile();
				break;
#ifdef DEBUG
			case 200: addDEBUG(); break;
			case 201: testPopDEBUG(); break;
			case 202: testPopOnlyDEBUG(); break;
#endif //DEBUG
			case INTERF_STOP: clear();
				return 0;
			default:
				printf("Nie istnieje taka operacja\n");
		};
	};

	return 0;
}

