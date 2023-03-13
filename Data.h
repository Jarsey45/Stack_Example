#pragma once

#include <string>

enum KIERUNKI {
	INF,
	INF_N,
	ARCH,
	ANG,
};

enum STUDENT_PARMS_ENUM {
	LASTNAME,
	YEAR,
	MAJOR
};

struct MY_STUDENT {
	KIERUNKI kierunek;
	size_t rok;
	char *nazwisko;
};

static const char* StudentParams[]{
	"nazwisko",
	"rok",
	"kierunek"
};


void* DataInit(char* lastname, size_t year, KIERUNKI major);
void DataFree(void* pData);
void* DataPush(char* lastname, size_t year, KIERUNKI major);
void DataPrint(void* pData);
int DataSearch(void* pCurrentData, void* pSearchedData, char* query);
bool DataSave(void** pdat, FILE* pf);

int KierunkiStringToEnum(char* str);
