
#include <string>
#include "Data.h"
#include "ErrorController.h"


std::string Nazwy_Kierunkow[] = {
	"Informatyka",
	"Informatyka Niestacjonarna",
	"Architektura",
	"Angielski",
};

#pragma warning (disable: 4996)
void* DataInit(char* lastname, size_t year, KIERUNKI major) {
	MY_STUDENT* student = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

	if (!student) {
		ErrorLog({ "Error creating new student.", 1 });
		return student;
	}

	student->nazwisko = (char*)malloc(strlen(lastname) + 1);
	strcpy(student->nazwisko, lastname);
	student->rok = year;
	student->kierunek = major;

	return student;
}

void DataFree(void* pData) {
	if (!pData) {
		ErrorLog({ "Could not free data.", 1 });
		return;
	}

	MY_STUDENT* p = (MY_STUDENT*)pData;

	free(p->nazwisko);
	free(p);
}



void* DataPush(char* lastname, size_t year, KIERUNKI major) {
	return DataInit(lastname,year,major);
}

void DataPrint(void* pData) {
	if (!pData) {
		ErrorLog({"Could not print data.", 1});
		return;
	}

	MY_STUDENT* p = (MY_STUDENT*)pData;

	printf_s("Nazwisko: %s\nRok: %lld\nKierunek: %s\n",
		p->nazwisko,
		p->rok,
		Nazwy_Kierunkow[p->kierunek].c_str()
	);

}

int DataSearch(void* pCurrentData, void* pSearchedData, char* query) {
	MY_STUDENT* pData = (MY_STUDENT *)pCurrentData;
	MY_STUDENT* searchData = (MY_STUDENT *) pSearchedData;

	if (!pData) {
		ErrorLog({ "Error reading data.", 1 });
		return -1;
	}


	if (strcmp(StudentParams[LASTNAME], query) == 0) {
		if (strcmp(pData->nazwisko, searchData->nazwisko) == 0)
			return 1;
	}
	else if (strcmp(StudentParams[YEAR], query) == 0) {
		if (pData->rok == searchData->rok)
			return 1;
	}
	else if (strcmp(StudentParams[MAJOR], query) == 0) {
		if (pData->kierunek == searchData->kierunek)
			return 1;
	}

	return 0;
}

bool DataSave(void** pdat, FILE* pf) {
	if (*pdat && pf) {
		MY_STUDENT* p = (MY_STUDENT*)*pdat;
		fwrite((const void*)p->nazwisko, sizeof(char*), strlen(p->nazwisko) + 1, pf);
		fwrite(&p->rok, sizeof(size_t), 1, pf);
		fwrite(&p->kierunek, sizeof(KIERUNKI), 1, pf);
		return true;
	}
	return false;
}

int KierunkiStringToEnum(char* str) {
	if (!str) {
		ErrorLog({ "Error, empty string as 'kierunek'.", 1 });
		return -1;
	}

	size_t size = sizeof(Nazwy_Kierunkow) / sizeof(Nazwy_Kierunkow[0]);

	for (int i = 0; i < size; i++) {
		if (strcmp(str, Nazwy_Kierunkow[i].c_str()) == 0) {
			return i;
		}
	}
	return -1;
}