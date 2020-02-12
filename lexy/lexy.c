/* Author:	Hamza Syed	*/
/* COSC4317:	Compilers	*/
/* Part-1:	Lexical		*/
#include <stdio.h>
#include <stdlib.h>

char *FileReader(char *fileName);
char *classify(char *jav);

int main()
{
	char javaZero[] = "pgm1.javaz";
	char *javCode = FileReader(javaZero);
	char *javClass = classify(javCode);
	printf("%s",javClass);

	return 0;
}

char *FileReader(char *fileName)
{
	char *buffer=NULL;
	int strSize,readSize;
	FILE *file = fopen(fileName,"r");

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

char *classify(char *jav)
{

	return jav;
}
