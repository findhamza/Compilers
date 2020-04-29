#include "../lexy/lexy.h"
#include "../paris/paris.h"
#include "../nancy/nancy.h"

int main()
{
	char *pgm = (char*)calloc(32, sizeof(char));
	char *lexyFile = (char*)calloc(32, sizeof(char));
	char *parisFile = (char*)calloc(32, sizeof(char));
	char *nancyFile = (char*)calloc(32, sizeof(char));

	printf("Please Enter Program Name Without Extension:\n");
	scanf("%s", pgm);

	strncpy(lexyFile, pgm, sizeof(pgm));
	strcat(lexyFile, ".javaz");
	strncpy(parisFile, pgm, sizeof(pgm));
	strcat(parisFile, ".lic");
	strncpy(nancyFile, pgm, sizeof(pgm));
	strcat(nancyFile, ".licp");

	LexyDriver(lexyFile);
	ParisDriver(parisFile);
	NancyDriver(nancyFile);
	return 0;
}
