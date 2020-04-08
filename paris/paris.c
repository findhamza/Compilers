/* Author:      Hamza Syed      */
/* COSC4317:    Compilers       */
/* Part-1:      Lexical         */

#include "paris.h"

int main()
{
	char lexFile[] = "pgm1.lic";
	char *lexCode = LexReader(lexFile);
}

char *LexReader(char *fileName)
{
	char ext[] = ".lic";
	char *verify = strstr(fileName, ext);
	if(!verify)
	{
		printf("INVALID INTERMIDATE LEX FILE\nexit code(P0)\n");
		exit(0);
	}

	char *buffer=NULL;
	int strSize,reaSize;
	FILE *file = fopen(filename,"r");

	if(file)
	{
                fseek(file,0,SEEK_END);
                strSize = ftell(file);
                rewind(file);

                buffer = (char*)malloc(sizeof(char)*(strSize+1));
                readSize = fread(buffer,sizeof(char),strSize,file);
                buffer[strSize]='\0';

                if(strSize != readSize)
                {
                        free(buffer);
                        buffer=NULL;
                }

                fclose(file);
        }

        return buffer;
}

