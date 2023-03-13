#pragma once

#include <stdio.h>

struct Error {
	const char* message;
	int status;
};

void ErrorLog(Error err);