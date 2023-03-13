#include "ErrorController.h"

void ErrorLog(Error err)
{
	printf_s("%s, status: %d", err.message, err.status);
}
